all: main

main: main.o syntax.tab.o
	$(CC) -o main main.o syntax.tab.o

syntax.tab.c syntax.tab.h: syntax.y
	bison -d syntax.y

main.o: main.c syn.h
	$(CC) -c main.c

syntax.tab.o: syntax.tab.c syn.h
	$(CC) -c syntax.tab.c

clean:
	rm -f *.o *.tab.* lex.yy.c main
