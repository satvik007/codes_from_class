CC = gcc
OBJS = dfs.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: dfs.c
	${CC} -c dfs.c

queue.o : graph.c
	${CC} -c graph.c

clean:
	\rm a.out *.o *.dot
