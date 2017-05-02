#include "../data_structure/base.h"

/**
*   
*/
void readInput(int argc, char *argv[]){
    FILE *fp;
    Graph *graph;

    if(argc < 3){
        printf("This program needs to receive the input and output.\n");
        return;
    }

    fp = fopen(argv[1], "r");

    if(!fp) {
        printf("%s doesn't exist.\n", argv[1]);
        return;
    }
    graph = readNodes(fp);
    readEdges(graph, fp);
    printf("\n");
    fclose(fp);
}

Graph* readNodes(FILE *fp){
    int travels;
    int i;
    int travelId, passenger, driver, amount, seats;
    float distance;

    fscanf(fp, "%d", &travels);
    fscanf(fp, "%d %d %d %d %d %f", &travelId, &passenger, &driver, &amount, &seats, &distance);
    Graph *head = createGraph(travelId, passenger, driver, amount, seats, distance);
        
    for (i=1; i<travels; i++) {
        fscanf(fp, "%d %d %d %d %d %f", &travelId, &passenger, &driver, &amount, &seats, &distance);
        addNode(head, travelId, passenger, driver, amount, seats, distance);
    }
    return head;
}

void readEdges(Graph *graph, FILE *fp){
    int i, sharing;
    int source, destination;
    fscanf(fp, "%d", &sharing);
    for (i=0; i<sharing; i++) {
        fscanf(fp, "%d %d", &source, &destination);
        addEdge(graph, source, destination);
    }
    printGraph(graph);
}