CC=g++ -std=c++11 #The compiler
LIBS=-lm #Libraries referenced

driver: tags.o tagdriver.o
	$(CC) tags.o tagdriver.o -o driver $(LIBS)

tags.o: tags.cpp tags.h
	$(CC) -c tags.cpp

tagdriver.o: tagdriver.cpp
	$(CC) -c tagdriver.cpp


run:
	./driver

clean:
	@rm -f *.o
	@rm driver
	@rm -f NYMTYR001_output.txt  #removing txt file with output