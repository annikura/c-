#include "huffman.h"
#include <cassert>

static const int ByteSize = 8;

template <typename T>
static void writeBinaryItem(std::ostream & out, T obj){
	out.write(reinterpret_cast<char *>(&obj), sizeof(obj));
}

template <typename T>
static void readBinaryItem(std::istream & in, T & obj){
	in.read(reinterpret_cast<char *>(&obj), sizeof(obj));
}

void HuffmanStructure::decode(std::istream & in, std::ostream & out){
	readTable(in);
	buildTree();

	writeDecoded(in, out);
}


void HuffmanStructure::encode(std::istream & in, std::ostream & out){	
	auto saved_pos = in.tellg();
	countFrequences(in);
	buildTree();

	in.clear();
	in.seekg(saved_pos, in.beg);
	
	writeEncoded(in, out);
}


void HuffmanStructure::readTable(std::istream & in) {
	std::uint32_t table_size; 
	char symbol;
	std::uint32_t quantity;
	
	readBinaryItem(in, table_size);
	for (std::size_t i = 0; i < table_size; i++){
		readBinaryItem(in, symbol);
		readBinaryItem(in, quantity);
		frequency_table[symbol] = quantity;
	}

	encode_table_size = sizeof(table_size) + table_size * (sizeof(symbol) + sizeof(quantity));
}

void HuffmanStructure::countFrequences(std::istream & in) {
	char symbol;
	while (in.get(symbol))
		frequency_table[symbol]++, text_size++;
	/*if (in.failbit || in.badbit)
		throw ...; */
	encode_table_size = sizeof(uint32_t) + frequency_table.size() * (sizeof(char) + sizeof(uint32_t));
}

void HuffmanStructure::buildTree() {
	std::set<HuffmanNode> vertexes;
	HuffmanNode left, right, parent;
	HuffmanNode *left_ptr, *right_ptr;

	for (auto i : frequency_table){
		vertexes.insert(HuffmanNode(i.first, i.second));
		if (frequency_table.size() == 1)
			vertexes.insert(HuffmanNode(i.first, i.second));
	}

	while (vertexes.size() > 1){
		left  = *vertexes.begin(), vertexes.erase(left);
		right = *vertexes.begin(), vertexes.erase(right);
		
		v_storage.push_back(left),  left_ptr  = &v_storage.back();
		v_storage.push_back(right), right_ptr = &v_storage.back();
		parent.tie(*left_ptr, *right_ptr);
		vertexes.insert(parent);
	}

	root = *vertexes.begin();
	std::vector <char> string;
	root.descende(string, encode_table);
	for (auto i : encode_table){
		decode_table[i.second] = i.first;
		
	}
	
	countCodeSize();
}


void HuffmanStructure::writeDecoded(std::istream & in, std::ostream & out) {
	std::uint32_t length, pos;
	char code, code_char;
	HuffmanNode * cur_node = &root;

	length = code_size;

	for (std::size_t i = 0; i < length; i++){
		if (i % ByteSize == 0) in.get(code);
		pos = i % ByteSize;
		code_char = ((code >> pos) & 1);
		
		cur_node = cur_node->advance(code_char);

		if (cur_node->is_leaf()){
			out << cur_node->getLetter();
			text_size++;
			cur_node = &root;
		}
	}
}

void HuffmanStructure::writeEncoded(std::istream & in, std::ostream & out) {
	writeTable(out);
	writeText(in, out);
}

void HuffmanStructure::writeTable(std::ostream & out) const {
	writeBinaryItem(out, static_cast<uint32_t>(decode_table.size()));
	for (std::pair<char, uint32_t> i : frequency_table) {
		writeBinaryItem(out, i.first);
		writeBinaryItem(out, i.second);
	}
}

void HuffmanStructure::writeText(std::istream & in, std::ostream & out) const {
	char symbol, to_record = 0;
	std::size_t pos = 0;

	while(in.get(symbol)){ 
		const std::string & code = (*encode_table.find(symbol)).second;
		for (std::size_t i = 0; i < code.size(); i++) {
			to_record = to_record | ((int)(code[i] == '1') << pos++);
			if (pos == ByteSize) {
				writeBinaryItem(out, to_record);
				to_record = 0, pos = 0;
			}
		}
	}
	if (pos)
		writeBinaryItem(out, to_record);
}


std::uint32_t HuffmanStructure::countCodeSize() {
	if (code_size)
		return code_size;
	for (auto i : encode_table){
		code_size += i.second.size() * frequency_table[i.first];
	}
	return code_size;
}

std::uint32_t HuffmanStructure::getCodeSize() const {
	return (code_size + ByteSize - 1) / ByteSize;
}

std::uint32_t HuffmanStructure::getTextSize() const {
	return text_size;
}

std::uint32_t HuffmanStructure::getTableSize() const {
	return encode_table_size;
}

//=== Huffman Node ===

HuffmanNode::HuffmanNode(char c, std::uint32_t cnt) :
		symbol(c),
		id(getId()),
		count(cnt) { }; 

bool HuffmanNode::is_leaf() const {
	return left == nullptr && right == nullptr;
}

char HuffmanNode::getLetter() const {
	return symbol;
}

void HuffmanNode::tie(HuffmanNode & l, HuffmanNode & r) {
	count = l.count + r.count;
	left = &l, right = &r;
	id = getId();
}

bool operator<(const HuffmanNode & a, const HuffmanNode & b) {
	return a.count < b.count || (a.count == b.count && a.id < b.id);	
}

HuffmanNode * HuffmanNode::advance(bool chr) const {
	return (chr ? this->right : this->left);
}

void HuffmanNode::descende(std::vector <char> & string, std::map <char, std::string> & table) const {
	if (is_leaf()){
		table[symbol] = std::string(string.begin(), string.end());
		return;
	}
	string.push_back ('0');
	left->descende(string, table);
	string.pop_back();
	
	string.push_back('1');
	right->descende(string, table);
	string.pop_back();

}