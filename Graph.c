/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa3
* Graph.c
* Implementation file for DFS Graph ADT
*/

#include "List.h"
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

/* GraphObj Type */
typedef struct GraphObj{
    List *vAdjs;   // array of adjacency list (vertices connected to vertices)
    int *color;
    int *parents;
    int *disc;     // array of discover time
    int *fin;      // array of finish time
    int size;
    int order;
    int finalTime; // final time value from Visit
} GraphObj;

/*** Constructors-Destructors ***/

//newGraph()
// creates new Graph Object and allocates memeory
// sets up default values as needed.
// default values: Distance = INF, parents = NIL
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->vAdjs = malloc((n+1) * sizeof(List));
    G->color = calloc(n, sizeof(int)+1);
    G->parents = calloc(n, sizeof(int)+1);
    G->disc = calloc(n, sizeof(int)+1);
    G->fin = calloc(n, sizeof(int)+1);
    for (int i = 0; i <= n; i++){ //setup default values
        G->disc[i] = UNDEF;
        G->fin[i] = UNDEF;
        G->parents[i] = NIL;
        G->vAdjs[i] = newList();
    }
    return G;
}

//freeGraph()
// frees up allocated memory for Graph Object pG
// and sets pG == NULL 
void freeGraph(Graph* pG){
    if( pG != NULL && *pG != NULL){
        //makeNull(*pG);
        //free memory of each array element within *pG
        for(int i = 0; i <= (*pG)->order; i++){
            if (i == 0) {
                free((*pG)->color);
                free((*pG)->parents);
                free((*pG)->disc);
                free((*pG)->fin);
            }
            freeList(&(*pG)->vAdjs[i]);
        }
        //freelist is only if the list gets populated
        freeList((*pG)->vAdjs); 
        free((*pG)->vAdjs);
        free(*pG);
        *pG = NULL;
    }
}

/*** Private Helper functions ***/

//Visit()
// private helper for DFS() function
// visits a vertex u and sets discover time
void Visit(Graph G, int u, int *time){
    int data;
    G->disc[u] = ++(*time);
    G->color[u] = GREY;
    //printf("\nTime is %d, Im on Vertex %d\n", *time, u);
    for(moveFront(G->vAdjs[u]); index(G->vAdjs[u]) >= 0; moveNext(G->vAdjs[u])){
        data = get(G->vAdjs[u]);
        if (G->color[data] == WHITE){
            G->parents[data] = u;
            Visit(G, data, time);
        }
    }
    G->color[u] = BLACK;
    G->fin[u] = ++(*time);
    G->finalTime = *time;
}

//saveFinTimes()
// store the finish times in increasing order
// into List S
void saveFinTimes(Graph G, List S){
    int ft = 0;
    int n;
    clear(S); //clear List S because we want to change the ordering of it
    n = getOrder(G);
    for (ft = 1; ft <= n; ft++) {
        if (length(S) == 0 || G->fin[back(S)] >= G->fin[ft]) {
            append(S, ft);
        } else //length > 0 so insert v into the list at the proper spot
        { // Finish List is in increasing order
           for(moveFront(S); index(S) >= 0; moveNext(S)){
               if (G->fin[get(S)] <= G->fin[ft]){
                    insertBefore(S, ft);
                    break;
               }
            }
        }
    }
    // end List sorting
}

/*** Access functions ***/

//getOrder();
// get the order of Graph G
// PRE: G != NULL
int getOrder(Graph G){
    if (G == NULL){
        printf("Graph Error: calling getOrder() on undefined Graph Object.");
        return(EXIT_FAILURE);
    }
    return G->order;
}

//getSize();
// get the size of Graph G
// PRE: G != NULL
int getSize(Graph G){
    if (G == NULL){
        printf("Graph Error: calling getSize() on undefined Graph Object.");
        return(EXIT_FAILURE);
    }
    return G->size;
}

//getParent();
// get the parent vertex of the give vertex u
// PRE: 1 <= u <= getOrder()
int getParent(Graph G, int u){
    if (u <= 0){
        printf("Graph Error: getParent() call on a vertex below or equal to 0 in Graph Object.");
        return(EXIT_FAILURE);
    }
    if (u > G->order){
        printf("Graph Error: getParent() call on a vertex greater than order of Graph Object.");
        return(EXIT_FAILURE);
    }
    return G->parents[u];
}

//getDiscover();
// get discover time of vertex u
// PRE: 1 <= u <= getOrder()
int getDiscover(Graph G, int u){
    if (u <= 0){
        printf("Graph Error: getDist() call on a vertex below or equal to 0 in Graph Object.");
        return(EXIT_FAILURE);
    }
    if (u > G->order){
        printf("Graph Error: getDist() call on a vertex greater than order of Graph Object.");
        return(EXIT_FAILURE);
    }
    return G->disc[u];
}

//getFinish();
// get finish time of vertex u
// PRE: 1 <= u <= Order(G)
int getFinish(Graph G, int u){
    if ( u < 1 ){
        printf("Graph Error: getPath() call on a vertex below or equal to 0 in Graph Object.");
        return(EXIT_FAILURE);
    }
    if (u > G->order){
        printf("Graph Error: getPath() call on a vertex greater than order of Graph Object.");
        return(EXIT_FAILURE);
    }
    return G->fin[u];
}

/*** Manipulation procedures ***/

//makeNull();
// deletes all edges in Graph G, clears adjacency lists
void makeNull(Graph G){
    for (int i = 0; i <= G->order; i++){
        clear(G->vAdjs[i]);
    }
}

//addEdge();
// inserts new edge from vertex u to vertex v
// uses addArc() in both directions to create an edge
// decrements size because arc added twice
// PRE: 1 <= u <= getOrder(), 1 <= v <= getOrder()
void addEdge(Graph G, int u, int v){
    // PRE is checked in addArc()
    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
}

//addArc();
// inserts new directed edge from vertex u to vertex v
// the directed edge to the adjacency list of G from v to u
// PRE: 1 <= u <= getOrder(), 1 <= v <= getOrder()
void addArc(Graph G, int u, int v){
    if ( u < 1 || v < 1){
        printf("Graph Error: getPath() call on a vertex below or equal to 0 in Graph Object.");
        exit(EXIT_FAILURE);
    }
    if (u > G->order || v > G->order){
        printf("Graph Error: getPath() call on a vertex greater than order of Graph Object.");
        exit(EXIT_FAILURE);
    }
    // Initial Sorting check
    if (length(G->vAdjs[u]) == 0 || back(G->vAdjs[u]) <= v) {
        append(G->vAdjs[u], v);
    } else //length > 0 so insert v into the list at the proper spot
    { // ADJ List is in increasing order
       for(moveFront(G->vAdjs[u]); index(G->vAdjs[u]) >= 0; moveNext(G->vAdjs[u])){
           if (get(G->vAdjs[u]) >= v){
               insertBefore(G->vAdjs[u], v);
               break;
           }
       }
    }
    G->size++;
}

//DFS();
// Depth-First-Search Algorithm on Graph G with source List S to
// define the order of vertices and for storage of vertices discovered
// by decreasing finish time.
void DFS(Graph G, List S){
    if (length(S) != getOrder(G)){
        printf("Graph or List Error: DFS() call with List length < Order of Graph G.");
        exit(EXIT_FAILURE);
    }
    int data;
    for (moveFront(S); index(S) >= 0; moveNext(S)){
        data = get(S);
        G->parents[data] = NIL;
        G->color[data] = WHITE;
    }
    int time = 0;
    for (moveFront(S); index(S) >= 0; moveNext(S)){
        data = get(S);
        if (G->color[data] == WHITE){
            Visit(G, data, &time);
        }
    }
    // append the List with vertices by finish times
    saveFinTimes(G, S);
}

/*** Other operations ***/

//transpose()
// returns a new graph object that is the transpose of graph G
// if G == NULL return NULL Graph
Graph transpose(Graph G){
    Graph transp = NULL;
    if (G == NULL){
        return transp;
    }
    int n, i, x;
    n = getOrder(G);
    transp = newGraph(n);
    for (i = 1; i <= n; i++){
        for (moveFront(G->vAdjs[i]); index(G->vAdjs[i]) >= 0; moveNext(G->vAdjs[i])){
            x = get(G->vAdjs[i]);
            append(transp->vAdjs[x], i); // append vertex I to adjList of x for every vertex in I of graph G
        }
    }
    return transp;
}

//copyGraph()
// creates a new graph that is an exact copy of graph G
// if G == NULL then return NULL graph
Graph copyGraph(Graph G){
    Graph copy = NULL;
    if (G == NULL){
        return copy;
    }
    int i;
    int n = getOrder(G);
    copy = newGraph(n);
    // populate arrays within copy
    for (i = 1; i <= n; i++){
        copy->disc[i] = G->disc[i];
        copy->fin[i] =  G->fin[i];
        copy->parents[i] =  G->parents[i];
        for(moveFront(G->vAdjs[i]); index(G->vAdjs[i]) >= 0; moveNext(G->vAdjs[i])){
            append(copy->vAdjs[i], get(G->vAdjs[i]));
        }
    }
    copy->size = G->size;
    return copy;
}

//printGraph();
// prints the adjacency List of graph G to the chosen output file
void printGraph(FILE* out, Graph G){
    /* Check if List is NULL */
    if (G == NULL){
        printf("Graph Error: calling printGraph() on NULL Graph Reference.\n");
        exit(EXIT_FAILURE);
    }
    /* Print data to out file */
    for (int i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d: ", i);
        printList(out, G->vAdjs[i]);
        fprintf(out, "\n");
    }
}