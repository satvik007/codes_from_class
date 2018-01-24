CC = g++
OBJS = dfs.o graph.o dlist.o

a.out : ${OBJS}
	${CC} ${OBJS}

main.o: dfs.cpp
	${CC} -c dfs.cpp

graph.o : graph.cpp
	${CC} -c graph.cpp

dlist.o : dlist.cpp
	${CC} -c dlist.cpp
clean:
	\rm a.out *.o *.dot
