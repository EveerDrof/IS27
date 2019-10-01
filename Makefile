
hello: main.o konstantinov.o
	g++ -o konstantinov main.o konstantinov.o

main.o: main.cpp
	g++ -c main.cpp

konstantinov.o: konstantinov.cpp
	g++ -c konstantinov.cpp

clean:
	rm -f *.o konstantinov
