CC = gcc
OBJS = hamiltonian.o graph.o dlist.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: hamiltonian.c
	${CC} -c hamiltonian.c

graphlib.o : graph.c
	${CC} -c graph.c

queue.o : dlist.c
	${CC} -c dlist.c

clean:
	\rm a.out *.o *.dot
