

#include <ostream>
#include <cassert>
#include "tournament_deme.h"

Chromosome* TournamentDeme::select_parent() {
	//select power of two less than size of population
	int counter = -1;
	unsigned int temp = 1;
	while (temp <= pop_.size()) {
		temp *= 2;
		counter += 1;
	}
	
	int p = pow(2, (counter - (int)(counter / 3)) % (counter + 1));
	assert(p % 2 == 0);

	//randomly select populace to fill selection vector

	std::vector<ClimbChromosome*> selected;
	std::vector<ClimbChromosome*> population = pop_;
	unsigned rand;
	std::vector<ClimbChromosome*>::iterator it;

	for (int i = 0; i < p; ++i) {
		rand = generator_() % population.size();
		selected.push_back(population[rand]);
		it = population.begin() + rand;
		population.erase(it);
	}

	//keep pitting chromosomes against each other until one remains

	while (selected.size() > 1) {
		for (unsigned i = 0; i < (selected.size() / 2); ++i) {
			if (selected[i]->get_fitness() > selected[i + 1]->get_fitness()) {
				it = selected.begin() + i + 1;
				selected.erase(it);
			}
			else {
				it = selected.begin() + i;
				selected.erase(it);
			}
		}
	}

	//return the one
	assert(selected.size() == 1);
	return selected[0];
}