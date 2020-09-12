//-----------------------------------------------------------------------------
// Bryan Munoz 1553629
// List.c
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj {
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private ListObj type
typedef struct ListObj {
	Node front;
	Node back; 
	int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// returns a List which points to a new empty list object
List newList(void) {
	List L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->length = 0;
	return(L);
}

// frees list and nodes
void freeList(List* pL) {
	if ( pL != NULL && *pL != NULL) {
		List L = *pL;
		if(L->length > 0) {
			Node N = L->front;
			while(N != NULL) {
				Node T = N->next;
				N->next = NULL;
				N->prev = NULL;
				free(N);
				N = T;
			}
		}
		L->front = NULL;
		L->back = NULL;
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

int length(List L) {
	if (L == NULL) {
		printf("Error: length() recieved a NULL input\n");
		exit(1);
	} else {
		return(L->length);
	}
}

int frontValue(List L) {
	if (L == NULL) {
		printf("Error: frontValue() recieved a NULL input\n");
		exit(1);
	} else if (L->length == 0) {
		printf("Error: frontValue() called for an empty list");
		exit(1);
	} else {
		return(L->front->data);
	}
}

int backValue(List L) {
	if (L == NULL) {
		printf("Error: backValue() recieved a NULL input\n");
		exit(1);
	} else if (L->length == 0) {
		printf("Error: backValue() called for an empty list");
		exit(1);
	} else {
		return(L->back->data);
	}
}

int getValue (Node N) {
	if (N == NULL) {
		printf("Error: getValue() recieved a NULL input\n");
		exit(1);
	} else {
		return(N->data);
	}
}

int equals(List A, List B) {
	if (A->length == B->length) {
		Node Aptr = A->front;
		Node Bptr = B->front;
		// goes through each node to check if match
		while (Aptr != NULL && Bptr != NULL) {
			if (Aptr->data == Bptr->data) {
				Aptr = Aptr->next;
				Bptr = Bptr->next;
			} else {
				return(0);
			}
		}
		return(1);
	}
	return(0);
}

// Manipulation Procedures ----------------------------------------------------

void clear(List L) {
	Node N = L->front;
	// free each node
	while(N != NULL) {
		Node T = N->next;
		N->next = NULL;
		N->prev = NULL;
		free(N);
		N = T;
	}
	L->front = NULL;
	L->back = NULL;
	L->length = 0;
}

Node getFront(List L) {
	if (L == NULL) {
		printf("Error: getFront() recieved a NULL input\n");
		exit(1);
	} else {
		return(L->front);
	}
	
}

Node getBack(List L) {
	if (L == NULL) {
		printf("Error: getBack() recieved a NULL input\n");
		exit(1);
	} else if (L->length == 0){
		printf("Warning: getBack() called for an empty list\n");
		exit(1);
	} else {
		return(L->back);
	}
}

Node getPrevNode(Node N) {
	if (N == NULL) {
		printf("Error: getPrevNode() recieved a NULL input\n");
		exit(1);
	} else {
		return(N->prev);
	}
}

Node getNextNode(Node N) {
	if (N == NULL) {
		printf("Error: getPrevNode() recieved a NULL input\n");
		exit(1);
	} else {
		return(N->next);
	}
}

void prepend(List L, int data) {
	Node New = malloc(sizeof(NodeObj));
	New->data = data;
	// special case: empty list
	if(L->length == 0) {
		New->next = NULL;
		New->prev = NULL;
		L->front = New;
		L->back = New;
	} else {
		New->next = L->front; // link new node to front
		New->prev = NULL; // nothing before new node
		L->front->prev = New; // link old front to new node
		L->front = New; // new node is now first
	}
	L->length++;
}

void append(List L, int data) {
	Node New = malloc(sizeof(NodeObj));
	New->data = data;
	// special case empty list
	if(L->length == 0) {
		New->next = NULL;
		New->prev = NULL;
		L->front = New;
		L->back = New;
	} else {
		New->next = NULL; // nothing after new node
		New->prev = L->back; // back node is new nodes prev
		L->back->next = New; // old back node's next node is new node
		L->back = New; // new node is now back
	}
	L->length++;
}

void insertBefore(List L, Node N, int data) {
	if (N != NULL) {
		if (N->prev == NULL) {
			prepend(L, data);
		} else if (L->length == 1) {
			append(L, data);
		} else {
			Node New = malloc(sizeof(NodeObj));
			New->data = data;
			New->prev = N->prev; // new node's prev is N's prev
			New->next = N; // new node's next is N
			N->prev->next = New; // new node is N's prev node's next
			N->prev = New; // N's prev node is now new
			L->length++;
		}
	}
}

void insertAfter(List L, Node N, int data) {
	if (N != NULL) {
		if (N->next == NULL) {
			append(L, data);
		} else if (L->length == 1) {
			prepend(L, data);
		} else {
			Node New = malloc(sizeof(NodeObj));
			New->data = data;
			New->prev = N; // new node's prev is N
			New->next = N->next; // new node's next is N's next
			N->next->prev = New; // new node is N's next node's prev
			N->next = New; // N's next node is now new
			L->length++;
		}
	}
}

void deleteFront(List L) {
	if (L->length > 0) {
		Node N = L->front;
		L->front = N->next;
		N->next->prev = NULL;
		free(N);
		L->length--;
	}
}

void deleteBack(List L) {
	if (L->length > 0) {
		Node N = L->back;
		L->back = N->prev;
		N->prev->next = NULL;
		free(N);
		L->length--;
	}
}

void detachNode(List L, Node N) {
    if (N == NULL)
        return;
    Node n = NULL;
    for (n = L->front; n != NULL; n = n->next) {
        if (n == N)
            break;
    }
    if (n == NULL)
        return;
    n = N->next;
    Node p = N->prev;
    if (n != NULL) {
        n->prev = p;
    }
    if (p != NULL) {
        p->next = n;
    }
    if (L->front == N) {
        L->front = n;
    }
    if (L->back == N) {
        L->back = p;
    }
    L->length -= 1;
}

// Other operations -----------------------------------------------------------

void printList(FILE *out, List L) {
    for (Node n = L->front; n != NULL; n = n->next) {
        fprintf(out, "%d ", n->data);
    }
    fprintf(out, "\n");
}

void deleteNode(List L, Node N) {
    detachNode(L, N);
    free(N);
    N = NULL;
}

int checkList (List L, int data) {
	if (L != NULL) {
		Node N = getFront(L);
		for (; N != NULL; N = N->next) {
			if (getValue(N) == data) {
				return(FOUND);
			}
		}
	}
	return(NOTFOUND);
}

void InsertSort(List L) {
	if (length(L) > 1) {
		int numcount = 0;
		Node np0 = getFront(L);
		Node np1 = getNextNode(np0);
		while(np1 != NULL) {
			int c = numcount;
			while(1) {
				if (getValue(np0) > getValue(np1)) {
					int data = getValue(np1);
					Node temp = np1;
					np1 = getNextNode(np1);
					deleteNode(L, temp);
					insertBefore(L, np0, data);
					break;
				} else if (c == 0) {
					np1 = getNextNode(np1);
					break;
				} else {
					np0 = getNextNode(np0);
					c--;
				}
			}
			np0 = getFront(L);
			numcount++;
		}
	}
}
