#include "huffman.h"
#include "bitio.h"
#include <string>
#include <fstream>
#include <iostream>

void encodeFile(std::ifstream& inFile, std::ofstream& outFile) {

	BitIO bitOut = BitIO(&outFile, nullptr);
	Huffman encoder;

	char inp;
	Huffman::bits_t outp;
	while (!inFile.eof()) {
		inp = inFile.get();
		if (inp == -1) {
			outp = encoder.encode(Huffman::HEOF);
			std::cout << "Wrote EOF\n";
		}
		else {
			outp = encoder.encode(inp);
		}

		for (uint64_t i = 0; i < outp.size(); ++i) {
			std::cout << "WB " << outp[i] << "\n";
			bitOut.output_bit(outp[i]);
		}
	}
}


int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "You must include at least one file name" << "\n";
		return -1;
	}

	for (int i = 1; i < argc; ++i) {
		std::ifstream inFile(argv[i]);
		if (!inFile.is_open()) {
			std::cerr << "Can't open input " << argv[i] << "\n";
			return -2;
		}
		std::string oFName = argv[i];
		oFName += ".comp";
		std::ofstream outFile(oFName);
		if (!inFile.is_open()) {
			std::cerr << "Can't open output " << oFName << "\n";
			return -2;
		}

		encodeFile(inFile, outFile);
	}
	return 0;
}