CC = gcc
OBJS = dijkstra.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: dijkstra.c
	${CC} -c dijkstra.c

queue.o : graph.c
	${CC} -c graph.c

clean:
	\rm a.out *.o *.dot
