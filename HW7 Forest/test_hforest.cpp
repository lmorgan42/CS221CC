#include "test_hforest.h"
#include "hforest.h"
#include <iostream>

void testForest() {

	std::cout << "--- Begin Forest Tests ---" << std::endl;

	HTree::tree_ptr_t a = std::shared_ptr<const HTree>(new HTree(1, 3));
	HTree::tree_ptr_t b = std::shared_ptr<const HTree>(new HTree(1, 9));
	HTree::tree_ptr_t c = std::shared_ptr<const HTree>(new HTree(1, 6));

	HForest* m = new HForest();

	std::cout << "Adding 3 one node trees..." << std::endl;
	m->add_tree(a);
	m->add_tree(b);
	m->add_tree(c);

	std::cout << "Querying size, expected: 3, got: " << m->size() << std::endl;

	HTree::tree_ptr_t out = m->pop_tree();
	std::cout << "Popping first tree, expected value: 9, got: " << out->get_value() << std::endl;
	std::cout << "Size now " << m->size() << std::endl;

	out = m->pop_tree();
	std::cout << "Popping second tree, expected value: 6, got: " << out->get_value() << std::endl;
	std::cout << "Size now " << m->size() << std::endl;

	out = m->pop_tree();
	std::cout << "Popping final tree, expected value: 3, got: " << out->get_value() << std::endl;
	std::cout << "Size now " << m->size() << std::endl;
	
	out = m->pop_tree();
	std::cout << "Popping final tree, expected value: nullptr, got: " << out << std::endl;
	std::cout << "Size now " << m->size() << std::endl;

	std::cout << "Deleteing forest..." << std::endl;

	delete m;

	std::cout << "--- End of testing ---" << std::endl;
}

int main(){
	testForest();
	return 0;
}