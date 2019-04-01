#pragma once
#include "htree.hh"
#include <vector>

class HForest {
private:
	std::vector<HTree::tree_ptr_t> trees_;

public:
	uint64_t size() const;
	void add_tree(HTree::tree_ptr_t tree);
	HTree::tree_ptr_t pop_tree();

	HForest() = default;
	~HForest() = default;
};