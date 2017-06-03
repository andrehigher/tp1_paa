#ifndef BASE__H_
#define BASE__H_
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define FALSE 0
#define TRUE 1

void readInput(int argc, char *argv[]);
Graph* readNodes(FILE *fp);
void readEdges(Graph *graph, FILE *fp, FILE *fpwrite);
void printCombination(Graph *graph, int combination[][2], int total, FILE *fpwrite);

#endif /*BASE_H_*/