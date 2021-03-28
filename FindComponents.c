/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa3
* FindComponents.c
* Description
*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
    FILE* in;
    FILE* out;
    Graph G = NULL;
    Graph gT = NULL;
    List S = newList();
    List Trees = newList();
    int n, num1, num2, i, comp;
    int count = 0;
    // Ensure proper number of arguments
    if( argc != 3 ){
        printf("Usage: %d %s <input file> <output file>\n", argc,argv[0]);
        exit(EXIT_FAILURE);
    }
    // open input file for reading
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Error: Unable to read from input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    // open output file for writing
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Error: Unable to write to out file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    fscanf(in, "%d", &n);
    G = newGraph(n);
    num1 = -1;
    while(num1 != 0){
        fscanf(in, "%d %d", &num1, &num2);
        if(num1 != 0 && num2 != 0){
            addArc(G, num1, num2);
        }
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // create transpose of G and List S
    gT = transpose(G);
    for (i = 1; i<= n; i++){
        append(S, i);
    }
    //printf("List S: ");
    //printList(stdout, S);
    //printf("\nCopy of S: ");
    //printList(stdout, C);
    //printf("\nDFS on Graph Gives: \n");
    DFS(G, S);
    //printList(stdout, S);
    //printf("\nDFS on GraphT Gives: \n");
    DFS(gT, S);
    //printList(stdout, S);

    //get transpose DFS trees
    //printf("\nTranspose Parents and Vertices: \n");
    //printf("x: P\n");
    int p = 0;
    for (i = 1; i<= n; i++){
        p = getParent(gT, i);
        //printf("%d: %d\n", i, p);
        if (p == NIL){
            prepend(Trees, i);
        }
    }
    //printf("\n");
    //printList(stdout, Trees);
    //printf("\n");
    // separate strongly connected components within the DFS list output of gTranspose
    for(moveFront(S); index(S) >= 0; moveNext(S)){
        comp = get(S);
        for(moveFront(Trees); index(Trees) >= 0; moveNext(Trees)){
            if (comp == get(Trees)){
                insertBefore(S, 0);
                count++;
            }
        }
    }
    //printList(stdout, S);
    clear(Trees);
    comp = 0;
    fprintf(out, "\nG contains %d strongly connected components: ", count);
    for(moveBack(S); index(S) >= 0; movePrev(S)){
        num1 = get(S);
        if (num1 != 0){
            prepend(Trees, get(S));
        }
        if (num1 == 0){
            comp++;
            fprintf(out, "\nComponent %d: ", comp);
            printList(out, Trees);
            clear(Trees);
        }
    }
    printf("\n");
    freeGraph(&gT);
    freeGraph(&G);
    freeList(&S);
    freeList(&Trees);
    fclose(in);
    fclose(out);
    return 0;
}