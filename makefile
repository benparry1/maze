run: grid.o trap.o 
	g++ grid.o trap.o -o run
grid.o: grid.cpp
	g++ -c grid.cpp
trap.o: trap.cpp
	g++ -c trap.cpp
clean:
	rm grid.o trap.o run
