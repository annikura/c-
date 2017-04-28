#include "huffman.h"

#include <gtest/gtest.h>
#include <string>
#include <cstdio>

class Fixture : public ::testing::Test {
protected:
	HuffmanStructure huff_str;
	std::stringstream in, out, mid;
};

TEST_F(Fixture, testUnarString){
	std::string string = "aaa";

	in << string;

	huff_str.encode(in, mid);
	mid.clear();
	mid.seekg(0, mid.beg);
	huff_str.decode(mid, out);

	EXPECT_EQ(in.str(), out.str());
}

TEST_F(Fixture, testSimpleString){
	std::string string = "not a simple\n string";

	in << string << '\0' << 'x';

	huff_str.encode(in, mid);
	mid.clear();
	mid.seekg(0, mid.beg);
	huff_str.decode(mid, out);
	EXPECT_EQ(in.str(), out.str());
}
	
TEST_F(Fixture, testString){
	std::string string = "not a simple string";

	in << string;

	huff_str.encode(in, mid);
	mid.clear();
	mid.seekg(0, mid.beg);
	huff_str.decode(mid, out);

	EXPECT_EQ(in.str(), out.str());
}



int main(int argc, char ** argv) {
	srand(179);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}