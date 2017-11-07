CC = gcc
OBJS = test2.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: test2.c
	${CC} -c test2.c

queue.o : graph.c
	${CC} -c graph.o

clean:
	\rm a.out *.o *.dot
