#include "huffman.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <assert.h>

Huffman::Huffman() {
	//remeber to check max values of int
	for (int i = 0; i < Huffman::ALPHABET_SIZE; i++) {
		//freq_.insert(std::pair<int, uint64_t>(i, 0));
		freq_.insert(std::make_pair(i, 0));
	}
}

HTree::tree_ptr_t createHForest(std::map<int, uint64_t> &freq) {
	HForest forest;

	//set HEOF to one
	std::map<int, uint64_t>::iterator it1 = freq.find(256);
	if (it1 != freq.end()) it1->second = 1;

	std::map<int, uint64_t>::iterator it;
	for (it = freq.begin(); it != freq.end(); ++it) {
		forest.add_tree(std::make_shared<const HTree>(
			HTree(it->first, it->second)));
	}
	assert(forest.size() == Huffman::ALPHABET_SIZE);

	while (forest.size() > 1) {
		std::shared_ptr<const HTree> treeL = forest.pop_tree();
		std::shared_ptr<const HTree> treeR = forest.pop_tree();
		forest.add_tree(std::make_shared<const HTree>(
			HTree(-1, treeL->get_value() + treeR->get_value(), treeL, treeR)));
	}
	return forest.pop_tree();
}

Huffman::bits_t Huffman::encode(int symbol) {
	HTree::tree_ptr_t tree = createHForest(freq_);
	HTree::path_t path = tree->path_to(symbol);
	Huffman::bits_t toRe;
	
	std::list<HTree::Direction> ::iterator it;
	for (it = path.begin(); it != path.end(); ++it){
		if (*it == HTree::Direction::LEFT) toRe.push_back(0);
		else toRe.push_back(1);
	}

	std::map<int, uint64_t>::iterator it1 = freq_.find(symbol);
	if (it1->second == UINT64_MAX) {
		std::cerr << "Symbol exceeded maximum count, file contains too many " << (char)symbol << "\n";
		throw("Symbol exceeded maximum count");
	}
	else {
		if (it1 != freq_.end()) it1->second = ++it1->second;
	}

	return toRe;
}

int Huffman::decode(bool bit) {
	bitBuffer_.push_back(bit);

	HTree::tree_ptr_t tree = createHForest(freq_);
	const HTree* curr = tree.get();
	for (uint32_t i = 0; i < bitBuffer_.size(); i++) {
		if (!bitBuffer_[i]) {
			if (curr->get_child(HTree::Direction::LEFT) == nullptr) {
				/*std::cerr << "Invalid left path attempted.";
				bitBuffer_.clear();
				return -2;*/
				return -2;
			}
			curr = (curr->get_child(HTree::Direction::LEFT)).get();
		}
		else {
			if (curr->get_child(HTree::Direction::RIGHT) == nullptr) {
				/*std::cerr << "Invalid right path attempted.";
				bitBuffer_.clear();
				return -2;*/
				return -2;
			}
			curr = (curr->get_child(HTree::Direction::RIGHT)).get();
		}
	}

	if (curr->get_key() < 0) return -1;
	
	bitBuffer_.clear();
	std::map<int, uint64_t>::iterator it1 = freq_.find(curr->get_key());
	if (it1->second == UINT64_MAX) {
		std::cerr << "Symbol exceeded maximum count, file contains too many " << (char)curr->get_key() << "\n";
		throw("Symbol exceeded maximum count");
	}
	else {
		if (it1 != freq_.end()) it1->second = ++it1->second;
	}
	
	return curr->get_key();
}