/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa1
* List.h
* Header file for List ADT
*/

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdio.h>

/* Exported Type */
typedef struct ListObj* List;

/* Constructors - Destructors ----------------------------------------------------------------- */
List newList();                     // returns a reference to a new empty List Object.
void freeList(List* pL);            // frees up the memory associated with List *pL and sets 
                                    // pL to NULL

/* Access Functions --------------------------------------------------------------------------- */
int front(List L);                  // returns element at the front of List "L"
                                    // PreCondition: !isEmpty(List)
int back(List L);                   // returns element at the back of List "L"
                                    // PreCondition: !isEmpty(List)
int length(List L);                 // returns the length of List "L" 
int index(List L);                  // returns index of the cursor element if defined on List 
                                    // "L", otherwise will return -1 
int get(List L);                    // returns the cursor element of L
                                    // PreConditions: !isEmpty(), index() >=0 
int equals(List A, List B);         // return True == 1 IFF List A and B are in same state
                                    //  otherwise return False == 0 

/* Manipulation Functions --------------------------------------------------------------------- */
void clear(List L);                 // Resets List L to an empty state. 
void set(List L, int x);            // Ovewrites the data at the cursor to the integer given x. 
                                    // PreConditions: length(L) > 0 and index() >= 0 
void moveFront(List L);             // If non-empty List "L", set the curser to the front element
                                    // otherwise do nothing 
void moveBack(List L);              // If non-empty List "L", set the curser to the back element
                                    // otherwise do nothing 
void movePrev(List L);              // If the cursor not at the front of L, move it one step to
                                    // the front of L. If cursor is at the front, it becomes
                                    // undefined. If the cursor is undefined do nothing.
void moveNext(List L);              // If the cursor is not at the back of L, move it one step to
                                    // the back of L. If cursor is at the back, it becomes
                                    // undefined. If the cursor is undefined do nothing.
void prepend(List L, int x);        // Insert new element into L, if L !empty then insert before
                                    // the first "front" element.
void append(List L, int x);         // Insert new element into L, if L !empty then insert after
                                    // the last "back" element. 
void insertBefore(List L, int x);   // Insert new element before the cursor.
                                    // PreConditions: index()>= 0 and length() > 0.
void insertAfter(List L, int x);    // Insert new element after cursor.
                                    // PreConditions: index()>= 0 and length() > 0.
void deleteFront(List L);           // Delete front element in L. PreConditions: Length() > 0
void deleteBack(List L);            // Delete back element in L.  PreConditions: Length() > 0
void delete(List L);                // Delete cursor element, cursor becomes undefined.
                                    // Preconditions: index()>= 0 and length() > 0.

/* Other Operations  -------------------------------------------------------------------------- */ 
void printList(FILE* out, List L);  // Prints the list to the file pointed to by the outFile
                                    // a string version of L consisting of space seperated 
                                    // integers with front on the left.
List copyList(List L);              // Returns a new list which represents the same sequence
                                    // of integers in "L." Cursor of the new list is undefined,
                                    // and the state of L is unchanged.
List concatList(List A, List B);    // returns a new list that is a concatination of Lists A and B
void combineLists(List A, List B);  // concatinations list A and list B, A is the new
                                    // combined list of A and B
#endif