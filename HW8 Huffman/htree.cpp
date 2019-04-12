#include "htree.h"
#include <assert.h>
#include <memory>

int HTree::get_key() const {
	return HTree::key_;
}

uint64_t HTree::get_value() const {
	return HTree::value_;
}

HTree::tree_ptr_t HTree::get_child(HTree::Direction dir) const {
	if (dir == HTree::Direction::LEFT) {
		return HTree::left_;
	}
	return HTree::right_;
}

void pathHelper(HTree::tree_ptr_t tree, int key, bool* found, HTree::path_t* tore) {
	if (tree->get_key() == key) {
		*found = true;
		return;
	}
	if (tree->get_child(HTree::Direction::LEFT) != nullptr) {
		pathHelper(tree->get_child(HTree::Direction::LEFT), key, found, tore);
		if (*found) {
			tore->push_front(HTree::Direction::LEFT);
			return;
		}
	}
	if (tree->get_child(HTree::Direction::RIGHT) != nullptr) {
		pathHelper(tree->get_child(HTree::Direction::RIGHT), key, found, tore);
		if (*found) {
			tore->push_front(HTree::Direction::RIGHT);
			return;
		}
	}
	return;
}

void doNothing() {
	return;
}


// path_to: return a list representing the path taken from a given tree root
// to a given key in the tree. For each left child taken along the path, the
// string contains an 'L' character, and 'R' for a right child, in order.
// If the key isn't found in the tree, path_to should abort the program using an
// assert() call.
// If multiple matches to key exist in the tree, return the path to the
// leftmost match. For the tree above, path_to(tree, 12) returns "LL".
HTree::path_t HTree::path_to(int key) const {
	HTree::path_t toRe;
	if (key_ == key) return toRe;
	bool found = false;
//	pathHelper(std::shared_ptr<const HTree>(this), key, &found, &toRe);
	pathHelper(left_, key, &found, &toRe);
	if (found) {
		toRe.push_front(HTree::Direction::LEFT);
	}
	else {
		pathHelper(right_, key, &found, &toRe);
		if (found) {
			toRe.push_front(HTree::Direction::RIGHT);
		}
	}
	assert(found);
	return toRe;
}