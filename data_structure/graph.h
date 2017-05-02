#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct _AdjList {
    int TravelId;
    int Passenger;
    int Driver;
    int Amount;
    int Seats;
    float Distance;
    struct _AdjList *next;
}AdjList;

#endif /*GRAPH_H_*/