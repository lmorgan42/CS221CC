#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// calculates where the edge of the circle would lie along each row of points
// this is used later to determine how many points would fall inside the circle
void calculateCutoffs(unsigned points, vector<double>& cutoffs) {
	for (unsigned i = 0; i < points; i++) {
		double temp = sqrt(pow((points - 1), 2) - pow(i, 2));
		cutoffs[i] = temp;
		//cout << "Cutoff " << i << ": " << temp << "\n";
	}
}

// uses the edge point of the circle provided by calculateCuttoffs to count the number of points that lie inside the circle
int countPoints(unsigned points, vector<double>& cutoffs) {
	int insidePoints = 0;
	for (double point : cutoffs) {
		insidePoints += static_cast<int>(point);
	}
	insidePoints += points + 1;
	return insidePoints;
}

//uses the total number of points and points inside the "circle" to estimate pi
double estimatePi(unsigned points, int insidePoints) {
	return 4 * (double(insidePoints) / double(pow(points, 2)));
}

//estimates pi by creating a grid of points and checking to see whether or not they are in a unit circle
double gridpi(unsigned npoints){
	vector<double> cutoffs;
	cutoffs.resize(npoints);
	calculateCutoffs(npoints, cutoffs);
	return estimatePi(npoints, countPoints(npoints, cutoffs));
}

//provides user interface and calls other methods
void helper() {
	unsigned points;
	cout << "How many points do you want to use?\n>";
	cin >> points;
	cout << "Your estimate with " << points << " points is " << gridpi(points) << endl;
}

int main(){
	helper();
	return 0;
}
