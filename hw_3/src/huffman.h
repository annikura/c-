#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <algorithm>


class HuffmanNode {
public:
	HuffmanNode *left = nullptr, *right = nullptr;
	char symbol;
	int id;
	std::uint32_t count;

	static int getId() {
		static int id_var = 0;
		return id_var++;
	}

public:
	HuffmanNode() = default;
	HuffmanNode(char c, std::uint32_t cnt);
	
	bool is_leaf() const;
	char getLetter() const;
	
	HuffmanNode * improve(bool symbol) const;
	void tie(HuffmanNode & l, HuffmanNode & r);
	void descende(std::vector <char> & string, std::map <char, std::string> & table) const;
	friend bool operator<(const HuffmanNode &, const HuffmanNode &);
};

bool operator<(const HuffmanNode & a, const HuffmanNode & b); 

// ===== =====

class HuffmanStructure {
private:
	std::uint32_t encode_table_size, code_size, text_size;
	std::map <std::string, char> decode_table;
	std::map <char, std::string> encode_table;
	std::map <char, uint32_t> frequency_table;
	std::list <HuffmanNode> v_storage;
	HuffmanNode root;

public:
	HuffmanStructure() : encode_table_size(0),  code_size(0), text_size(0) { };
	void readTable(std::ifstream & in);
	void countFrequences(std::ifstream & in);
	
	void buildTree();

	void decode(const std::string & file_in, const std::string & file_out);
	void encode(const std::string & file_in, const std::string & file_out);
	
	void writeDecoded(std::ifstream & in, std::ofstream & out);
	void writeEncoded(std::ifstream & in, std::ofstream & out);

	void writeTable(std::ofstream & out) const;
	void writeText(std::ifstream & in, std::ofstream & out) const;

	std::uint32_t countCodeSize();
	std::uint32_t getCodeSize() const;
	std::uint32_t getTextSize() const;
	std::uint32_t getTableSize() const;
};

