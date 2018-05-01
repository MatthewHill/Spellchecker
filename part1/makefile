CC=g++
CFLAGS=-std=c++11 -Wall
OUTPUTNAME=Spellcheck

all: Dictionary Spellcheck
	g++ -std=c++11 Dictionary.o Spellcheck.o -o $(OUTPUTNAME)
Dictionary: Dictionary.h Dictionary.cpp
	$(CC) $(CFLAGS) -c Dictionary.h
	$(CC) $(CFLAGS) -c Dictionary.cpp
Spellcheck: 
	$(CC) $(CFLAGS) -c Spellcheck.cpp
clean:
	rm *.o
	rm $(OUTPUTNAME)