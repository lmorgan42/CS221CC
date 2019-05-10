#pragma once

#include "deme.h"

class TournamentDeme : public Deme {
public:
	TournamentDeme(const Cities* cities_ptr , unsigned pop_size , double mut_rate ) : Deme(cities_ptr, pop_size, mut_rate) {}
	~TournamentDeme() = default;

protected:
	Chromosome* select_parent() override;
};