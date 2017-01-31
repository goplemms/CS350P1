all: prog1sorter prog1generator

prog1sorter: sorter.o option_parse.o
	gcc -Wall sorter.o option_parse.o -o prog1sorter

prog1generator: generator.o option_parse.o
	gcc -Wall generator.o option_parse.o -o prog1generator

sorter.o: sorter.c option_parse.c
	gcc -Wall -c sorter.c option_parse.c

generator.o: generator.c option_parse.c
	gcc -Wall -c generator.c option_parse.c

option_parse.o: option_parse.c
	gcc -Wall -c option_parse.c

clean:
	rm *.o prog1sorter prog1generator
