/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa1
* List.c
* Implementation file for List ADT
*/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

/* structs defaulted all private */
typedef struct NodeObj{
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

/* Node Alias for NodeObj */
typedef NodeObj* Node;

/* ListObj Type */
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

/* Constructors - Destructors ------------------------------------------------------------ */

/* newNode() 
*  returns a reference to a new initialized Node obj
*  based on newNode in Queue.c for CSE101 */
Node newNode(int d){
    Node N = malloc(sizeof(NodeObj));
    N->data = d;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}
/* freeNode()
*  returns a reference to a new initialized Node obj
*  based on freeNode Queue.c for CSE101 */
void freeNode(Node* pN){
    if( pN != NULL && *pN!= NULL){
        free(*pN);
        *pN = NULL;
    }
}
/* newList() 
*  returns a reference to a new initialized List obj
*  based on newQueue in Queue.c for CSE101 */
List newList() {
    List L;
    L =  malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}
/* freeList() 
*  frees memory allocated with every node inside List pL and the list itself
*  based on freeQueue in Queue.c for CSE101 */
void freeList(List* pL){
    if ( pL != NULL && *pL != NULL ){
        while( length(*pL) > 0 ) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

/* Access Functions ------------------------------------------------------------ */

// front()
//returns the data element at front of List L
//PRE: List != NULL
int front(List L){
    if (L == NULL){
        printf("List Error: calling front() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}
// back()
// returns the data element at the back of List L
// PRE: List != NULL
int back(List L){
    if (L == NULL){
        printf("List Error: calling back() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}
// length()
// returns the length of List L
// PRE: List != NULL
int length(List L){
    if (L == NULL){
        printf("List Error: calling length() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
}
// index()
// returns the index of the cursor in List L
// PRE: Cursor != NULL
int index(List L){
    if (L->cursor == NULL){
        return -1;
    }
    return L->index;
}
// index()
// returns the index of the cursor in List L
// PRE: List != NULL && index() >= 0
int get(List L){
    /*PreCondition If Statements*/
    if(L == NULL){
        printf("List Error: calling get() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling get() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /*Get current node and return its data*/
    return L->cursor->data;
}
// equals()
// returns 1 (true) IFF List A == List B 
// PRE: List A != NULL && List B != NULL
int equals(List A, List B){
    if (A == NULL || B == NULL){ /*if either list is NULL exit with error */
        printf("List Error: calling equals() with a NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    int equal = 0; /* default to false "0" */
    Node F = A->front;
    Node N = B->front;
    
    equal = (A->length == B->length); /* if lengths are not same return false "0"*/
    /* look at each data point until they are not equal or lists end */
    while(F!=NULL && N!=NULL && equal > 0){
        if (F->data != N->data){ equal = 0; } /* if data is NOT equal flag*/
        F = F->next;
        N = N->next;
    }
    return equal;
}

/* Manipulation Functions ------------------------------------------------------------- */

// clear()
// deletes all elements and frees nodes in a list
// PRE: length() > 0
void clear(List L){
    while(length(L) > 0){
        deleteFront(L);
    }
}
// set()
// overwrites the data at the cursor
// PRE: length() > 0 && index() >= 0
void set(List L, int x){
    if(L == NULL){
        printf("List Error: calling set() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling set() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}
// moveFront()
// moves the Cursor of L to the front node in the list
// PRE: length() > 0
void moveFront(List L){
    if (L != NULL){
        L->cursor = L->front;
        L->index = 0;
    }
}
// moveBack()
// moves the Cursor of L to the last node in the list
// PRE: length() > 0
void moveBack(List L){
    if (L != NULL){
        L->cursor = L->back;
        L->index = length(L) - 1; /* length is always +1 the index*/
    }
}
// movePrev()
// moves the Cursor of L to the previous Node otherwise do nothing
// PRE: index() >= 0 
void movePrev(List L){
    if (L->cursor != NULL){ /* Only do something if cursor != NULL */
        /* if at front already then cursor is set to undefined*/
        if (L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
        else{ /* move cursor 1 step to front */
            L->cursor = L->cursor->prev;
            L->index -= 1;
        }
    }
}
// moveNext()
// moves the Cursor of L to the next Node otherwise do nothing
// PRE: index() >= 0 
void moveNext(List L){
    if (L->cursor == NULL){ return; }

    /* if at back already then cursor is set to undefined*/
    if (L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
    else{ /* move cursor 1 step to back */
        L->cursor = L->cursor->next;
        L->index++;
        }
}
// prepend()
// adds a new node to the front of List L
// PRE: List != NULL 
void prepend(List L, int x){
    if (L == NULL){
        printf("List Error: calling prepend() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if(L->front == NULL && L->back == NULL){ /* if L isEmpty() */
        L->front = L->back = N;
    }else{
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
    }
    L->length++;
    L->index++;
}
// append()
// adds a new node to the back of List L
// PRE: List != NULL 
void append(List L, int x){
    if (L == NULL){
        printf("List Error: calling append() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->front == NULL && L->back == NULL){ /* if L isEmpty() */
        L->front = L->back = N;
    }else{ /*if L !isEmpty() then set N prev to the back and L->back to N*/
        L->back->next = N; /* current last elements "next" to N */
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}
// insertBefore()
// adds a new node before the location of Cursor in List L
// PRE: List != NULL && index() >= 0
void insertBefore(List L, int x){
    if(L == NULL){
        printf("List Error: calling insertBefore() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling insertBefore() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /* Check to see if cursor is current at front to make things easier. */
    if (L->cursor == L->front) {prepend(L, x); return;};
    /* Otherwise, Insert before wherever cursor is*/
    Node temp = newNode(x);
    temp->next = L->cursor;
    temp->prev = L->cursor->prev;
    L->cursor->prev = temp;
    temp->prev->next = temp;
    L->index++;
    L->length++;
}
// insertAfter()
// adds a new node after the location of Cursor in List L
// PRE: List != NULL && index() >= 0
void insertAfter(List L, int x){
    if(L == NULL){
        printf("List Error: calling insertAfter() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling insertAfter() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /* Check to see if cursor is current at back to make things easier. */
    if (L->cursor == L->back ) {append(L, x); return;};
    /* Otherwise, Insert before wherever cursor is*/
    Node temp = newNode(x);
    temp->next = L->cursor->next;
    temp->prev = L->cursor;
    L->cursor->next = temp;
    temp->next->prev = temp;
    L->length++;
}
// deleteFront()
// deletes the first (front) node in the List
// PRE: List != NULL
void deleteFront(List L){
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->front){ /* If cursor points at Front its now undefined*/
        L->cursor = NULL;
        L->index = 0; //index will be decremented below
    }
    if (length(L) == 1){
        freeNode(&L->front);
        L->back = NULL;
        L->index -= 1;
        L->length -=1;
        return;
    }
    /* Set oldFront Node to free up the current front and set L->front */
    Node oldFront = NULL;
    oldFront = L->front;
    L->front = L->front->next;
    freeNode(&oldFront);
    L->front->prev = NULL;
    L->index -=1;
    L->length-=1;
}
// deleteBack()
// deletes the last (back) node in the List
// PRE: List != NULL
void deleteBack(List L){
    if(L == NULL){
        printf("List Error: calling deleteBack() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->back){ /* If cursor points at back its now undefined*/
        L->cursor = NULL;
        L->index = -1;
    }
    if(length(L) == 1){ /* Special Case for deleteBack on singular List*/
        freeNode(&L->back);
        L->front = NULL;
        L->index = -1;
        L->length -= 1;
        return;
    }
    /* Set oldBack Node to free up the current back and set L->back */
    Node oldBack = NULL;
    oldBack = L->back;
    L->back = L->back->prev;
    freeNode(&oldBack);
    L->back->next = NULL;
    L->length -= 1;
}
// delete()
// deletes node at cursor and cursor is now undefined
// PRE: List != NULL && index() >= 0
void delete(List L){
    if(L == NULL){
        printf("List Error: calling delete() on NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling delete() with an undefined Cursor\n");
        exit(EXIT_FAILURE);
    }
    /* Check to see if cursor is current at front or back to make things easier. */
    if (L->cursor == L->front) {deleteFront(L); return;};
    if (L->cursor == L->back ) {deleteBack(L); return;};
    /* Otherwise */
    /* Cursors Previous Nodes "Next" is Cursors Next Node. "Keep the List intact"*/
    L->cursor->prev->next = L->cursor->next;
    freeNode(&L->cursor); /*freeNode should set cursor = Null and free memory*/
    L->index = -1; /*Undefined Cursor Index set*/
    L->length -= 1;
}

/* Other Functions ----------------------------------------------------------------------- */

// printList()
// writes data in List to a file
// PRE: List != NULL
void printList(FILE* out, List L){
    /* Check if List is NULL */
    if (L == NULL){
        printf("List Error: calling printList() on NULL List Reference.\n");
        exit(EXIT_FAILURE);
    }
    /* Print data to out file */
    Node temp = NULL;
    for (temp = L->front; temp != NULL; temp = temp->next){
        fprintf(out, "%d ", temp->data);
    }
}
// copyList()
// copies the data of a list to a new one and returns the copy
List copyList(List L){
    List copy = newList();
    Node temp = L->front;
    while (length(copy) != length(L)){
        append(copy, temp->data);
        temp = temp->next;
    }
    return copy;
}
// concatList()
// returns a new list that is a concatination of List A and B
List concatList(List A, List B){
    List combined = newList();
    Node temp = A->front;
    while (length(combined) != length(A)){
        append(combined, temp->data);
        temp = temp->next;
    }
    temp = B->front;
    while (temp != NULL){
        append(combined, temp->data);
        temp = temp->next;
    }
    return combined;
}

//combineLists()
// combines List A and B
void combineLists(List A, List B){
    for (moveFront(B); index(B) >= 0; moveNext(B)){
        append(A, get(B));
    }
}