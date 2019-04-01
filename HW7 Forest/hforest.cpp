#include "hforest.h"
#include <algorithm>

//Returns how many trees are in the forest
uint64_t HForest::size() const {
	return trees_.size();
}

//Takes a pointer to an HTree and adds it to the forest
void HForest::add_tree(HTree::tree_ptr_t tree) {
	trees_.push_back(tree);
}

bool compare_trees_(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
	return t1->get_value() < t2->get_value();
}

//Returns a pointer to the HTree with the highest value in the root node, and removes it from the forest
HTree::tree_ptr_t HForest::pop_tree() {
	std::make_heap(trees_.begin(), trees_.end(), compare_trees_);
	HTree::tree_ptr_t toRe = trees_.front();
	trees_.erase(trees_.begin());
	return toRe;
}

