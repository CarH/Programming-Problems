#include <iostream>		// fixed
#include <iomanip>		// setprecision
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string desc;
	int prev_distance		= 0,
		curr_distance		= 0,
		fuel_consumption	= 0,
		num_leaks			= 0,
		delta_s				= 0;
	double tank_volume 		= 0.0,
		smallest_tank_volume= 0.0;

	while ( cin >> curr_distance ) {
		cin >> desc;

		delta_s 	= (curr_distance - prev_distance);
		tank_volume += ( (delta_s * (double)num_leaks) + ((double)fuel_consumption * (delta_s/(double)100)));
 		
		smallest_tank_volume = max (smallest_tank_volume, tank_volume);
		prev_distance = curr_distance;
		
		if ( !desc.compare("Fuel") ) {
			cin >> desc >> fuel_consumption;
		}
		else if ( !desc.compare("Leak") ) {
			num_leaks++;
		}
		else if ( !desc.compare("Mechanic") ) {
			num_leaks = 0;
		}
		else if ( !desc.compare("Gas") ) {
			cin.ignore(10, '\n');
			tank_volume = 0;
		}
		else if ( !desc.compare("Goal") ) {
			cout << fixed;
			cout << setprecision(3) << smallest_tank_volume << "\n";

			// Prepare for the next input doesn't start with wrong data
			// from a previous test case
			smallest_tank_volume = 0;
			prev_distance = 0;
			tank_volume = 0;
			num_leaks = 0;
		}
	}
	return 0;
}