all:
	g++ -Wall -O3 -o SA main.cpp

clean:
	rm -f main *.o