/*
 * Author: Bryan Munox
 * 1553629 Bmunozga
 * CMPS 101
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Digraph.h"

#define MAX 1000


int main(int argc, char* argv[]) {
	FILE *in, *out;

	// check command line for correct number of arguments
	if(argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	int ch;
	int linecount = 0;
	
	// count lines
	while(EOF != (ch = fgetc(in))) {
		if (ch == '\n') {
			linecount++;
		}
	}
	
	// reset file pointer
	fseek(in, 0, SEEK_SET);
	
	// init
	char line[MAX];
	char *ptr;
	fgets(line, MAX, in);
	ptr = strtok(line, ", "); // get number of nodes
	int nV = atoi(ptr);
	Digraph G = newDigraph(nV); // create new Digraph with that many nodes
	
	// create Digraph based on first input line
	ptr = strtok(NULL, " ");
	int eFlag = 0;
	while (ptr != NULL) {
		int a[2];
		for(int i = 0; i < 2; i++) {
			a[i] = atoi(ptr);
			ptr = strtok(NULL, " ");
		}
		if (a[0] > nV || a[1] > nV || a[0] == a[1]) {
			eFlag = 1;
			fseek(in, 0, SEEK_SET); // reset file ptr
			fgets(line, MAX, in); // load in 1000 first chars into string
			ptr = (char*) strtok(line, "\n"); // get digraph spec
			fprintf(out, "%s\n", line); // print because error
		} else {
			addEdge(G, a[0], a[1]);
		}
	}
	
	for(fgets(line, MAX, in), linecount--; linecount > 0; fgets(line, MAX, in), linecount--) {
		if (eFlag) {
			fprintf(out, "ERROR\n"); // error and stop processing
			break;
		}
		int flag = 1;
		ptr = (char*)strtok(line, "\r\n");
		fprintf(out, "%s\n", ptr);
		if (strcmp(ptr, "PrintDigraph") == 0) {
			printDigraph(out, G);
			flag = 0;
		}
		if (strcmp(ptr, "GetOrder") == 0) {
			fprintf(out, "%d\n", getOrder(G));
			flag = 0;
		}
		if (strcmp(ptr, "GetSize") == 0) {
			fprintf(out, "%d\n", getSize(G));
			flag = 0;
		}
		if (strcmp(ptr, "GetCountSCC") == 0) {
			fprintf(out, "%d\n", getCountSCC(G));
			flag = 0;
		}
		if (flag) ptr = (char*)strtok(line, " ");
		if (strcmp(ptr, "GetOutDegree") == 0) {
			ptr = strtok(NULL, " ");
			int u = atoi(ptr);
			int result = getOutDegree(G, u);
			if (result != -1) {
				fprintf(out, "%d\n", result);
				flag = 0;
			}
		}
		if (strcmp(ptr, "GetNumSCCVertices") == 0) {
			ptr = strtok(NULL, " ");
			int u = atoi(ptr);
			int result = getNumSCCVertices(G, u);
			if (result != -1) {
				fprintf(out, "%d\n", result);
				flag = 0;
			}
		}
		if (strcmp(ptr, "AddEdge") == 0) {
			ptr = strtok(NULL, " ");
			int u = atoi(ptr);
			ptr = strtok(NULL, "\n");
			int v = atoi(ptr);
			int result = addEdge(G, u, v);
			if (result != -1) {
				fprintf(out, "%d\n", result);
				flag = 0;
			}
		}
		if (strcmp(ptr, "DeleteEdge") == 0) {
			ptr = strtok(NULL, " ");
			int u = atoi(ptr);
			ptr = strtok(NULL, "\n");
			int v = atoi(ptr);
			int result = deleteEdge(G, u, v);
			if (result != -1) {
				fprintf(out, "%d\n", result);
				flag = 0;
			}
		}
		if (strcmp(ptr, "InSameSCC") == 0) {
			ptr = strtok(NULL, " ");
			int u = atoi(ptr);
			ptr = strtok(NULL, "\n");
			int v = atoi(ptr);
			int result = inSameSCC(G, u, v);
			if (result != -1) {
				if (result == 1) {
					fprintf(out, "YES\n");
				} else {
					fprintf(out, "NO\n");
				}
				flag = 0;
			}
		}
		if (flag) fprintf(out, "ERROR\n");
	}

	freeDigraph(&G);
	
	// close input and output files
	fclose(in);
	fclose(out);
	
    return(0);
}
	
	
	
	
	