#include "../src/FrequencyTable.h"
#include <gtest/gtest.h>

#include <iostream>
#include <cstdio>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include "../src/HuffmanFileEncoder.h"
#include "../src/HuffmanFileDecoder.h"
#include "../src/HuffmanNode.h"

TEST(TableCheck, CountTest) {
    FrequencyTable<std::string::iterator, std::string> table;
    std::string s = "abbacabbaa";
    table.fillTable(s.begin(), s.end());
    EXPECT_EQ(3, table.size());
    EXPECT_EQ(4, table['b']);
    EXPECT_EQ(5, table['a']);
    EXPECT_EQ(1, table['c']);
}

TEST(TableCheck, ZeroTest) {
    FrequencyTable<std::string::iterator, std::string> table;
    std::string s = "";
    table.fillTable(s.begin(), s.end());
    EXPECT_EQ(0, table.size());
}

TEST(TableCheck, ReadTest) {
    FrequencyTable<std::vector<bool>::iterator, std::string> table;
    std::vector<bool> v{0, 1, 0, 0, 0, 0, 0, 0, // 2 symbols: 129 : 386, 1 : 259
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,

                        1, 0, 0, 0, 0, 0, 0, 1,

                        0, 1, 0, 0, 0, 0, 0, 1,
                        1, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,

                        1, 0, 0, 0, 0, 0, 0, 0,

                        1, 1, 0, 0, 0, 0, 0, 0,
                        1, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0, 0, 0};
    table.importBinary(v.begin());
    EXPECT_EQ(2, table.size());
    EXPECT_EQ(386, table[129]);
    EXPECT_EQ(259, table[1]);
}

TEST(TableCheck, WriteTest) {
    FrequencyTable<std::string::iterator, std::vector<bool> > table;
    std::vector<bool> dest;
    std::string s = "aaa";

    table.fillTable(s.begin(), s.end());
    table.exportBinary(dest);
    EXPECT_EQ(1, table.size());
    EXPECT_EQ(3, table['a']);

    std::string res;
    for (auto el: dest) res += el + '0';
    EXPECT_EQ("1000000000000000000000000000000000000000000000000000000000000000100001101100000000000000000000000000000000000000000000000000000000000000", res);
}

int main(int argc, char ** argv) {
    srand(179);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}