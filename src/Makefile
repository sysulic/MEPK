#Makefile

OBJECTS = main.o epddlLexer.o epddlParser.o acdf.o adnf.o parse.o heuristicHelper.o initial.o plan.o planner.o

LEXER = flex
PARSER = bison
COMPILER = g++
COMPILE_OPTION = -g -Wall -std=c++11

start: ${OBJECTS}
	${COMPILER} ${COMPILE_OPTION} ${OBJECTS} -o start -O2

main: main.cpp
	${COMPILER} ${COMPILE_OPTION} -c main.cpp -o main.o -O2

planner.o: planner.h planner.cpp
	${COMPILER} ${COMPILE_OPTION} -c planner.cpp -o planner.o -O2

plan.o: plan.h plan.cpp
	${COMPILER} ${COMPILE_OPTION} -c plan.cpp -o plan.o -O2

initial.o: initial.h initial.cpp
	${COMPILER} ${COMPILE_OPTION} -c initial.cpp -o initial.o -O2

heuristicHelper.o: heuristicHelper.h heuristicHelper.cpp
	${COMPILER} ${COMPILE_OPTION} -c heuristicHelper.cpp -o heuristicHelper.o -O2

parse.o: parse.h parse.cpp
	${COMPILER} ${COMPILE_OPTION} -c parse.cpp -o parse.o -O2

Cover.o: Cover.h Cover.cpp
	${COMPILER} ${COMPILE_OPTION} -c acdf.cpp -o acdf.o -O2

ACDF.o: ACDF.h ACDF.cpp
	${COMPILER} ${COMPILE_OPTION} -c adnf.cpp -o adnf.o -O2

epddlLexer.o: lex.yy.c
	${COMPILER} ${COMPILE_OPTION} -c lex.yy.c -o epddlLexer.o -O2

lex.yy.c: epddlLexer.l epddlParser.o
	${LEXER} epddlLexer.l

epddlParser.o: epddlParser.tab.c
	${COMPILER} ${COMPILE_OPTION} -c epddlParser.tab.c -o epddlParser.o -O2

epddlParser.tab.c: epddlParser.y
	${PARSER} --defines=epddlParser.h -d epddlParser.y

.PHONY: clean

clean:
	rm -r *.o *c epddlParser.h start