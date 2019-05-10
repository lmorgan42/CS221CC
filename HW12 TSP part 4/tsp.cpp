/*
 * Main file for Traveling-Salesperson solver.
 * Read a cities file in TSV format into a Cities object, then run
 * of several solver algorithms on it and output the best result.
 */

#include "cities.h"
#include "deme.h"
#include "tournament_deme.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <numeric>
#include <mutex>
#include <thread>

//////////////////////////////////////////////////////////////////////////////
// Check whether a specific ordering reduces the total path distance in cities
// from a previous best distance. If so, print out the iteration number and
// new distance, update the best distance, and return true.
// Returns false if no improvement was found.
bool
is_improved(const Cities& cities,
            const Cities::permutation_t& ordering,
            double& best_dist)
{
  const auto dist = cities.total_path_distance(ordering);
  if (dist < best_dist) {
    //std::cout << iter << "\t" << dist << std::endl;
    best_dist = dist;
    return true;
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////////
// exhaustive_search searches niter randomized operdinges on the given cities
// The best cities permutation is returned.
Cities::permutation_t
randomized_search(const Cities& cities, uint64_t niter)
{
  auto best_ordering = Cities::permutation_t(cities.size());
  auto best_dist = 1e100;

  for (uint64_t i = 0; i < niter; ++i) {
    auto ordering = random_permutation(cities.size());
    if (is_improved(cities, ordering, best_dist)) {
      best_ordering = ordering;
    }
  }

  return best_ordering;
}

//////////////////////////////////////////////////////////////////////////////
// exhaustive_search searches every single permutation of the cities.
// The best cities permutation is returned.
Cities::permutation_t
exhaustive_search(const Cities& cities)
{
  auto ordering = Cities::permutation_t(cities.size());
  std::iota(ordering.begin(), ordering.end(), 0);
  auto best_ordering = ordering;
  auto best_dist = 1e100;
  uint64_t i = 0;

  do {
    i++;
    if (is_improved(cities, ordering, best_dist)) {
      best_ordering = ordering;
    }
  } while (std::next_permutation(ordering.begin(), ordering.end()));

  return best_ordering;
}


//void threadTask(const Cities& cities, unsigned iters, unsigned pop_size, double mutation_rate, std::vector<Cities::permutation_t>& ordering, std::mutex& myMutex) {
//	
//	//original code has been pasted here since now each thread runs its own deme
//	double best_dist = 1e100;
//	auto best_ordering = Cities::permutation_t(cities.size());
//
//	TournamentDeme deme(&cities, pop_size, mutation_rate);
//
//	// Evolve the population to make it fitter and keep track of
//	// the shortest distance generated
//	for (long i = 1; i <= iters / pop_size; ++i) {
//		deme.compute_next_generation();    // generate next generation
//
//		// Find best individual in this population
//		const auto ordering = deme.get_best()->get_ordering();
//		if (is_improved(cities, ordering, best_dist, i * pop_size)) {
//			best_ordering = ordering;
//		}
//	}
//	//aquire lock and "submit" best order
//	std::lock_guard<std::mutex> guard(myMutex);
//	ordering.push_back(best_ordering);
//}

//////////////////////////////////////////////////////////////////////////////
// ga_search uses a genetic algorithm to solve the traveling salesperson
// problem for a given list of cities.
// This function then creates a randomly generated population of permutations
// for traveling to those cities.
// The function also requires a population size and mutation rate.
// indicates how aggressively the population's individuals mutate.  The
// function then repeatedly evolves the population to generate increasingly
// better (i.e. shorter total distances) city permutations.
// The best cities permutation is returned.
Cities::permutation_t ga_search(const Cities& cities, unsigned iters, unsigned pop_size, double mutation_rate, int nThreads) {
	//create shared mutex
	std::mutex mutex;
	//to store best returned values
	std::vector<Cities::permutation_t> ordering;

	auto threadTask = [=, &mutex, &ordering]() {
		//original code has been pasted here since now each thread runs its own deme
		double best_dist = 1e100;
		auto best_ordering = Cities::permutation_t(cities.size());

		TournamentDeme deme(&cities, pop_size, mutation_rate);

		// Evolve the population to make it fitter and keep track of
		// the shortest distance generated
		for (long i = 1; i <= (iters / pop_size) / nThreads; ++i) {
			deme.compute_next_generation();    // generate next generation

			// Find best individual in this population
			const auto ordering = deme.get_best()->get_ordering();
			if (is_improved(cities, ordering, best_dist)) {
				best_ordering = ordering;
				std::lock_guard<std::mutex> guard(mutex);
				std::cout << "Best length: " << cities.total_path_distance(ordering) << "\n";
			}
		}
		//aquire lock and "submit" best order
		std::lock_guard<std::mutex> guard(mutex);
		ordering.push_back(best_ordering);
	};

	//create threads and start them
	std::vector<std::thread> threads;
	for (int i = 0; i < nThreads; ++i) {
		 threads.push_back(std::thread (threadTask));
	}

	for (unsigned i = 0; i < threads.size(); ++i) {
		threads[i].join();
	}

	Cities::permutation_t bestOrder = ordering[0];
	for (unsigned i = 0; i < ordering.size(); ++i) {
		if (cities.total_path_distance(ordering[i]) < cities.total_path_distance(bestOrder)) bestOrder = ordering[i];
	}
	return bestOrder;
}


//////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
  if (argc != 5) {
    std::cerr << "Required arguments: filename for cities, population size, mutation rate, and number of threads\n";
    return -1;
  }

  const auto cities = Cities(argv[1]);
  assert(cities.size() > 0 && "Did you actually read the input file successfully?");
  const auto pop_size = atoi(argv[2]);
  const auto mut_rate = atof(argv[3]);
  const auto nThreads = atoi(argv[4]);
  constexpr unsigned NUM_ITER = 100000;


//  const auto best_ordering = exhaustive_search(cities);
//  const auto best_ordering = randomized_search(cities, NUM_ITER);
  const auto best_ordering = ga_search(cities, NUM_ITER, pop_size, mut_rate, nThreads);
  std::cout << "Overall best distance: " << cities.total_path_distance(best_ordering) << "\n";

  auto out = std::ofstream("shortest.tsv");
  if (!out.is_open()) {
    std::cerr << "Can't open output file to record shortest path!\n";
    return -2;
  }

  out << cities.reorder(best_ordering);

  return 0;
}

