
kursach: main.o konstantinov.o utilities.o kharitonova.o vershinin.o zachynyaev.o smirnov.o ramazanov.o kupriyanova.o lalykin.o pshenichnikov.o babaev.o
	g++ -o konstantinov main.o konstantinov.o utilities.o kharitonova.o vershinin.o ramazanov.o babaev.o zachynyaev.o smirnov.o kupriyanova.o  lalykin.o pshenichnikov.o babaev.o

main.o: main.cpp
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
ramazanov.o:ramazanov.cpp
	g++ -c ramazanov.cpp
kupriyanova.o:kupriyanova.cpp
	g++ -c kupriyanova.cpp
lalykin.o: lalykin.cpp
	g++ -c lalykin.cpp
pshenichnikov.o:pshenichnikov.cpp
	g++ -c pshenichnikov.cpp
babaev.o:babaev.cpp
	g++ -c babaev.cpp
clean:
	rm -f *.o konstantinov
