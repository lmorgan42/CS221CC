#include <iostream>
#include <array>
#include <cmath>

using namespace std;

constexpr unsigned npoints = 100;

// calculates where the edge of the circle would lie along each row of points
// this is used later to determine how many points would fall inside the circle
constexpr void calculateCutoffs(array<double, npoints>& cutoffs) {
	for (unsigned i = 0; i < npoints; ++i) {
		double temp = sqrt(pow((npoints - 1), 2) - pow(i, 2));
		cutoffs[i] = temp;
		const_cast<int&>(static_cast<std::array<int, H> const&>[j])
		//cout << "Cutoff " << i << ": " << temp << "\n";
	}
}

// uses the edge point of the circle provided by calculateCuttoffs to count the number of points that lie inside the circle
constexpr int countPoints(array<double, npoints>& cutoffs) {
	int insidePoints = 0;
	for (unsigned i = 0; i < npoints; ++i) {
		insidePoints += static_cast<int>(cutoffs[i]);
	}
	insidePoints += npoints + 1;
	return insidePoints;
}

//uses the total number of points and points inside the "circle" to estimate pi
constexpr double estimatePi(int insidePoints) {
	return 4 * (double(insidePoints) / double(pow(npoints, 2)));
}

//estimates pi by creating a grid of points and checking to see whether or not they are in a unit circle
constexpr double gridpi() {
	array<double, npoints> cutoffs = { 0 };
	calculateCutoffs(cutoffs);
	return estimatePi(countPoints(cutoffs));
}

//provides user interface and calls other methods
void helper() {
	cout << "Your estimate with " << npoints << " points is " << gridpi() << "\n";
}

int main() {
	helper();
	return 0;
}
