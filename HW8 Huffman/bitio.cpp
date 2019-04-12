#include "bitio.h"
#include <iostream>

BitIO::BitIO(std::ostream* os, std::istream* is) {
	if (is != nullptr && os != nullptr) {
		std::cerr << "BitIO failed to construct, two streams were provided but only one can be accepted.\n";
		throw ("BitIO excessive arguments");
		return;
	}
	if (os != nullptr) {
		os_ = os;
	}
	else if (is != nullptr) {
		is_ = is;
	}
	else {
		std::cerr << "BitIO failed to construct, no stream was provided.\n";
		throw ("BitIO no streams");
		return;
	}
}

void BitIO::output_bit(bool bit) {
	if (bit) {
		uint8_t mask = 1;
		buffer_ |= (mask << count_);
	}

	++count_;

	if (count_ > 7) {
		*os_ << buffer_;
		buffer_ = 0;
		count_ = 0;
	}
}

bool BitIO::input_bit() {
	if (count_ == 0) {
		buffer_ = is_->get();
		count_ = 8;
	}

	--count_;
	
	uint8_t input = buffer_ & 1;
	buffer_ >>= 1;
	return (input);
}

BitIO::~BitIO(){
	if (os_ != nullptr && count_ != 0) {
		*os_ << buffer_;
	}
}