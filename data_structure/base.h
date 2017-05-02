#ifndef BASE__H_
#define BASE__H_
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define FALSE 0
#define TRUE 1

void readInput(int argc, char *argv[]);
void readNodes(FILE *fp);
void readEdges(FILE *fp);

#endif /*BASE_H_*/