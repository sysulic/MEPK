#Makefile

OBJECTS = main.o epddlLexer.o epddlParser.o acdf.o adnf.o parse.o initial.o plan.o
OBJS_TEST = test.o epddlLexer.o epddlParser.o acdf.o adnf.o parse.o initial.o tester.o

LEXER = flex
PARSER = bison
COMPILER = g++
CFLAGS = -g -Wall -std=c++11

start: ${OBJECTS} test
	   ${COMPILER} ${CFLAGS} ${OBJECTS} -o start -O2

test: $(OBJS_TEST)
	  $(COMPILER) $(CFLAGS) $(OBJS_TEST) -o test -O2

main.o: main.cpp
	${COMPILER} ${CFLAGS} -c main.cpp -o main.o -O2

test.o: test.cpp
		$(COMPILER) $(CFLAGS) -c test.cpp -o test.o -O2

tester.o: tester.cpp tester.h
		  $(COMPILER) $(CFLAGS) -c tester.cpp -o tester.o -O2

plan.o: plan.h plan.cpp
	${COMPILER} ${CFLAGS} -c plan.cpp -o plan.o -O2

initial.o: initial.h initial.cpp
	${COMPILER} ${CFLAGS} -c initial.cpp -o initial.o -O2

parse.o: parse.h parse.cpp
	${COMPILER} ${CFLAGS} -c parse.cpp -o parse.o -O2

acdf.o: acdf.h acdf.cpp
	${COMPILER} ${CFLAGS} -c acdf.cpp -o acdf.o -O2

adnf.o: adnf.h adnf.cpp
	${COMPILER} ${CFLAGS} -c adnf.cpp -o adnf.o -O2

epddlLexer.o: lex.yy.c
	${COMPILER} ${CFLAGS} -c lex.yy.c -o epddlLexer.o -O2

lex.yy.c: epddlLexer.l epddlParser.o
	${LEXER} epddlLexer.l

epddlParser.o: epddlParser.tab.c
	${COMPILER} ${CFLAGS} -c epddlParser.tab.c -o epddlParser.o -O2

epddlParser.tab.c: epddlParser.y
	${PARSER} --defines=epddlParser.h -d epddlParser.y

.PHONY: clean

clean:
	rm -r *.o *c epddlParser.h start test