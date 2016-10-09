#ifndef DECLARATIONS
#define DECLARATIONS

#include <set>
using namespace std;
struct compare;
int numCities;
void inputData(int & numCities, float ** & distanceMatrix);
void inputDistanceMatrix(float ** distanceMatrix, int numCities);
void brutus(float ** distanceMatrix, int numCities);
vector<int> constructStartTour(int numCities);
float computeTourCost(vector<int> tour, float ** distanceMatrix, int numCities);
set<vector<int>> moveGen(vector<int> originalTour, int numCities);
void printTour(vector<int> tour, int numCities);
void copy(vector<int> from, vector<int> & to, int numCities);

#endif