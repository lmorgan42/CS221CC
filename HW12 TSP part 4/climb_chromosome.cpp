#include "climb_chromosome.h"

#include <cassert>
#include <algorithm>

void ClimbChromosome::mutate() {
	std::vector<double> fitness(order_.size());
	std::vector<Cities::permutation_t> orders(order_.size());
	fitness[0] = get_fitness();
	orders[0] = order_;
	
	std::uniform_int_distribution<int> dist(0, order_.size() - 1);
	int p = dist(generator_);

	orders[1] = orders[0];
	auto temp = p - 1;
	if (p - 1 < 0) temp = order_.size() - 1;
	std::swap(orders[1][p], orders[1][temp]);

	orders[2] = orders[0];
	std::swap(orders[2][p], orders[2][(p + 1) % order_.size()]);
	
	order_ = orders[std::distance(fitness.begin(), std::max_element(fitness.begin(), fitness.end()))];

	assert(is_valid());
}