#ifndef DECLARATIONS
#define DECLARATIONS

#include <set>
using namespace std;
struct compare;
int numCities;
void inputData(int & numCities, float ** & distanceMatrix);
void inputDistanceMatrix(float ** distanceMatrix, int numCities);
void brutus(float ** distanceMatrix, int numCities);
int * constructStartTour(int numCities);
float computeTourCost(int * tour, float ** distanceMatrix, int numCities);
set<int *, compare> moveGen(int * originalTour, int numCities);
void printTour(int * tour, int numCities);
void copy(int * from, int * & to, int numCities);

#endif