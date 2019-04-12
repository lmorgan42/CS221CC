#include "huffman.h"
#include "bitio.h"
#include <string>
#include <fstream>
#include <iostream>

void decodeFile(std::ifstream& inFile, std::ofstream& outFile) {

	BitIO bitIn = BitIO(nullptr, &inFile);
	Huffman decoder;

	int inp = -1;
	while (true) {
		while (inp < 0) {
			inp = decoder.decode(bitIn.input_bit());
		}
		std::cout << "obtained inp of " << (char)inp << " " << inp << "\n";
		if (inp == 256) {
			std::cout << "breaking\n";
			break;
		}
		else {
			outFile.put(inp);
			inp = -1;
		}
	}

}


int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "You must include at least one file name" << "\n";
		return -1;
	}

	for (int i = 1; i < argc; ++i) {
		std::cout << "running for\n";
		std::ifstream inFile(argv[i]);
		if (!inFile.is_open()) {
			std::cerr << "Can't open input " << argv[i] << "\n";
			return -2;
		}
		std::string oFName = argv[i];
		oFName += ".plaintext";
		std::ofstream outFile;
		outFile.open(oFName, std::ios::binary);
		if (!inFile.is_open()) {
			std::cerr << "Can't open output " << oFName << "\n";
			return -2;
		}

		decodeFile(inFile, outFile);
		inFile.close();
		outFile.close();
	}
	return 0;
}