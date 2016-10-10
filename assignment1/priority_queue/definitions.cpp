#include <iostream>
#include <set>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>
using namespace std;



class Tour
{
public:
	vector<int> tour;
	float cost;
	Tour() {
		cost = 0;
	}
	float computeTourCost(float ** distanceMatrix) {
		cost = 0;
		int i;
		for(i = 0; i < tour.size()-1; i++)
			cost += distanceMatrix[tour[i]][tour[i+1]];
		cost += distanceMatrix[tour[i]][tour[0]]; //Completing the cycle
	}
	void printTour() {
		for(int i = 0; i < tour.size(); i++) {
			cout << tour[i] << " ";
		}
		cout << endl;
	}
	void printTourCost() {
		cout << "TOUR: ";
		for(int i = 0; i < tour.size(); i++) {
			cout << tour[i] << " ";
		}
		cout << endl;
		cout << "COST: " << cost << endl;
	}
};

struct compar
{
  bool operator()(const Tour& lhs, const Tour& rhs) const
  {
    return rhs.cost < lhs.cost;
  }
};

Tour moveGen(Tour originalTour, float ** distanceMatrix) {
	//Generate 3 random numbers within the range 0 to size of tour -1;
	int numCities = originalTour.tour.size();
	int a, b, c, d, e, f;
	a = rand() % numCities;
	b = rand() % numCities;
	c = rand() % numCities;
	d = rand() % numCities;
	e = rand() % numCities;
	f = rand() % numCities;
	//Pick 'cities' at these 3 indexes from tour and permute them in all possible ways and put them in a set.
	/*set<Tour> permuations;
	Tour tour = originalTour;	//1,2,3
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
	return permuations;*/
	Tour tour = originalTour;
	swap(tour.tour[b], tour.tour[c]);
	swap(tour.tour[a], tour.tour[d]);
	//swap(tour.tour[e], tour.tour[f]);
	tour.computeTourCost(distanceMatrix);
	//tour.printTourCost();
	return tour;
}



Tour constructStartTour(int numCities, float ** distanceMatrix) {
	Tour tour;
	for(int i = 0; i < numCities; i++)
		tour.tour.push_back(i);
	tour.computeTourCost(distanceMatrix);
	return tour; //The constructed tour is simply "01234...(numCities-1)"
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


