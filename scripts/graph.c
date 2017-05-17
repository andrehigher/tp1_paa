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

ListAdj* createEdge(int destination) {
    ListAdj *list = (ListAdj *) malloc(sizeof(ListAdj));
    list->TravelId = destination;
    list->Next = NULL;
    return list;
}

void addEdge(Graph *graph, int source, int destination) {
    Graph *aux = graph;
    while(aux != NULL && aux->TravelId != source) {
        aux = aux->Next;
    }
    if(aux == NULL || aux->TravelId != source) {
        printf("Impossible to add an edge from %d to %d\n", source, destination);
        return;
    }
    insertEdge(aux, destination);
}

void insertEdge(Graph *node, int destination){
    ListAdj *newEdge = createEdge(destination);
    newEdge->Next = node->ListAdj;
    node->ListAdj = newEdge;
}

void printGraph(Graph *graph) {
    Graph *aux = graph;
    ListAdj *listAux;
    while(aux != NULL) {
        printf("%d %d %d %d %d %f\n", aux->TravelId, aux->Passenger, aux->Driver, aux->Amount, aux->Seats, aux->Distance);
        listAux = aux->ListAdj;
        printf("Edges:");
        while(listAux != NULL) {
            printf("%d->", listAux->TravelId);
            listAux = listAux->Next;
        }
        printf("NULL\n");
        aux = aux->Next;
    }
}

int calculateBenefit(Graph *graph, int source, int destination) {
    Graph *aux = graph;
    Graph *nodeSource = NULL, *nodeDestination = NULL;
    while(aux != NULL) {
        if(source == aux->TravelId){
            nodeSource = aux;
        }
        if(destination == aux->TravelId){
            nodeDestination = aux;
        }
        aux = aux->Next;
    }

    printf("nodeSource: %d %d %d %d %d %f\n", nodeSource->TravelId, nodeSource->Passenger, nodeSource->Driver, nodeSource->Amount, nodeSource->Seats, nodeSource->Distance);
    printf("nodeDestination: %d %d %d %d %d %f\n", nodeDestination->TravelId, nodeDestination->Passenger, nodeDestination->Driver, nodeDestination->Amount, nodeDestination->Seats, nodeDestination->Distance);
    if(nodeDestination->Amount + nodeSource->Amount <= nodeDestination->Seats) {
        nodeDestination->Amount += nodeSource->Amount;
        return nodeDestination->Amount;
    } else {
        return 0;
    }
}