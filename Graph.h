/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa3
* Graph.h
* Header file for DFS Graph ADT
*/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include"List.h"
#include<stdio.h>

#define NIL -5
#define UNDEF -1
// Color Constants
#define BLACK 0  // Hexcode #000000
#define GREY  9  // Hexcode #999999
#define WHITE 15 // Hexcode #FFFFFF

/* Exported Type */
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n);      // creates a new Graph Object, allocates memory
                            // and default values for needed arrays

void freeGraph(Graph* pG);  // frees up allocated memory for Graph Object pG
                            // and sets pG == NULL

/*** Access functions ***/

int getOrder(Graph G);      // get the order of Graph G
                            // PRE: G != NULL

int getSize(Graph G);       // get the size of Graph G
                            // PRE: G != NULL

int getParent(Graph G, int u);          // get the parent vertex of the give vertex u
                                        // PRE: 1 <= u <= getOrder()

int getDiscover(Graph G, int u);        // get discover time of vertex u
                                        // PRE: 1 <= u <= getOrder()

int getFinish(Graph G, int u);         // get finish time of vertex u
                                        // PRE: 1 <= u <= getOrder()

/*** Manipulation procedures ***/

void makeNull(Graph G);                 // deletes all edges and arcs in Graph G

void addEdge(Graph G, int u, int v);    // inserts new edge from vertex u to vertex v
                                        // u and v are added to the adjacency lists for each other
                                        // PRE: 1 <= u <= getOrder(), 1 <= v <= getOrder() 

void addArc(Graph G, int u, int v);     // inserts new directed edge from vertex u to vertex v
                                        // the directed edge to the adjacency list of G from v to u
                                        // PRE: 1 <= u <= getOrder(), 1 <= v <= getOrder()

void DFS(Graph G, List S);              // Depth-First-Search Algorithm on Graph G with source List S to
                                        // define the order of vertices and for storage of vertices discovered
                                        // by time.

/*** Other operations ***/
Graph transpose(Graph G);               // returns a new graph object that is the transpose of graph G

Graph copyGraph(Graph G);               // returns a new graph objects that is a copy of graph G

void printGraph(FILE* out, Graph G);    // prints the adjacency List of graph G to the chose output file

#endif