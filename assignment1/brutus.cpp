/* Basic algo:
OPEN <- {some_random_tour}
min_cost_so_far = INF
repeat until OPEN.size != 0:
	tour <- select_random_element_from_OPEN;
	tour_cost <- Cost(tour)
	if(tour_cost < min_cost_so_far)
		min_cost_so_far = tour_cost;
		best_tour_so_far = tour;
	OPEN <- OPEN\{tour}
	CLOSED <- CLOSED U {tour}
	OPEN <- OPEN U {MoveGen(tour)\CLOSED}
	print(min_cost_so_far)
*/

#include <iostream>
#include <set>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>
#include <queue>
#include <cmath>
#include "declarations.h"
#include "definitions.cpp"
using namespace std;


bool choose(float probability) {
	float r = ((double) rand() / (RAND_MAX));
	if(r <= probability)
		return true;
	else return false;
}

int main() {
	srand(time(NULL));
	float ** distanceMatrix;
	inputData(numCities, distanceMatrix); //numCities is a global variable (how to solve this?)
	brutus(distanceMatrix, numCities);
}


void brutus(float ** distanceMatrix, int numCities) {
	Tour tour = constructStartTour(numCities, distanceMatrix);
	Tour bestTourSoFar = tour;
	Tour newTour;
	float deltaE;
	float probability;
	for(float T = 1000; T > 0 ; T -= 0.001) { //T denotes temperature
		do {
			newTour = moveGen(tour, distanceMatrix);
			deltaE = newTour.cost - tour.cost;
			probability = 1.0/(1.0 + exp(deltaE/T));
			//cout << "P: " << probability << endl;
		}while(!choose(probability));
		
		tour = newTour;
		if(tour.cost < bestTourSoFar.cost) {
			bestTourSoFar = tour;
			bestTourSoFar.printTourCost();
		} 
	}
}

