#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct _ListAdj {
    int TravelId;
    struct _ListAdj *Next;
}ListAdj;

typedef struct _Graph {
    int TravelId;
    int Passenger;
    int Driver;
    int Amount;
    int Seats;
    float Distance;
    ListAdj *ListAdj;
    struct _Graph *Next;
}Graph;

Graph* createGraph(int travelId, int passenger, int driver, int amount, int seats, float distance);
Graph* createNode(int travelId, int passenger, int driver, int amount, int seats, float distance);
void addNode(Graph *graph, int travelId, int passenger, int driver, int amount, int seats, float distance);
void printGraph(Graph *graph);

#endif /*GRAPH_H_*/