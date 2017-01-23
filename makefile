prog1sorter: sorter.o
	gcc -Wall sorter.o -o prog1sorter

sorter.o: sorter.c
	gcc -Wall -c sorter.c

clean:
	rm *.o prog1sorter prog1generator
