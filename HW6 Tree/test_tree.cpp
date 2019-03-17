#include "tree.hh"
#include <assert.h>
#include <iostream>

void testCreateAndDestroy() {
	tree_ptr_t tree = create_tree(1, 12);
	assert(tree->key_ == 1);
	assert(tree->value_ == 12);
	destroy_tree(tree);
	std::cout << "Test Create And Destroy succsesful.\n";
}

void testCreateDestroyChildren() {
	tree_ptr_t child2 = create_tree(3, 4);
	tree_ptr_t child1 = create_tree(2, 3);
	tree_ptr_t head = create_tree(1, 2, child1, child2);
	destroy_tree(head);
	std::cout << "Test destroying children successful.\n";
}

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
	tree_ptr_t l4c1 = create_tree(6, 1);
	tree_ptr_t l3c1 = create_tree(5, 1, nullptr, l4c1);
	tree_ptr_t l3c2 = create_tree(9, 1);
	tree_ptr_t l2c1 = create_tree(4, 1, l3c1);
	tree_ptr_t l2c2 = create_tree(4, 1, l3c2);
	tree_ptr_t l2c3 = create_tree(7, 1);
	tree_ptr_t l1c1 = create_tree(2, 1, l2c1);
	tree_ptr_t l1c2 = create_tree(3, 1, l2c2, l2c3);
	tree_ptr_t head = create_tree(1, 1, l1c1, l1c2);

	std::cout << "\nTesting path finding...\n";
	std::cout << "Find 6, expected LLLR got " << path_to(head, 6) << std::endl;
	std::cout << "Find 7, expected RR got " << path_to(head, 7) << std::endl;
	std::cout << "Find 4, expected LL got " << path_to(head, 4) << std::endl;
	std::cout << "Find 9, expected RLL got " << path_to(head, 9) << std::endl;
	std::cout << "Find 1, expected  got " << path_to(head, 1) << std::endl;

	std::cout << "Testing retreival...\n";
	std::cout << "Find LLLR, expected 6 got " << (node_at(head, "LLLR")->key_) << std::endl;
	std::cout << "Find RR, expected 7 got " << (node_at(head, "RR")->key_) << std::endl;
	std::cout << "Find LL, expected 4 got " << (node_at(head, "LL")->key_) << std::endl;
	std::cout << "Find RLL, expected 9 got " << (node_at(head, "RLL")->key_) << std::endl;
	std::cout << "Find , expected 1 got " << (node_at(head, "")->key_) << std::endl;
	std::cout << "Find RRL, expected nullptr got " << (node_at(head, "RRL")) << std::endl;
	std::cout << "Find ABC, expected nullptr got " << (node_at(head, "ABC")) << std::endl;

	destroy_tree(head);
	std::cout << "Testing complete\n";
}

void testTree() {
	testCreateAndDestroy();
	testCreateDestroyChildren();
	testPathFinding();
}

int main(){
	testTree();
	return 0;
}