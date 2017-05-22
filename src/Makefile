# Makefile

OBJS	= main.o Formula.o reader.o lex.o parse.o initial.o ACDF.o plan.o
OBJS_TEST	= test.o Formula.o reader.o lex.o parse.o initial.o ACDF.o tester.o

CC	= g++
CFLAGS	= -g -Wall -std=c++0x
LEXER = flex
PARSER = bison

start:	$(OBJS) test
		$(CC) $(CFLAGS) $(OBJS) -o start -O2

test:	$(OBJS_TEST)
		$(CC) $(CFLAGS) $(OBJS_TEST) -o test -O2

main.o:  main.cpp
		$(CC) $(CFLAGS) -c main.cpp -o main.o -O2

test.o:  test.cpp
		$(CC) $(CFLAGS) -c test.cpp -o test.o -O2

tester.o:  tester.cpp tester.h
		$(CC) $(CFLAGS) -c tester.cpp -o tester.o -O2

plan.o:  plan.cpp plan.h
		$(CC) $(CFLAGS) -c plan.cpp -o plan.o -O2

initial.o:  initial.cpp initial.h
		$(CC) $(CFLAGS) -c initial.cpp -o initial.o -O2
	
ACDF.o:  ACDF.cpp ACDF.h
		$(CC) $(CFLAGS) -c ACDF.cpp -o ACDF.o -O2

reader.o:  reader.cpp reader.h
		$(CC) $(CFLAGS) -c reader.cpp -o reader.o -O2

Formula.o:  Formula.cpp Formula.h
		$(CC) $(CFLAGS) -c Formula.cpp -o Formula.o -O2

lex.o:  lex.yy.c
		$(CC) $(CFLAGS) -c lex.yy.c -o lex.o -O2

lex.yy.c:  lex.l parse.o
		$(LEXER) lex.l

parse.o:  parse.tab.c
		$(CC) $(CFLAGS) -c parse.tab.c -o parse.o -O2

parse.tab.c:	parse.y
		$(PARSER) --defines=parse.h -d parse.y

.PHONY : clean

test:


clean:
	rm -f *.o *.c parse.h parse.output output_begin output_end
