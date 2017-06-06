#include "../data_structure/base.h"

void readInput(int argc, char *argv[]){
    FILE *fp, *fpwrite;
    Graph *graph;

    if(argc < 3){
        printf("This program needs to receive the input and output.\n");
        return;
    }

    fp = fopen(argv[1], "r");
    fpwrite = fopen(argv[2], "w");

    if(!fp) {
        printf("%s doesn't exist.\n", argv[1]);
        return;
    }
    float maxBenefit = 0;
    graph = readNodes(fp);
    readEdges(graph, fp, fpwrite, &maxBenefit);
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

void readEdges(Graph *graph, FILE *fp, FILE *fpwrite, float *maxBenefit){
    int i, sharing;
    int source, destination;
    fscanf(fp, "%d", &sharing);
    int combination[sharing][2];
    int arr[sharing];
    for (i=0; i<sharing; i++) {
        arr[i] = i;
        fscanf(fp, "%d %d", &source, &destination);
        addEdge(graph, source, destination);
        combination[i][0] = source;
        combination[i][1] = destination;
    }

    int r;
    int n = sizeof(arr)/sizeof(arr[0]);
    for(r=1;r<=sharing; r++) {
        printCombinationAux(arr, n, r, graph, combination, maxBenefit);
    }
    // old method
    // printCombination(graph, combination, sharing, fpwrite);
}

void printCombination(Graph *graph, int combination[][2], int total, FILE *fpwrite) {
    int i, j, k, l, hash[total];
    float benefit, auxBenefit, bestBenefit = 0;
    int bestCombination[total][2], auxCombination[total][2];

     for (i=0; i<total; i++) {
        bestCombination[i][0] = -1;
        bestCombination[i][1] = -1;
        auxCombination[i][0] = -1;
        auxCombination[i][1] = -1;
     }

    for (i=0; i<total; i++) {
        l=0;
        benefit = 0;
        if (checkPassengerAvailability(graph, combination[i][0]) != 0) {
            auxCombination[l][0] = combination[i][0];
            auxCombination[l][1] = combination[i][1];
            l++;
            resetAvaiableSeats(graph);
            benefit = calculateBenefit(graph, combination[i][0], combination[i][1]);
            for (k=0; k<total; k++) {
                hash[k] = 0;
            }
            hash[combination[i][0]] = 1;
            hash[combination[i][1]] = 2;
            for (j=i+1;j<total;j++){
                if(checkPassengerAvailability(graph, combination[j][0]) != 0) {
                    if(hash[combination[j][0]] == 0 && (hash[combination[j][1]] == 0 || hash[combination[j][1]] == 2)) {
                        auxBenefit = calculateBenefit(graph, combination[j][0], combination[j][1]);
                        if(auxBenefit > 0) { 
                            hash[combination[j][0]] = 1;
                            hash[combination[j][1]] = 2;
                            auxCombination[l][0] = combination[j][0];
                            auxCombination[l][1] = combination[j][1];
                            l++;
                            benefit += auxBenefit;
                        }
                    }
                }
            }
            for (j=0;j<i;j++){
                if(checkPassengerAvailability(graph, combination[j][0]) != 0) {
                    if(hash[combination[j][0]] == 0 && (hash[combination[j][1]] == 0 || hash[combination[j][1]] == 2)) {
                        auxBenefit = calculateBenefit(graph, combination[j][0], combination[j][1]);
                        if(auxBenefit > 0) { 
                            hash[combination[j][0]] = 1;
                            hash[combination[j][1]] = 2;
                            auxCombination[l][0] = combination[j][0];
                            auxCombination[l][1] = combination[j][1];
                            l++;
                            benefit += auxBenefit;
                        }
                    }
                }
            }
        }
        if(benefit > bestBenefit) {
            for (j=0; j<total; j++) {
                bestCombination[j][0] = -1;
                bestCombination[j][1] = -1;
            }

            for (j=0; j<total; j++) {
                if(auxCombination[j][0] > 0 ) {
                    bestCombination[j][0] = auxCombination[j][0];
                    bestCombination[j][1] = auxCombination[j][1];
                }
            }

            rewind(fpwrite);
            bestBenefit = benefit;
            int leia = 0;
            int juju[total];
            for(j=0; j<total; j++) {
               juju[j] = -1; 
            }
            for (j=0;j<total;j++) {
                if(bestCombination[j][0] > 0 && bestCombination[j][1] > 0) {
                    if(juju[bestCombination[j][1]] == -1) {
                        juju[bestCombination[j][1]] = 1;
                        leia++;
                    }
                }
            }
            fprintf(fpwrite, "%d %.1f\n", leia, bestBenefit);
            for (j=0;j<total;j++) {
                if(bestCombination[j][0] > 0 && bestCombination[j][1] > 0) {
                    fprintf(fpwrite, "%d ", bestCombination[j][1]);
                    for (l=0;l<total;l++) {
                        if(bestCombination[l][1] == bestCombination[j][1]) {
                            fprintf(fpwrite, "%d ", bestCombination[l][0]);
                            bestCombination[l][0] = -1;
                        }
                    }
                    auxCombination[j][1] = -1;
                    fprintf(fpwrite, "\n");
                }
            }
        }
    }
    if(bestBenefit == 0) {
        fprintf(fpwrite, "0 0.0");
    }
    fclose(fpwrite);
}

void printCombinationAux(int arr[], int n, int r, Graph *graph, int combination[][2], float *maxBenefit) {
    // A temporary array to store all combination one by one
    int data[r];
 
    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, data, 0, n-1, 0, r, graph, combination, maxBenefit);
}

void combinationUtil(int arr[], int data[], int start, int end, int index, int r, Graph *graph, int combination[][2], float *maxBenefit) {
    // Current combination is ready to be printed, print it
    if (index == r)
    {
        float benefit = 0, auxBenefit = 0;
        resetAvaiableSeats(graph);
        for (int j=0; j<r; j++) {
            if(checkPassengerAvailability(graph, combination[j][0]) == 1 && checkDriverAvailability(graph, combination[j][1]) == 1 && checkIsDriving(graph, combination[j][0]) == 0 && checkAvailability(graph, combination[j][0]) == 1 && checkSeats(graph, combination[j][0], combination[j][1]) == 1) {
                setTravel(graph, combination[j][0], combination[j][1]);
                benefit += calculateBenefit(graph, combination[j][0], combination[j][1]);
            }
        }
        if(benefit > *maxBenefit) {
            *maxBenefit = benefit;
            printf("\n\nFOUND MAX BENEFIT\n");
            printf("benefit: %.1f\n", benefit);
            resetAvaiableSeats(graph);
            for (int j=0; j<r; j++) {
                if(checkPassengerAvailability(graph, combination[j][0]) == 1 && checkDriverAvailability(graph, combination[j][1]) == 1 && checkAvailability(graph, combination[j][0]) == 1 && checkSeats(graph, combination[j][0], combination[j][1]) == 1) {
                    setTravel(graph, combination[j][0], combination[j][1]);
                    benefit += calculateBenefit(graph, combination[j][0], combination[j][1]);
                    printf("index: %d\t %d -> %d\n", data[j], combination[j][0], combination[j][1]);
                }
            }
        }
        return;
    }
 
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r, graph, combination, maxBenefit);
    }
}