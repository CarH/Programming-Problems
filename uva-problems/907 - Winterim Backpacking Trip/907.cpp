#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<int> camp;

/**
 * 
 * f(d) : predicate function
 *	Aims to aswer the question: Can I reach the end of the trip walking 
 * at most d in a day?
 * 
 * @param d the maximum distance allowed
 * @return true, in case it's possible to do the trip walking at most d
 * 		in a day, false otherwise.
 */

bool f(int d) {
	int distance = 0; // The amount of distance walked so far
	int nights 	 = 0; // The number of nights slept in campsites so far

	if (d < camp[0]) return false;
	distance = camp[0]; // distance start -> first campsite
	for (int i = 1; i < camp.size(); i++) {
		if (distance + camp[i] <= d) {
			distance += camp[i];
		}
		else if (nights < k && distance <= d) {
			nights++;
			distance = camp[i];
		}
		else {
			return false;
		}
	}
	return true;
}

int binary_search(int lo=0, int hi=2160) {
	int mid=0;
	while (lo < hi) {
		mid = (hi+lo)/2;
		if (f(mid)) {
			hi = mid;
		}
		else {
			lo = mid+1; // This +1 is important!
		}
	}
	return lo;
}

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int value;
	while ( cin >> n >> k ) {
		for (int i = 0; i < n+1; i++) {
			cin >> value;
			camp.push_back(value);
		}
		cout << binary_search() << "\n";
		camp.clear();
	}
	return 0;
}