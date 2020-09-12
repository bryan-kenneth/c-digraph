Bryan Munoz 1553629

Files Included:
Makefile
List.h
List.c
Digraph.h
Digraph.c
DigraphProperties.c
README

Descrition:

This program takes in lines of integers and commands from a file, then prints out the line
followed by the output to the command. The first line specifies the digraph that the program
takes in represented by an array of linked lists.

Efficiency:

Distance: O(n)
My distance function recurses through all nodes that u can reach adding 1 to the distance each
time the function is called again until it reaches v or searches all paths. If a path is found
the function continues looking for shorter paths or until all options have been searched.

Acyclic: O(n)
My acyclic function uses a DFS, if while searching we reach a node that is INPROGRESS then 
there must be a cycle.

TopoSort: O(n)
My toposort also uses the same DFS function to check if acyclic while also creating a list
as each node reaches ALLDONE such that that is the first item to be printed.