all: prog1sorter prog1generator

prog1sorter: sorter.o option_parse.o timer.o
	gcc -Wall sorter.o option_parse.o timer.o -o prog1sorter

prog1generator: generator.o option_parse.o timer.o
	gcc -Wall generator.o option_parse.o timer.o -o prog1generator

sorter.o: sorter.c option_parse.c timer.c
	gcc -Wall -c sorter.c option_parse.c timer.c

generator.o: generator.c option_parse.c timer.c
	gcc -Wall -c generator.c option_parse.c timer.c

option_parse.o: option_parse.c
	gcc -Wall -c option_parse.c

timer.o: timer.c
	gcc -Wall -c timer.c

clean:
	rm *.o prog1sorter prog1generator

test: test-1 test-2

test-1:
	./prog1generator -s 0 -o test.txt
	./prog1sorter -i test.txt -o test_result.txt
	./prog1generator -s 0 -o test.txt
	./prog1sorter -i test.txt -o test_result2.txt
	diff test_result2.txt test_result.txt

test-2:
	./prog1generator -s 1 -n 10 -o test.txt
	./prog1sorter -n 10 -i test.txt -o test_result.txt
	./prog1generator -s 1 -n 10 -o test.txt
	./prog1sorter -n 10 -i test.txt -o test_result2.txt
	diff test_result2.txt test_result.txt

test-3:
