--- Included Files ---
tree.hh       - header file for tree struct, included with assignment
Tree .cpp     - contains C++ code that defines struct Tree
test_tree.cpp - contains C++ code that tests the functioning of tree, also contains the main
Makefile      - makefile for the project

--- How to Build ---
use the make command.

--- Design Choices ---
node_at and create_tree are both very straightforward in implementation. For destroy_tree I opted to use recursion since it seemed a simple and elegant way to ensure the tree and its children where deleted completely and in a logical order. path_to also uses recursion but because of the way it was defined in Tree.hh i had to create a recursive helper function that was able to convey when the desired value was found using a reference to a boolean.

--- Testing Notes ---
Proper deletion was tested using valgrind since it is difficult to safely confirm that memory has been freed.
-total heap usage: 15 allocs, 15 frees, 74,144 bytes allocated-
