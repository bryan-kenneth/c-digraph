/*
 * Author: Bryan Munox
 * 1553629 Bmunozga
 * CMPS 101
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "Digraph.h"

// Structs --------------------------------------------------------------------

struct DigraphObj {
	int v; // number of vertices
	int e; // number of edges
	int *mark; // array to store marks
	List *L; // array of lists of neighbors
	int SCC_flag; // lets us know if we need to recompute SCCs
	int SCC_N; // number of SCCs
	int **SCC; // 2d array to store SCCs
} DigraphObj;

// Constructors-Destructors ---------------------------------------------------
Digraph newDigraph(int numVertices) {
	Digraph G = malloc(sizeof(DigraphObj)); // create digraph
	G->v = numVertices;
	G->e = 0; // start with 0 edges
	G->mark = calloc(numVertices + 1, sizeof(int)); // array for mark
	G->L = calloc(numVertices + 1, sizeof(List)); // create array of lists
	G->SCC_flag = 1;
	G->SCC_N = 0;
	G->SCC = (int**)calloc(numVertices + 1, sizeof(int*)); // 2d array for SCCs
	for(int i = 0; i <= numVertices; i++) {
		G->SCC[i] = (int*)calloc(numVertices + 1, sizeof(int));
	}
	if (G == NULL || G->mark == NULL || G->L == NULL || G->SCC == NULL) {
		printf("Error: calloc or malloc failed in newDigraph()");
		exit(1);
	}
	return (G);
}

void freeDigraph(Digraph* pG) {
	Digraph G = *pG;
	free(G->mark);
	for (int i = 1; i <= G->v; i++) {
		if (G->L[i] != NULL) freeList(&G->L[i]);
	}
	for(int i = 0; i <= G->v; i++) free(G->SCC[i]);
	free(G->SCC);
	free(G->L);
	free(G);
	pG = NULL;
}

// Access functions -----------------------------------------------------------
int getOrder(Digraph G) {
	if (G == NULL) {
		printf("Error: getOrder() recieved a NULL Digraph\n");
		exit(1);
	}
	return(G->v);
}

int getSize(Digraph G) {
	if (G == NULL) {
		printf("Error: getSize() recieved a NULL Digraph\n");
		exit(1);
	}
	return(G->e);
}

int getOutDegree(Digraph G, int u) {
	if (0 < u && u <= G->v) {
		if (G == NULL) {
			printf("Error: getOutDegree() revieced a NULL Digraph");
			exit(1);
		}
		if (G->L[u] != NULL) {
			return(length(G->L[u]));
		} else {
			return (0);
		}
	} else {
		return(-1);
	}
}

List getNeighbors(Digraph G, int v) {
	if (G == NULL) {
		printf("Error: getNeighbor() recieved a NULL Digraph\n");
		exit(1);
	} else {
		return(G->L[v]);
	}
}

int getCountSCC(Digraph G) {
	if(G->SCC_flag) {
		refreshSCC(G);
	}
	return(G->SCC_N);
}

int getNumSCCVertices(Digraph G, int u) {
	if (0 < u && u <= G->v) {
		if(G->SCC_flag) {
			refreshSCC(G);
		}
		int SCCVertices = 1;
		for(int i = 1; i <= G->v; i++) {
			if(G->SCC[u][i]) SCCVertices++;
		}
		return(SCCVertices);
	} else {
		return(-1);
	}
}

int inSameSCC(Digraph G, int u, int v) {
	if (0 < u && u <= G->v && 0 < v && v <= G->v) {
		if(G->SCC_flag) {
			refreshSCC(G);
		}
		return(G->SCC[u][v]);
	} else {
		return(-1);
	}
}

// Manipulation procedures ----------------------------------------------------
int addEdge(Digraph G, int u, int v) {
	if (0 < u && u <= G->v && 0 < v && v <= G->v) {
		if (checkList(G->L[u], v) == NOTFOUND) {
			if (G->L[u] == NULL) {
				G->L[u] = newList();
			}
			append(G->L[u], v);
			G->e++;
			InsertSort(G->L[u]);
			G->SCC_flag = 1;
			return(0);
		}
		return(1);
	} else {
		return(-1);
	}
}

int deleteEdge(Digraph G, int u, int v) {
	if (0 < u && u <= G->v && 0 < v && v <= G->v) {
		List L = getNeighbors(G, u);
		if (checkList(L, v) == FOUND) {
			for (Node N = getFront(L); N != NULL; N = getNextNode(N)) {
				if (getValue(N) == v) {
					deleteNode(L, N);
					G->e--;
					G->SCC_flag = 1;
					return(0);
				}
			}
		}
		return(1);
	} else {
		return(-1);
	}
}

void unvisitAll(Digraph G) {
	if (G == NULL) {
		printf("Error: getOrder() recieved a NULL Digraph\n");
		exit(1);
	}
	for (int i = 1; i <= G->v; i++) {
		G->mark[i] = UNVISITED;
	}
}

void setMark(Digraph G, int u, int theMark) {
	if (G == NULL) {
		printf("Error: getOrder() recieved a NULL Digraph\n");
		exit(1);
	}
	G->mark[u] = theMark;
}

int getMark(Digraph G, int u) {
	if (G == NULL) {
		printf("Error: getOrder() recieved a NULL Digraph\n");
		exit(1);
	}
	return(G->mark[u]);
}


// Other operations ------------------------------------------------------------

void printDigraph(FILE* out, Digraph G) {
	fprintf(out, "%d", G->v);
	Node N = NULL;
	for (int i = 1; i <= G->v; i++) {
		if (G->L[i] != NULL) {
			for(N = getFront(G->L[i]); N != NULL; N = getNextNode(N)) {
				fprintf(out, ", %d %d", i, getValue(N));
			}
		}
	}
	fprintf(out, "\n");
}
	
	
void DFS(Digraph G, int u, List L) {
	if (getMark(G, u) == UNVISITED) {
		setMark(G, u, INPROGRESS);
		List Neighbors = getNeighbors(G, u);
		for (Node N = getFront(Neighbors); N != NULL; N = getNextNode(N)) {
			if(getMark(G, getValue(N)) == UNVISITED) {
				DFS(G, getValue(N), L);
			}
		}
		setMark(G, u, ALLDONE);
		if (L != NULL) {
			prepend(L, u);
		}
	}
}
	
void refreshSCC(Digraph G) {
	unvisitAll(G);
	List finish = newList();
	for (int i = 1; i <= G->v; i++) {
		DFS(G, i, finish);
	}
	Digraph T = transpose(G);
	unvisitAll(T);
	List prev_n = newList();
	for(Node N = getFront(finish); N != NULL; N = getNextNode(N)) {
		int result = DFS_SCC(G, T, getValue(N), prev_n);
		if(result) {
			G->SCC_N++;
			clear(prev_n);
		}
	}
	G->SCC_flag = 0;
	freeList(&finish);
	freeList(&prev_n);
	freeDigraph(&T);
}

int DFS_SCC(Digraph G, Digraph T, int u, List L) {
	if (getMark(T, u) == UNVISITED) {
		setMark(T, u, INPROGRESS);
		List Neighbors = getNeighbors(T, u);
		for (Node N = getFront(Neighbors); N != NULL; N = getNextNode(N)) {
			if(getMark(T, getValue(N)) == UNVISITED) {
				for(Node P = getFront(L); P != NULL; P = getNextNode(P)) {
					G->SCC[getValue(P)][getValue(N)] = 1;
					G->SCC[getValue(N)][getValue(P)] = 1;
				}
				G->SCC[u][getValue(N)] = 1;
				G->SCC[getValue(N)][u] = 1;
				append(L, u);
				DFS_SCC(G, T, getValue(N), L);
			}
		}
		setMark(G, u, ALLDONE);
		return(1);
	}
	return(0);
}

Digraph transpose(Digraph G) {
	Digraph T = newDigraph(G->v); // create new digraph of same size
	for(int i = 1; i <= G->v; i++) {
		List neighbors = getNeighbors(G, i);
		for (Node N = getFront(neighbors); N != NULL; N = getNextNode(N)) {
			addEdge(T, getValue(N), i);
		}
	}
	return T;
}
	
	
	
	
	



