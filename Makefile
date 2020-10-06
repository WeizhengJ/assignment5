.DEFAULT_GOAL := parking.exe
parking.o: parking.cc
	g++ -c parking.cc -Wall -std=c++11

parking.exe: parking.o
	g++ -o parking.exe parking.o -Wall -std=c++11

clean:
	rm *.o parking.exe
