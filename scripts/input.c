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
    int combination[sharing][2];
    for (i=0; i<sharing; i++) {
        fscanf(fp, "%d %d", &source, &destination);
        addEdge(graph, source, destination);
        combination[i][0] = source;
        combination[i][1] = destination;
    }
    printCombination(graph, combination, sharing);
    // printGraph(graph);
}

void printCombination(Graph *graph, int combination[][2], int total){
    int i, j, k, hash[total];
    int benefit;

    for (i=0; i<total; i++) {
        benefit = 0;
        printf("%d -> %d\n", combination[i][0], combination[i][1]);
        benefit = calculateBenefit(graph, combination[i][0], combination[i][1]);
        for (k=0; k<total; k++) {
            hash[k] = 0;
        }
        hash[combination[i][0]] = 1;
        for (j=i+1;j<total;j++){
            if(combination[j][1] != combination[i][0] && hash[combination[j][1]] == 0 && hash[combination[j][0]] == 0){
                hash[combination[j][0]] = 1;
                printf("%d -> %d\n", combination[j][0], combination[j][1]);
                benefit = calculateBenefit(graph, combination[j][0], combination[j][1]);
            }
        }
        printf("benefit: %d\n", benefit);
        printf("****\n");
    }
}