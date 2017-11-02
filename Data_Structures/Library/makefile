CC = gcc
OBJS = test.o queue.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: test.c
	${CC} -c test.c

queue.o : queue.c
	${CC} -c queue.c

clean:
	\rm a.out *.o *.dot
