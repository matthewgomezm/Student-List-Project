hw4: matrix.o main.o
	g++ -o hw4 -std=c++11 matrix.o main.o
matrix.o: matrix.h matrix.cpp
	g++ -c -std=c++11 matrix.h
	g++ -c -std=c++11 matrix.cpp
main.o: main.cpp
	g++ -c -std=c++11 main.cpp
clear:
	rm *.o
	rm *.h.gch
	rm hw4
