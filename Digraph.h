/*
 * Author: Bryan Munox
 * 1553629 Bmunozga
 * CMPS 101
 */
 
#include <stdio.h>
#include "List.h"


#define UNVISITED -3
#define INPROGRESS -4
#define ALLDONE -5
 
// private Digraph type
typedef struct DigraphObj *Digraph;
 
// Constructors-Destructors ---------------------------------------------------
Digraph newDigraph(int numVertices); // returns a DigraphObj pointer

void freeDigraph(Digraph* pG);

// Access functions -----------------------------------------------------------
int getOrder(Digraph G);

int getSize(Digraph G);

int getOutDegree(Digraph G, int u);

List getNeighbors(Digraph G, int v);

int getCountSCC(Digraph G);

int getNumSCCVertices(Digraph G, int u);

int inSameSCC(Digraph G, int u, int v);

// Manipulation procedures ----------------------------------------------------
int addEdge(Digraph G, int u, int v);

int deleteEdge(Digraph G, int u, int v);

void unvisitAll(Digraph G);

int getMark(Digraph G, int u);

void setMark(Digraph G, int u, int theMark);

// Other operations -----------------------------------------------------------
void printDigraph(FILE* out, Digraph G);

void DFS(Digraph G, int u, List L);

void refreshSCC(Digraph G);

Digraph transpose(Digraph G);

int DFS_SCC(Digraph G, Digraph T, int u, List L);