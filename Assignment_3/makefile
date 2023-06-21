CC=g++ -std=c++20 #The compiler
LIBS=-lm #Libraries referenced

all:testing findcomp

testing: ConnectedComponents.o PGMimageProcessor.o testing.o
	$(CC) ConnectedComponents.o PGMimageProcessor.o testing.o -o testing $(LIBS)

findcomp: PGMimageProcessor.o ConnectedComponents.o findcomp.o
	$(CC) PGMimageProcessor.o ConnectedComponents.o findcomp.o -o findcomp $(LIBS)

ConnectedComponents.o: ConnectedComponents.cpp
	$(CC) -c ConnectedComponents.cpp -o ConnectedComponents.o

PGMimageProcessor.o: PGMimageProcessor.cpp PGMimageProcessor.h
	$(CC) -c PGMimageProcessor.cpp -o PGMimageProcessor.o

testing.o: testing.cpp
	$(CC) -c testing.cpp -o testing.o

findcomp.o: findcomp.cpp
	$(CC) -c findcomp.cpp -o findcomp.o

run:
	./findcomp chess.pgm -s 3 500 -t 160 -w sample -p

test:
	./testing

clean:
	@rm -f *.o
	@rm -f findcomp
	@rm sample
	@rm testing
	