OFILES = grammar.o scanner.o main.o parser.o  ast.o  sem.o codegen.o
LEX = flex
BISON = bison
CPATH=/opt/llvm/bin/
CC = $(CPATH)clang++
LD = $(CPATH)clang++
CXXFLAGS=`$(CPATH)llvm-config --cppflags` -std=c++11 -Wno-deprecated-register
LDFLAGS=`$(CPATH)llvm-config --ldflags --system-libs --libs engine` -fvisibility=internal 

all: parse scan parse nightfury

scan: scanner.c

parse: grammar.c

grammar.c grammar.h: grammar.y 
	$(BISON) --debug -d $< -o grammar.c

scanner.c: scanner.lex grammar.h
	$(LEX) --bison-bridge -o $@ $<

parse: grammar.c grammar.h


nightfury: $(OFILES)
	$(LD) -g $(OFILES) $(LDFLAGS) -o $@

%.o %.d : %.C
	$(CC) -g -c -x c++ $(CXXFLAGS) $< -MD 

%.o %.d : %.c
	$(CC) -g -c -x c++ $(CXXFLAGS) $< -MD

clean: 
	rm -rf *.o *~ grammar.c grammar.h scanner.c *.d nightfury

include $(addsuffix .d ,$(basename $(OFILES)))
