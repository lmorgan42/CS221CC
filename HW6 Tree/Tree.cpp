#include "tree.hh"
#include <assert.h>

// create_tree allocates space for a new tree node and fills it with the given
// data parameters. By default, the tree is a leaf, so its children point to
// nullptr, but you may override with actual pointers to other nodes.
tree_ptr_t create_tree(const key_t& key, const value_t& value, tree_ptr_t left, tree_ptr_t right) {
	tree_ptr_t tree = new Tree({ key, value, left, right });
	return tree;
}

// Deallocate all space consumed by this tree and its children.
void destroy_tree(tree_ptr_t tree) {
	if (tree->left_ != nullptr) {
		destroy_tree(tree->left_);
	}
	if (tree->right_ != nullptr) {
		destroy_tree(tree->right_);
	}
	delete tree;
}

void pathHelper(tree_ptr_t tree, key_t key, bool* found, std::string* toRe) {
	if (tree->key_ == key) {
		*found = true;
		return;
	}
	if (tree->left_ != nullptr) {
		pathHelper(tree->left_, key, found, toRe);
		if (*found) {
			*toRe = "L" + *toRe;
			return;
		}
	}
	if (tree->right_ != nullptr) {
		pathHelper(tree->right_, key, found, toRe);
		if (*found) {
			*toRe = "R" + *toRe;
			return;
		}
	}
	return;
}

// path_to: return a string representing the path taken from a given tree root
// to a given key in the tree. For each left child taken along the path, the
// string contains an 'L' character, and 'R' for a right child, in order.
// If the key isn't found in the tree, path_to should abort the program using an
// assert() call.
// If multiple matches to key exist in the tree, return the path to the
// leftmost match. For the tree above, path_to(tree, 12) returns "LL".
std::string path_to(tree_ptr_t tree, key_t key) {
	bool found = false;
	std::string toRe = "";
	pathHelper(tree, key, &found, &toRe);
	assert(found);
	return toRe;
}

// node_at: Follow a path from a given root node and return the node that is
// at the end of the path.
// If the path leads to an invalid or empty child, or contains any character
// other than 'L' or 'R', return nullptr (don't crash)
tree_ptr_t node_at(tree_ptr_t tree, std::string path) {
	
	for (char next : path) {
		if (next == 'L' && tree->left_ != nullptr) {
			tree = tree->left_;
		}
		else if (next == 'R' && tree->right_ != nullptr) {
			tree = tree->right_;
		}
		else {
			return nullptr;
		}
	}
	return tree;
}
