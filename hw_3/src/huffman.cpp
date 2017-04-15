#include "huffman.h"

static const int BYTE_SIZE = 8;

template <typename T>
static void writeBinaryItem(std::ofstream & out, T obj){
	out.write(reinterpret_cast<char *>(obj), sizeof(obj));
}

template <typename T>
static void readBinaryItem(std::ifstream & in, T & obj){
	in.read(reinterpret_cast<char *>(&obj), sizeof(obj));
}


void HuffmanStructure::readTable(std::ifstream & in) {
	std::size_t table_size; 
	readBinaryItem(in, table_size);
	for (std::size_t i = 0; i < table_size; i++){
		char symbol;
		std::size_t quantity;
		readBinaryItem(in, symbol);
		readBinaryItem(in, quantity);
		frequency_table[symbol] = quantity;	
	}
}

void HuffmanStructure::readNCount(std::ifstream & in) {
	char symbol;
	while (in.get(symbol))
		frequency_table[symbol]++;
	/*if (in.failbit || in.badbit)
		throw ...; */
}

void HuffmanStructure::buildTree() {
	std::set <HuffmanNode> vertexes;
	HuffmanNode left, right, parent;

	for (auto i : frequency_table)
		vertexes.insert(HuffmanNode(i.first, i.second));
	while (vertexes.size() > 1){
		left = *vertexes.begin(), vertexes.erase(vertexes.begin());
		right = *vertexes.begin(), vertexes.erase(vertexes.begin());
		parent.tie(left, right);
		vertexes.insert(parent);
	}

	HuffmanNode root = *vertexes.begin();
	std::vector <char> string;
	root.descende(string, encode_table);

	for (auto i : encode_table)
		decode_table[i.second] = i.first;
}

std::size_t HuffmanStructure::countCodeSize() {
	code_size = 0;
	for (auto i : encode_table){
		code_size += i.second.size() * frequency_table[i.first];
	}
	return code_size;
}

std::size_t HuffmanStructure::getCodeSize() {
	if (!code_size)
		countCodeSize();
	return code_size;
}

void HuffmanStructure::decodeNWrite(std::ifstream & in, std::ofstream & out) const {
	std::size_t length, pos;
	std::string current_code;
	char code, code_char;

	readBinaryItem(in, length);
	for (std::size_t i = 0; i < length; i++){
		if (i % BYTE_SIZE) in.get(code);
		pos = i / BYTE_SIZE, code_char = '0' + ((code >> pos) & 1);

		current_code += code_char; 
		auto symbol = decode_table.find(current_code);

		if (symbol != decode_table.end()){
			out << (*symbol).second;
			current_code = "";
		}
	}
	if (current_code.size() > 0)
		throw "Input is not a huffman encoded file";
}

void HuffmanStructure::encodeNWrite(std::ifstream & in, std::ofstream & out) {
	writeTable(out);
	writeText(in, out);
}

void HuffmanStructure::writeTable(std::ofstream & out) const {
	writeBinaryItem(out, decode_table.size());
	for (std::pair<char, size_t> i : frequency_table) {
		writeBinaryItem(out, i.first);
		writeBinaryItem(out, i.second);
	}
}

void HuffmanStructure::writeText(std::ifstream & in, std::ofstream & out) {
	char symbol, to_record = 0;
	std::size_t pos = 0;

	writeBinaryItem(out, this->getCodeSize());

	while(in.get(symbol)){ 
		const std::string & code = (*encode_table.find(symbol)).second;
		for (std::size_t i = 0; i < code.size(); i++) {
			to_record = to_record | ((code[i] == '1') << pos++);
			if (pos == BYTE_SIZE) {
				writeBinaryItem(out, to_record);
				to_record = 0, pos = 0;
			}
		}
	}
}

//=== Huffman Node ===

bool operator<(const HuffmanNode & a, const HuffmanNode & b) {
	return a.count < b.count || (a.count == b.count && a.symbol < b.symbol);
}

void HuffmanNode::descende(std::vector <char> & string, std::map <char, std::string> & table) const {
	if (is_leaf){
		table[symbol] = std::string(string.begin(), string.end());
		return;
	}

	string.push_back('0');
	left->descende(string, table);

	string.pop_back();
	string.push_back('1');
	right->descende(string, table);

}