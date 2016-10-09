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


set<vector<int>> moveGen(vector<int> originalTour, int numCities) {
	//Generate 3 random numbers within the range 0 to size of tour -1;
	int a, b, c;
	a = rand() % numCities;
	b = rand() % numCities;
	c = rand() % numCities;
	//Pick 'cities' at these 3 indexes from tour and permute them in all possible ways and put them in a set.
	set<vector<int>> permuations;
	vector<int> tour = originalTour;	//1,2,3
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

float computeTourCost(vector<int> tour, float ** distanceMatrix, int numCities) {
	float cost = 0;
	int i;
	for(i = 0; i < numCities-1; i++)
		cost += distanceMatrix[tour[i]][tour[i+1]];
	cost += distanceMatrix[tour[i]][tour[0]]; //Completing the cycle
	return cost;
}

vector<int> constructStartTour(int numCities) {
	vector<int> tour;
	for(int i = 0; i < numCities; i++)
		tour.push_back(i);
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

void printTour(vector<int> tour, int numCities) {
	for(int i = 0; i < numCities; i++) {
		cout << tour[i] << "\t";
	}
}