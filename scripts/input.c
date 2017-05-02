#include "../data_structure/base.h"

/**
*   
*/
void readInput(int argc, char *argv[]){
    FILE *fp;

    if(argc < 3){
        printf("This program needs to receive the input and output.\n");
        return;
    }

    fp = fopen(argv[1], "r");

    if(!fp) {
        printf("%s doesn't exist.\n", argv[1]);
        return;
    }
    readNodes(fp);
    readEdges(fp);
    fclose(fp);
}

void readNodes(FILE *fp){
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
    printGraph(head);
    printf("\n");
}

void readEdges(FILE *fp){
    int i, sharing;
    int sharing1, sharing2;
    fscanf(fp, "%d", &sharing);
    for (i=0; i<sharing; i++) {
        fscanf(fp, "%d %d", &sharing1, &sharing2);
        printf("%d %d\n", sharing1, sharing2);
    }
    printf("\n");
}