#include "htree.hh"
#include "test_htree.h"
#include <assert.h>
#include <iostream>
#include <string>

/*
void testCreateDestroyChildren() {
	tree_ptr_t child2 = create_tree(3, 4);
	tree_ptr_t child1 = create_tree(2, 3);
	tree_ptr_t head = create_tree(1, 2, child1, child2);
	destroy_tree(head);
	std::cout << "Test destroying children successful.\n";
}
*/

std::string convertPathList(HTree::path_t l);

void testPathFinding() {
	/*
	creates a tree as such
		 1
		/ \
	   2   3
	  /   / \
	 4   4   7
	/   /
	5  9
	 \
	  6
	each element is named after its layer then its position from left to right
	*/
	HTree::tree_ptr_t l4c1 = std::shared_ptr<const HTree>(new HTree(6, 1));
	HTree::tree_ptr_t l3c1 = std::shared_ptr<const HTree>(new HTree(5, 1, nullptr, l4c1));
	HTree::tree_ptr_t l3c2 = std::shared_ptr<const HTree>(new HTree(9, 1));
	HTree::tree_ptr_t l2c1 = std::shared_ptr<const HTree>(new HTree(4, 1, l3c1));
	HTree::tree_ptr_t l2c2 = std::shared_ptr<const HTree>(new HTree(4, 1, l3c2));
	HTree::tree_ptr_t l2c3 = std::shared_ptr<const HTree>(new HTree(7, 1));
	HTree::tree_ptr_t l1c1 = std::shared_ptr<const HTree>(new HTree(2, 1, l2c1));
	HTree::tree_ptr_t l1c2 = std::shared_ptr<const HTree>(new HTree(3, 1, l2c2, l2c3));
	HTree::tree_ptr_t head = std::shared_ptr<const HTree>(new HTree(1, 1, l1c1, l1c2));

	std::cout << "\nTesting path finding...\n";
	std::cout << "Find 6, expected LLLR got " + convertPathList(head->path_to(6)) << std::endl;
	std::cout << "Find 7, expected RR got " + convertPathList(head->path_to(7)) << std::endl;
	std::cout << "Find 4, expected LL got " + convertPathList(head->path_to(4)) << std::endl;
	std::cout << "Find 9, expected RLL got " + convertPathList(head->path_to(9)) << std::endl;
	std::cout << "Find 1, expected  got " + convertPathList(head->path_to(1)) << std::endl;
	/*
	std::cout << "Testing retreival...\n";
	std::cout << "Find LLLR, expected 6 got " << (node_at(head, "LLLR")->key_) << std::endl;
	std::cout << "Find RR, expected 7 got " << (node_at(head, "RR")->key_) << std::endl;
	std::cout << "Find LL, expected 4 got " << (node_at(head, "LL")->key_) << std::endl;
	std::cout << "Find RLL, expected 9 got " << (node_at(head, "RLL")->key_) << std::endl;
	std::cout << "Find , expected 1 got " << (node_at(head, "")->key_) << std::endl;
	std::cout << "Find RRL, expected nullptr got " << (node_at(head, "RRL")) << std::endl;
	std::cout << "Find ABC, expected nullptr got " << (node_at(head, "ABC")) << std::endl;
	*/

	std::cout << "Testing complete\n";
}

std::string convertPathList(HTree::path_t l) {
	std::string toRe = "";
	for (HTree::Direction dir : l) {
		if (dir == HTree::Direction::LEFT){
			toRe += "Left, ";
		}
		else {
			toRe += "Right, ";
		}
	}
	toRe = toRe.substr(0, toRe.size() - 2);
	return toRe;
}

void testTree() {
	testPathFinding();
}

int main(){
	testTree();
	return 0;
}