--- Included Files ---
hforest.cpp      - implementation of forest
hforest.h        - header for forest
htree.cpp        - implementation of tree
htree.hh         - header for tree, included with project
Makefile         - makefile for both tests
test_hforest     - pre-compiled forest test
test_hforest.cpp - implementation of the forest tester
test_hforest.h   - header for forest tester
test_htree       = pre-compiled tree test
test_htree.cpp   - implementation of the tree tester
test_htree.h     - header for the tree tester

--- How to Build ---
use "make tree" to make tree test
use "make forest" to make forest test

--- Design Choices ---
I had a little trouble getting the shared pointers to work with the recursive implementation of path_to but otherwise
the class transformation was fairly smooth. The hforest class was very simple to implement since most of the required
methods where already standard for vectors. Otherwise it was simple to use the make_heap to access the highest value.