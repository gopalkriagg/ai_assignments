#ifndef DECLARATIONS
#define DECLARATIONS

#include <set>
using namespace std;
struct compar;
class Tour;
int numCities;
void inputData(int & numCities, float ** & distanceMatrix);
void inputDistanceMatrix(float ** distanceMatrix, int numCities);
void brutus(float ** distanceMatrix, int numCities);
Tour constructStartTour(int numCities, float ** distanceMatrix);
Tour moveGen(Tour originalTour, float ** distanceMatrix);
void copy(Tour from, Tour & to, int numCities);

#endif