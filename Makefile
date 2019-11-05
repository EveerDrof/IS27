lib.a:  konstantinov.o utilities.o  vershinin.o zachynyaev.o smirnov.o 
	ar cr lib.a konstantinov.o utilities.o  vershinin.o  zachynyaev.o smirnov.o
main.o:main.cpp
	g++ -c main.cpp


konstantinov.o: konstantinov.cpp
	g++ -c konstantinov.cpp
utilities.o: utilities.cpp
	g++ -c utilities.cpp
kharitonova.o: kharitonova.cpp
	g++ -c kharitonova.cpp
vershinin.o: vershinin.cpp
	g++ -c vershinin.cpp
zachynyaev.o:zachynyaev.cpp
	g++ -c zachynyaev.cpp
smirnov.o:smirnov.cpp
	g++ -c smirnov.cpp

clean:
	rm -f *.o konstantinov
