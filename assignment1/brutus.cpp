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
	vector<int> tour;
	vector<int> bestTourSoFar;
	float tourCost;
	set<vector<int>> open;
	set<vector<int>> closed;
	float minCostSoFar = numeric_limits<float>::max();
	
	tour = constructStartTour(numCities);
	open.insert(tour);
	while(!open.empty()) { //Alterate termination conditions: (closed.size() != maxPermutations)
		tour = *open.begin(); //Instead of first element any other random element could have been chosen too.
		
		tourCost = computeTourCost(tour, distanceMatrix, numCities);
		if(tourCost < minCostSoFar) {
			minCostSoFar = tourCost;
			bestTourSoFar = tour;
		}
		//cout << "Before erasing: " << open.size() << endl;
		open.erase(tour);
		//cout << "After erasing: " << open.size() << endl;
		closed.insert(tour);
		
		set<vector<int>> neighbours = moveGen(tour, numCities);


		set_difference(neighbours.begin(), neighbours.end(), closed.begin(), closed.end(), inserter(open, open.begin())); 
		//cout << endl;
		//printTour(tour, numCities);
		//cout << tourCost << endl;
		cout << open.size() << endl;
		//cout << closed.size() << endl;
	}
}

