#include <iostream>
#include <algorithm>	// copy
#include <map>			// map
#include <queue>		// priority_queue

#define N 4
using namespace std;

// 2-connected neighbors - LEFT and RIGHT
int d[2] = { -1, 1 };

struct State {
	vector<int> conf;		// The 4-digit integer displayed
	int cost;				// g(n) : # of steps up to this node
	int fn;					// f(n) = g(n) + h(n)
	State *parent;			// To build the path

	State(){}

	State(vector<int> &a_conf, vector<int> &goal, int c=0) {
		conf = a_conf;
		cost = c;
		fn   = get_fn(goal);
	}

	// Heuristic function
	int get_fn(vector<int> &goal) {
		int acc=0;
		for (int i = 0; i < N; i++) {
			int ma = max(goal[i], conf[i]);
			int mi = min(goal[i], conf[i]);
			acc   += min((ma-mi), (10-(ma-mi)));
		}
		return (acc + cost);
	}

	bool compare(vector<int> &c) {
		for (int i = 0; i < N; i++) {
			if (conf[i] != c[i])
				return false;
		}
		return true;
	}

	void print_path() {
		State *ptr = this;
		while ( ptr != NULL ) {
			ptr->print();
			ptr = ptr->parent;
		}
		return;
	}

	void print() {
		cout << "-------------------\n  Printing State\n-------------------\n";
		cout << "  > g(n): " << cost << "\n";
		cout << "  > f(n): " << fn << "\n";
		cout << "  > Configuration:\n";
		for (vector<int>::iterator it = conf.begin(); it != conf.end(); it++) {
			cout << "  " << *it; 
		}
		cout << "\n-------------------\n";
	}
};

struct StateCompare {
	bool operator() (State &s1, State &s2) const {
		return s1.fn > s2.fn;
	}
};

// Collector of dynamic memory's addresses associated to structs created
vector<State*> collector;
void free_dynamic_memory() {
	for (vector<State*>::iterator it = collector.begin(); it != collector.end(); it++) {
		delete *it;
	}
	collector.clear();
}

int a_star_search(State &initial, vector<vector<int> > &forbidden, vector<int> &goal) {
	priority_queue<State, vector<State>, StateCompare> frontier;
	map<vector<int>, bool > explored;

	// Mark all forbidden configurations as explored, to avoid enqueuing invalid states
	for (vector<vector<int> >::iterator it = forbidden.begin(); it != forbidden.end(); it++)
		explored[*it] = true;

	frontier.push(initial);
	while ( !frontier.empty() ) {
		State curr = frontier.top();
		frontier.pop();

		// Check if it's reached the goal configuration
		if ( !explored.count(curr.conf) ) {
			// Insert the vertex on the explored list
			explored[curr.conf] = true;

			if (curr.compare(goal)) {
				free_dynamic_memory();
				return curr.cost;
			}

			// for each digit of the current configuration 
			for (int i = 0; i < N; i++) {
				
				// Move to the LEFT and to the RIGHT
				for (int j = 0; j < 2; j++) { 
					vector<int> new_conf(N);
					copy(curr.conf.begin(), curr.conf.end(), new_conf.begin());
					
					// Perform a move
					new_conf[i] += d[j];
					// When new_conf[i] = -1 that means 0 -> 9, so fix it to 9
					new_conf[i] = (new_conf[i]  < 0 ) ? 9 : new_conf[i];
					// When new_conf[i] = 10 that means 9 -> 1, so fix it to 1
					new_conf[i] = (new_conf[i] == 10) ? 0 : new_conf[i];

					// If the state has not been explored, enqueue it
					if ( !(explored.count(new_conf)) ) {
						State new_state (new_conf, goal, (curr.cost+1));
						new_state.parent 	= new State();
						*(new_state.parent) = curr;
						frontier.push(new_state);
						collector.push_back(new_state.parent);
					}
				}
			}
		}
	}
	free_dynamic_memory();
	return -1;
}

int main(int argc, char const *argv[])
{
	int n, m, value;
	// target configuration
	vector<int> target(N);
	// start configuration
	vector<int> start(N);
	
	while ( cin >> n ) {
		// for each test case
		for (int i = 0; i < n; i++) {
			// Get the initial configuration
			for (int j = 0; j < N; j++) {
				cin >> start[j];
			}
			// Get the target configuration
			for (int j = 0; j < N; j++) {
				cin >> target[j];
			}

			// Get the number of forbidden configurations
			cin >> m;

			// Read forbidden configurations
			vector< vector<int> > forbidden; 
			for (int k = 0; k < m; k++) {
				vector<int> v;
				forbidden.push_back(v);
				for (int l = 0; l < N; l++) {
					cin >> value;
					forbidden[k].push_back(value);
				}
			}
			// Create the initial state
			State goal(target, start, 0);
			goal.parent = NULL;
			cout << a_star_search(goal, forbidden, start) << "\n";
		}
	}
	return 0;
}