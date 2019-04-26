#include "pch.h"
#include "cities.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
#include <ctime>
#include <math.h>

double distance(std::pair<int, int> p1, std::pair<int, int> p2) {
	return std::sqrt((double)((p2.first - p1.first) * (p2.first - p1.first) + (p2.second - p1.second) * (p2.second - p1.second)));
}

std::pair<int, int> parseLine(std::string line) {
	std::pair<int, int> toRe;
	std::string num;
	bool first = true;
	if (line.back() != '\n') line += "\n";
	for (auto x : line){
		if (x == ' ' || x=='\n'){
			if (num.size() > 0) {
				if (first) {
					toRe.first = std::stoi(num);
					first = false;
				}
				else toRe.second = std::stoi(num);
			}
			num = "";
		}
		else num = num + x;
	}
	/*std::cout << "made pair: <" << toRe.first << ", " << toRe.second << ">\n";*/
	return toRe;
}

double Cities::total_path_distance(const Cities::permutation_t& ordering) const {
	double toRe = 0;
	for (unsigned i = 0; i < coords_.size(); ++i) {
		toRe += distance(coords_[ordering[i]], coords_[ordering[(i + 1) % coords_.size()]]);
	}
	return toRe;
}

double Cities::total_path_distance() const {
	double toRe = 0;
	for (unsigned i = 0; i < coords_.size(); ++i) {
		toRe += distance(coords_[i], coords_[(i + 1) % coords_.size()]);
	}
	return toRe;
}

std::istream & operator >> (std::istream &in, Cities &c){
	std::string line;
	c.coords_.clear();
	while (std::getline(in, line)) {
		c.coords_.push_back(parseLine(line));
	}
	return in;
}

std::ostream & operator << (std::ostream &out, Cities &c) {
	for (unsigned i = 0; i < c.coords_.size(); ++i) {
		out << c.coords_[i].first << " " << c.coords_[i].second << "\n";
	}
	return out;
}

Cities Cities::reorder(const permutation_t& ordering) const {
	Cities toRe;
	std::string out = "";
	for (unsigned i = 0; i < ordering.size(); ++i) {
		out += std::to_string(coords_[ordering[i]].first);
		out += " ";
		out += std::to_string(coords_[ordering[i]].second);
		out += "\n";
	}
	std::stringstream streamout(out);
	streamout >> toRe;
	return toRe;
}

Cities::Cities(std::string fileName) {
	std::ifstream file(fileName);
	file >> *this;
}

Cities::permutation_t CitiesHelper::random_permutation(unsigned len) {
	//create and populate vector of appropriate size
	Cities::permutation_t toRe(len);
	std::iota(toRe.begin(), toRe.end(), 0);

	//randomly shuffle the vector
	std::srand(std::time(0));
	std::random_shuffle(toRe.begin(), toRe.end());

	return toRe;
}