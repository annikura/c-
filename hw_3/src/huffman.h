#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

class HuffmanStructure {
private:
	std::size_t encode_table_size, code_size;
	std::map <std::string, char> decode_table;
	std::map <char, std::string> encode_table;
	std::map <char, size_t> frequency_table;

public:
	void readTable(std::ifstream & in);
	void readNCount(std::ifstream & in);
	
	void buildTree();
	
	void decodeNWrite(std::ifstream & in, std::ofstream & out) const;
	void encodeNWrite(std::ifstream & in, std::ofstream & out);

	void writeTable(std::ofstream & out) const;
	void writeText(std::ifstream & in, std::ofstream & out);

	std::size_t countCodeSize();
	std::size_t getCodeSize();
};


class HuffmanNode {
private:
	bool is_leaf;
	HuffmanNode *left, *right;
	char symbol;
	std::size_t count;
public:
	HuffmanNode() { };
	HuffmanNode(char c, std::size_t cnt) : 
		is_leaf(true), 
		left(NULL), 
		right(NULL),
		symbol(c),
		count(cnt) { }; 

	void tie(HuffmanNode & l, HuffmanNode & r) {
		count = l.count + r.count;
		left = &l, right = &r;
		is_leaf = false;
	}
	void descende(std::vector <char> & string, std::map <char, std::string> & table) const;
	friend bool operator<(const HuffmanNode &, const HuffmanNode &);
};


bool operator<(const HuffmanNode & a, const HuffmanNode & b);