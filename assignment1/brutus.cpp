/*
tour <- some random tour.
min_cost_so_far <- Cost(tour);
set.add(tour);
repeat until set.size < (tour.length-1)!:
	tour <- Random_change(tour)
	if(set.exists(tour)) continue;
	tour_cost <- Cost(tour)
	if(tour_cost < min_cost_so_far)
		min_cost_so_far = tour_cost;
	set.add(tour);
*/



#include <iostream>
#include <set>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>
using namespace std;


void inputData(int & numCities, float ** & distanceMatrix);
void inputDistanceMatrix(float ** distanceMatrix, int numCities);
void brutus(float ** distanceMatrix, int numCities);
string constructStartTour(int numCities);
float computeTourCost(string tour);
set<string> moveGen(string tour);

int main() {
	srand(time(NULL));
	int numCities;
	float ** distanceMatrix;
	inputData(numCities, distanceMatrix);

	brutus(distanceMatrix, numCities);
/*	for(int i = 0; i < numCities; i++) {
		for(int j = 0; j < numCities; j++) {
			cout << distanceMatrix[i][j] << "\t";
		}
		cout << endl;
	}*/
}

/*
OPEN <- {some_random_tour}
min_cost_so_far = INF
repeat until CLOSED.size != (tour.length)!:
	tour <- select_random_element_from_set(OPEN);
	tour_cost <- Cost(tour)
	if(tour_cost < min_cost_so_far)
		min_cost_so_far = tour_cost;
		best_tour_so_far = tour;
	OPEN <- OPEN\{tour}
	CLOSED <- CLOSED U {tour}
	OPEN <- OPEN U {MoveGen(tour)\CLOSED}
	print(min_cost_so_far)

MoveGen(tour):

*/
float computeTourCost(string tour, float ** distanceMatrix) {
	float cost = 0;
	int i;
	for(i = 0; i < tour.size()-1; i++)
		cost += distanceMatrix[tour[i]-'0'][tour[i+1]-'0'];
	cost += distanceMatrix[tour[i]-'0'][tour[0]-'0']; //Completing the cycle
	return cost;
}

string constructStartTour(int numCities) {
	string tour;
	for(int i = 0; i < numCities; i++)
		tour += i+'0';
	return tour; //The constructed tour is simply "01234...(numCities-1)"
}

set<string> moveGen(string originalTour) {
	//Generate 3 random numbers within the range 0 to size of tour -1;
	int a, b, c;
	a = rand() % originalTour.size();
	b = rand() % originalTour.size();
	c = rand() % originalTour.size();
	//Pick 'cities' at these 3 indexes from tour and permute them in all possible ways and put them in a set.
	set<string> permuations;
	string tour = originalTour;	//1,2,3
	swap(tour[b], tour[c]); //1,3,2
	permuations.insert(tour);
	swap(tour[a], tour[b]); //3,1,2
	permuations.insert(tour);
	swap(tour[b], tour[c]); //3,2,1
	permuations.insert(tour);
	swap(tour[a], tour[b]); //2,3,1
	permuations.insert(tour);
	swap(tour[a], tour[b]); //2,1,3
	permuations.insert(tour);
	return permuations;
}

void brutus(float ** distanceMatrix, int numCities) {
	string tour;
	string bestTourSoFar;
	int tourCost;
	set<string> open;
	set<string> closed;
	float minCostSoFar = numeric_limits<float>::max();
	
	tour = constructStartTour(numCities);
	
	open.insert(tour);
	while(open.size() != 0) { //Alterate termination conditions: (closed.size() != maxPermutations)
		tour = *open.begin(); //Instead of first element any other random element could have been chosen too.
		
		tourCost = computeTourCost(tour, distanceMatrix);
		if(tourCost < minCostSoFar) {
			minCostSoFar = tourCost;
			bestTourSoFar = tour;
		}
		
		open.erase(tour);
		closed.insert(tour);
		
		set<string> neighbours = moveGen(tour);

		/*set<string> neighboursNotInClosed;
		set_difference(neighbours.begin(), neighbours.end(), closed.begin(), closed.end(), neighboursNotInClosed.begin()); 
		set_union(open.begin(), open.end(), neighboursNotInClosed.begin(), neighboursNotInClosed.end(), open.begin());
		*/
		set_difference(neighbours.begin(), neighbours.end(), closed.begin(), closed.end(), inserter(open, open.begin())); 

		cout << minCostSoFar << endl;
	}
}

void inputData(int & numCities, float ** & distanceMatrix) {
	string dump; //To dump useless lines in input file
	getline(cin, dump);

	cin >> numCities; //Input number of cities in file

	getline(cin, dump); //To dump newline character
	for(int i = 0; i < numCities; i++)
		getline(cin, dump); //Dump next numCities number of lines where each line is coordinates of each city which is not needed right now.

	//Allocate memory for distanceMatrix
	distanceMatrix = new float*[numCities];
	for(int i = 0; i < numCities; i++) 
		distanceMatrix[i] = new float[100];

	inputDistanceMatrix(distanceMatrix, numCities);
}

void inputDistanceMatrix(float ** distanceMatrix, int numCities) {
	for(int i = 0; i < numCities; i++) {
		for(int j = 0; j < numCities; j++) {
			cin >> distanceMatrix[i][j];
		}
	}
}