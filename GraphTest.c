/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa3
* GraphTest.c
* Graph Client Test file for DFS Graph ADT
*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
   // below is from sample GraphClient.c
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   //personal Testing
   printf("\nNew Test");
   // copy and transpose Graph
   Graph H = NULL;
   Graph Trnp = NULL;
   int x, nOrd = 5;
   Graph g = newGraph(5);
   for(x=1; x<nOrd; x++) addArc(g, x, x+1);
   H = copyGraph(g);
   printGraph(stdout, g);
   printf(" Copy G\n");
   printGraph(stdout, H);
   printf(" Transpose G\n");
   Trnp = transpose(H);
   printGraph(stdout, Trnp);

   //Testing CombineLists
   printf("\n");
   List A = newList();
   List B = newList();
   append(A, 1);
   append(A, 2);
   append(A, 3);
   append(B, 4);
   append(B, 5);
   append(B, 6);
   combineLists(A, B);
   printList(stdout, A);
   printf("\n");

   freeList(&A);
   freeList(&B);
   freeGraph(&Trnp);
   freeGraph(&g);
   freeGraph(&H);
   return(0);
}
