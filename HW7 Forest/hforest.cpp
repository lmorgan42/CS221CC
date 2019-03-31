#include "hforest.h"
#include <algorithm>

//Returns how many trees are in the forest
uint64_t HForest::size() const {
	return trees.size();
}

//Takes a pointer to an HTree and adds it to the forest
void HForest::add_tree(HTree::tree_ptr_t tree) {
	trees.push_back(tree);
}

bool compare_trees(HTree::tree_ptr_t t1, HTree::tree_ptr_t t2) {
	return t1->get_value() < t2->get_value();
}

//Returns a pointer to the HTree with the highest value in the root node, and removes it from the forest
HTree::tree_ptr_t HForest::pop_tree() {
	std::make_heap(trees.begin(), trees.end(), compare_trees);
	HTree::tree_ptr_t toRe = trees.front();
	trees.erase(trees.begin());
	return toRe;
}

