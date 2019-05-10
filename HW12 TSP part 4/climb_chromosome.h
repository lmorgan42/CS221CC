#pragma once

#include "chromosome.h"

class ClimbChromosome : public Chromosome {
public:
	void mutate();

	ClimbChromosome(const Cities* city) : Chromosome(city) {}

	 Chromosome* clone() const
	{
		return new ClimbChromosome(*this);
	}
};