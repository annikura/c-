#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>
#include "huffman.h"

using namespace std;

struct arg_struct{
	bool pack, unpack;
	bool input, output;
	string iname, oname;
	arg_struct(){
		pack = false, unpack = false;
		input = false, output = false;
	}
};

arg_struct readInput(int carg, const char ** varg){
	arg_struct args; 
	for (int i = 1; i < carg; i++){
		string arg = string(varg[i]);
		if (arg == "-c"){
			args.pack = true;
			continue;
		}
		if (arg == "-u"){
			args.unpack = true;
			continue;
		}
		if (arg == "-f" || arg == "--file"){
			if (i == carg - 1) throw invalid_argument("An argument after " + arg + " was expected.");
			if (!args.input){
				args.input = true;
				args.iname = string(varg[++i]);
			}
			continue;
		}
		if (arg == "-o" || arg == "--output"){
			if (i == carg - 1) throw invalid_argument("An argument after " + arg + " was expected.");
			if (!args.output){
				args.output = true;
				args.oname = string(varg[++i]);
			}
			continue;
		}
		throw invalid_argument("Unknown argument " + arg + ".");
	}
	return args;
}

void checkArgs(const arg_struct & args){
	if (!args.input || !args.output)
		throw invalid_argument("At least one of the input/output keys is absent.");
	if (args.pack == args.unpack)
		throw invalid_argument("Choose ONE of the encode/decode options");
	if (args.iname == args.oname)
		throw invalid_argument("input and output filenames should be different");
}

int main(int carg, const char ** varg){
	arg_struct args = readInput(carg, varg);
	checkArgs(args);
	HuffmanStructure huff_str;
	if (args.unpack){
		ifstream in (args.iname, ios::binary);
		
		huff_str.readTable(in);
		huff_str.buildTree();

		ofstream out (args.oname, ios::binary);
		huff_str.decodeNWrite(in, out);
		
		in.close();
		out.close();
		return 0;
	}
	if (args.pack){
		ifstream in (args.iname);
		
		huff_str.readNCount(in);
		huff_str.buildTree();

		in.seekg(0, ios_base::beg);
		ofstream out (args.oname);
		huff_str.encodeNWrite(in, out);
		
		in.close();
		out.close();
		return 0;
	}
	return 1;
	//Err. What is going on?
}