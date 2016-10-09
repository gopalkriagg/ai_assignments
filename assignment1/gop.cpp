#include <vector>
#include <set>
#include <iostream>
using namespace std;
int main() {
	set<vector<int> > s;
	vector<int> v1 ={1,2,3,4};
	vector<int> v2 ={1,2,3,4};
	s.insert(v1);
	s.insert(v2);
	s.erase(v2);
	cout << s.size();
}