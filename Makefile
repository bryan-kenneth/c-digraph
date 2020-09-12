#------------------------------------------------------------------------------
# Makefile for CMPS 101-01 Programming Assignment 2
#
#       make                   makes DigraphProperties
#       make Digraph			   makes Digraph
#------------------------------------------------------------------------------

DigraphProperties : DigraphProperties.o Digraph.o List.o
	gcc -g -o DigraphProperties DigraphProperties.o Digraph.o List.o

DigraphProperties.o : DigraphProperties.c Digraph.h List.h
	gcc -g -c -std=c99 -Wall DigraphProperties.c

Digraph.o : Digraph.c Digraph.h List.h
	gcc -g -c -std=c99 -Wall Digraph.c

List.o : List.c List.h
	gcc -g -c -std=c99 -Wall List.c

clean :
	rm -f DigraphProperties Digraph DigraphProperties.o Digraph.o List.o
 