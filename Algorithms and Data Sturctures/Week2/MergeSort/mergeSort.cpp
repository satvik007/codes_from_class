#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>

// File pointers declared global for speed optimization.
FILE *p, *q, *temp1, *temp2, *f;

// returns minimum of two integers.
int min(int a, int b){
    return (a <= b ? a : b);
}

// merging 2 sorted sub arrays between lo and mid , mid + 1 and hi.
inline void merge(int lo, int mid, int hi){
    fseek(temp1, 0, SEEK_SET); // Pointer to start of temp file1.
    fseek(temp2, 0, SEEK_SET); // Pointer to start of temp file2.
    //fseek(q, lo * 4, SEEK_SET);
    int temp;
    // Writing into both the temporary files.
    for(int i=lo; i<=mid; i++){
        fread(&temp, sizeof temp, 1, q);
        fwrite(&temp, sizeof temp, 1, temp1);
    }
    for(int i=mid+1; i<=hi; i++){
        fread(&temp, sizeof temp, 1, q);
        fwrite(&temp, sizeof temp, 1, temp2);
    }

    // sentinel for safety reasons.
    int inf = INT_MAX;
    fwrite(&inf, sizeof inf, 1, temp1);
    fwrite(&inf, sizeof inf, 1, temp2);

    int left = mid - lo + 1;
    int right = hi - mid;
    int i = 0, j = 0;
    int val1, val2;
    fseek(q, -(hi - lo + 1)*4, SEEK_CUR);
    fseek(temp1, 0, SEEK_SET);
    fseek(temp2, 0, SEEK_SET);
    fread(&val1, sizeof val1, 1, temp1);
    fread(&val2, sizeof val2, 1, temp2);

    while(i < left && j < right){
        if(val1 <= val2){
            fwrite(&val1, sizeof val1, 1, q);
            i++; fread(&val1, sizeof val1, 1, temp1);
        }else{
            fwrite(&val2, sizeof val2, 1, q);
            j++; fread(&val2, sizeof val2, 1, temp2);
        }
    }
    while(i < left){
        fwrite(&val1, sizeof val1, 1, q);
        i++; fread(&val1, sizeof val1, 1, temp1);
    }
    while(j < right){
        fwrite(&val2, sizeof val2, 1, q);
        j++; fread(&val2, sizeof val2, 1, temp2);
    }
}

inline void mergeSort(int lo, int hi){
    temp1 = fopen("tempFile1.bin", "wb+");
    temp2 = fopen("tempFile2.bin", "wb+");
    for (int w = 1; w <= hi - lo; w <<= 1){
        printf("%d\n", w);
        fseek(q, 0, SEEK_SET);
        for (int i = lo; i < hi; i += 2*w){
            merge(i, min(i + w - 1, hi), min(i + 2*w-1, hi));
        }
    }
    fclose(temp1); fclose(temp2);
    remove("tempFile1.bin");
    remove("tempFile2.bin");
}

int main(){
    char name1[100] = {"input.bin"};
    char name2[100] = {"output.txt"};
    //printf("Enter n: ");
    int n;// scanf("%d", &n);
    //printf("Enter name of input file: ");
    //scanf("%s", name1);
    //printf("Enter name of output file: ");
    //scanf("%s", name2);

    p = fopen(name1, "rb+"); // input binary file.
    f = fopen(name2, "w"); // output text file.
    q = fopen("Sorted.bin", "wb+"); // output binary file.

    int temp;
    fseek(p, 0L, SEEK_END);
    n = ftell(p) / 4;
    fseek(p, 0L, SEEK_SET);
    for(int i=0; i<n; i++){
        fread(&temp, sizeof temp, 1, p); // reading input binary file.
        fwrite(&temp, sizeof temp, 1, q); // making a copy.
    }
    std::cout << n << std::endl;
    mergeSort(0, n-1);

    fseek(q, 0, SEEK_SET);
    for(int i=0; i<n; i++){
        fread(&temp, sizeof temp, 1, q); // reading the sorted bin file.
        fprintf(f, "%d\n", temp); // writing into a text file.
    }

    return 0;
}