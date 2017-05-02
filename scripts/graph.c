#include "../data_structure/base.h"

Graph *createGraph(int travelId, int passenger, int driver, int amount, int seats, float distance) {
    return createNode(travelId, passenger, driver, amount, seats, distance);
}
Graph* createNode(int travelId, int passenger, int driver, int amount, int seats, float distance) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->TravelId = travelId;
    graph->Passenger = passenger;
    graph->Driver = driver;
    graph->Amount = amount;
    graph->Seats = seats;
    graph->Distance = distance;
    graph->ListAdj = NULL;
    graph->Next = NULL;
    return graph;
}

void addNode(Graph *graph, int travelId, int passenger, int driver, int amount, int seats, float distance){
    Graph *aux = graph;
    Graph *newNode = createNode(travelId, passenger, driver, amount, seats, distance);
	while ( aux->Next != NULL ) {
		aux = aux->Next;
	}
	aux->Next = newNode;
}

void printGraph(Graph *graph) {
    Graph *aux = graph;
    while(aux != NULL) {
        printf("%d %d %d %d %d %f\n", aux->TravelId, aux->Passenger, aux->Driver, aux->Amount, aux->Seats, aux->Distance);
        aux = aux->Next;
    }
}
