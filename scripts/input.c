#include <stdio.h>
#include <stdlib.h>
#include "../data_structure/base.h"
#include "../data_structure/graph.h"

/**
*   
*/
void readInput(int argc, char *argv[]){
    int travels, sharing;
    int i;
    int travel_id, passenger, driver, amount, seats;
    float distance;
    int sharing1, sharing2;

    if(argc < 3){
        printf("This program needs to receive the input and output.\n");
        return;
    }

    FILE *fp;

    fp = fopen(argv[1], "r");

    if(!fp) {
        printf("%s doesn't exist.\n", argv[1]);
        return;
    }

    fscanf(fp, "%d", &travels);
    for (i=0; i<travels; i++) {
        fscanf(fp, "%d %d %d %d %d %f", &travel_id, &passenger, &driver, &amount, &seats, &distance);
        printf("%d %d %d %d %d %f\n", travel_id, passenger, driver, amount, seats, distance);
    }
    printf("\n");

    fscanf(fp, "%d", &sharing);
    for (i=0; i<sharing; i++) {
        fscanf(fp, "%d %d", &sharing1, &sharing2);
        printf("%d %d\n", sharing1, sharing2);
    }
    printf("\n");

    fclose(fp);
}