CC=g++ -std=c++20 #The compiler
LIBS=-lm #Libraries referenced

extractor: frames.o extractor.o
	$(CC) frames.o extractor.o -o extractor $(LIBS)

frames.o: frames.cpp frames.h
	$(CC) -c frames.cpp

frameDriver.o: extractor.cpp
	$(CC) -c extractor.cpp

run:
	./extractor sloan_image.pgm -t 0 0 100 100 -s 100 100 -w reverse REVERSE

clean:
	@rm -f *.o
	@rm -f extractor
	@rm invseq*
	@rm sequence2*
	@rm SIMPLE*
	@rm BACKWARDS*
	@rm VERTICAL*
	@rm HORIZONTAL*
	@rm REVERSE*
	@rm INVERTED*
	@rm REINVERT*
	@rm MULTI*
	
	