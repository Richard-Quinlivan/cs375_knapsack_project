CFLAGS = g++ -std=c++14 -g

all: recursive

recursive.o: recursive.cpp
	$(CFLAGS) -c recursive.cpp

recursive: recursive.o
	$(CFLAGS) recursive.o -o recursive

run: all
	./recursive

.PHONY: clean
clean:
	rm *.o recursive
