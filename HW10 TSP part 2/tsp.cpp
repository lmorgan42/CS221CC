// Traveling Salesman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "cities.h"
#include "deme.h"
#include "chromosome.h"
#include <iostream>
#include <fstream>
#include <numeric>

bool is_improved(const Cities& cities, const Cities::permutation_t& ordering, double& best_dist, uint64_t iter){
	const auto dist = cities.total_path_distance(ordering);
	if (dist < best_dist) {
		std::cout << iter << "\t" << dist << std::endl;
		best_dist = dist;
		return true;
	}
	return false;
}

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

void basicGA(Cities cities, unsigned popCount, double mutate) {
	auto best_ordering = Cities::permutation_t(cities.coordSize());
	auto best_dist = cities.total_path_distance(best_ordering);
	unsigned iters = 100;


	Deme deme(&cities, popCount, mutate);

	// Evolve the population to make it fitter and keep track of
	// the shortest distance generated
	for (long i = 1; i <= iters / popCount; ++i) {
		deme.compute_next_generation();    // generate next generation

		// Find best individual in this population
		const auto ordering = deme.get_best()->get_ordering();
		if (is_improved(cities, ordering, best_dist, i * popCount)) {
			best_ordering = ordering;
		}
	}
	
	auto out = std::ofstream("shortest.tsv");
	if (!out.is_open()) {
		std::cerr << "Can't open output file to record shortest path!\n";
	}

	Cities temp = cities.reorder(best_ordering);
	out << temp;
}

int main(int argc, char** args) {

	//testCities();
	if (argc != 2 && argc != 4) {
		std::cerr << "Incorrect arguments, only provide one filename.";
		return 1;
	}
	if (argc == 2) randomSearch(args[1]);
	else if (argc == 4) {
		std::ifstream file(args[1]);
		if (!file.is_open()) {
			std::cerr << "file cannot be opened.";
			return -1;
		}
		Cities cities;
		file >> cities;
		const auto pop_size = atoi(args[2]);
		const auto mut_rate = atof(args[3]);
		basicGA(cities, pop_size, mut_rate);
	}
	return 0;
}