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
#include "declarations.h"
#include "definitions.cpp"
using namespace std;


int main() {
	srand(time(NULL));
	float ** distanceMatrix;
	inputData(numCities, distanceMatrix); //numCities is a global variable (how to solve this?)
	brutus(distanceMatrix, numCities);
}


void brutus(float ** distanceMatrix, int numCities) {
	Tour tour;
	priority_queue<Tour, vector<Tour>, compar> open;
	
	tour = constructStartTour(numCities, distanceMatrix);
	open.push(tour);
	while(true) { 
		tour = open.top(); //Instead of first element any other random element could have been chosen too.
		
		open.push(moveGen(tour, distanceMatrix));
 		
 		tour = open.top();
 		tour.printTourCost();
 		
 		open.pop();open.pop();
 		open.push(tour);

 		//cout << open.size();    
	} 
}

