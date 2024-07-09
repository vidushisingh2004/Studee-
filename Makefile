studee: main.o input.o
	g++ -Wall main.o input.o /usr/local/cs/cs251/react.o -lcurl -o studee

main.o: main.cpp User.h
	g++ -Wall -c main.cpp

input.o: input.cpp User.h 
	g++ -Wall -c input.cpp
