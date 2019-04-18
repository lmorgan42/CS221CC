// Traveling Salesman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "cities.h"
#include <iostream>
#include <fstream>
#include <numeric>

void testCities() {
	std::ifstream file("linear.tsv");
	Cities cities;
	file >> cities;
	std::cout << cities;
	std::cout << cities.total_path_distance({ 0,1,2 }) << "\n";
	auto city2 = cities.reorder({ 2,1,0 });
	std::cout << city2;
	auto city3 = cities.reorder(CitiesHelper::random_permutation(cities.coordSize()));
	std::cout << "3: " << city3;
	auto city4 = cities.reorder(CitiesHelper::random_permutation(cities.coordSize()));
	std::cout << "4: " << city4;
}

void randomSearch(std::string filename) {
	uint64_t iterations = 1000000;

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "file cannot be opened.";
		return;
	}
	Cities cities;
	file >> cities;
	Cities::permutation_t best = std::vector<unsigned int>(cities.coordSize());
	std::iota(best.begin(), best.end(), 0);
	Cities::permutation_t curr = std::vector<unsigned int>(cities.coordSize());
	
	for (uint64_t i = 0; i < iterations; ++i) {
		curr = CitiesHelper::random_permutation(cities.coordSize());
		if (cities.total_path_distance(curr) < cities.total_path_distance(best)) {
			best = curr;
			std::cout << i << "	" << cities.total_path_distance(best) << "\n";
		}
	}

	cities = cities.reorder(best);
	std::ofstream fileOut("shortest.tsv");
	fileOut << cities;
}

int main(int argc, char** args) {

	//testCities();
	if (argc != 2) {
		std::cerr << "Incorrect arguments, only provide one filename.";
		return 1;
	}
	randomSearch(args[1]);
	return 0;
}