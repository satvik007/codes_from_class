CC = gcc
OBJS = cut-vertices.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: cut-vertices.c
	${CC} -c cut-vertices.c

queue.o : graph.c
	${CC} -c graph.c

clean:
	\rm a.out *.o *.dot
