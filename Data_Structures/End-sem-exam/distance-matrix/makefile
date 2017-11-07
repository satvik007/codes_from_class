CC = gcc
OBJS = test1.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: test1.c
	${CC} -c test1.c

queue.o : graph.c
	${CC} -c graph.o

clean:
	\rm a.out *.o *.dot
