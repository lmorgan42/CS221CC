/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "pch.h"
#include "chromosome.h"
#include "deme.h"

#include <random>
#include <iostream>

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate) : 
	mut_rate_(mut_rate),
	generator_(rand())
{
	for (unsigned i = 0; i < pop_size; ++i) {
		pop_.insert(new Chromosome(cities_ptr));
	}
}

// Clean up as necessary
Deme::~Deme()
{
	while (pop_.size() > 0) {
		Chromosome* chrom = *pop_.begin();
		pop_.erase(chrom);
		delete chrom;
	}
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
	std::multiset<Chromosome*, compChromosomes> newPop;
	std::pair<Chromosome*, Chromosome*> parents;
	std::pair<Chromosome*, Chromosome*> children;

	while (newPop.size() < pop_.size()) {
		parents = select_parents();
		
		double mute = ((double)rand() / RAND_MAX);
		if (mute <= mut_rate_) parents.first->mutate();
		mute = ((double)rand() / RAND_MAX);
		if (mute <= mut_rate_) parents.second->mutate();

		children = parents.first->recombine(parents.second);
		newPop.insert(children.first);
		newPop.insert(children.second);
	}

	auto pos = pop_.begin();
	for (; pos != pop_.end(); ++pos) {
		delete *pos;
	}

	pop_ = newPop;
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
	return *pop_.begin();
}

// Randomly select two chromosomes in the population based on fitness and
// return a pointer to those chromosomes.
std::pair<Chromosome*, Chromosome*> Deme::select_parents()
{
	//make return pair
	std::pair<Chromosome*, Chromosome*> toRe;
	
	//calculate total fitness
	auto pos = pop_.begin();
	long long unsigned totalFit = 0;
	for (; pos != pop_.end(); ++pos) {
		totalFit += (*pos)->get_fitness();
	}
	
	//randomly select two different values out of the total fitness value
	auto first = (rand() * rand()) % totalFit;
	auto second = (rand() * rand()) % totalFit;
	while (second == first) {
		second = (rand() * rand()) % totalFit;
	}
	
	//figure out to which chromosomes those values correspond, accounting
	//for the possibility of both landing on one
	bool f = false;
	bool s = false;
	std::cout << "first: " << first << ", second: " << second << ", totalfit: " << totalFit << "\n";
	pos = pop_.begin();
	for (; pos != pop_.end(); ++pos) {
		if ((*pos)->get_fitness() <= totalFit) totalFit -= (*pos)->get_fitness();
		else totalFit = 0;
		std::cout << "totFit decreased to " << totalFit << "\n";
		if (!f && !s && (totalFit < first) && (totalFit < second)) {
			std::cout << "ran combined out.\n";
			toRe.first = *pos;
			++pos;
			toRe.second = *pos;
			f = true;
			s = true;
			break;
		}

		if (!f && totalFit < first) {
			std::cout << "ran first out.\n";
			toRe.first = *pos;
			f = true;
		}
		else if (!s && totalFit < second) {
			std::cout << "ran second out.\n";
			toRe.second = *pos;
			s = true;
		}

		if (f && s) break;

	}
	return toRe;
}
