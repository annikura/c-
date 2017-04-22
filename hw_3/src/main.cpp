#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>
#include "huffman.h"

struct ModeSpecifier{
	enum class ActionType{ Undefined, Encode, Decode, Multiple };
	ActionType type = ActionType::Undefined;
	std::string iname, oname;

	void validate(){
		if (iname.empty() || oname.empty())
			throw std::invalid_argument("At least one of the input/output file keys is absent.");
		if (type == ModeSpecifier::ActionType::Undefined ||
			type == ModeSpecifier::ActionType::Multiple)
			throw std::invalid_argument("Enter ONE of the -u/-c keys");
		if (iname == oname)
			throw std::invalid_argument("input and output filenames should be different");
	}
};

ModeSpecifier parseArgs(int carg, const char ** varg){
	ModeSpecifier args; 
	for (int i = 1; i < carg; i++){

		std::string arg = static_cast<std::string>(varg[i]);
		
		if (arg == "-c"){
			args.type = args.type == ModeSpecifier::ActionType::Undefined ?
									 ModeSpecifier::ActionType::Encode :
						 			 ModeSpecifier::ActionType::Multiple ;
			continue;
		}
		if (arg == "-u"){
			args.type = args.type == ModeSpecifier::ActionType::Undefined ?
									 ModeSpecifier::ActionType::Decode :
						 			 ModeSpecifier::ActionType::Multiple ;
			continue;
		}
		if (arg == "-f" || arg == "--file"){
			if (i == carg - 1) throw std::invalid_argument("An argument after " + arg + " was expected.");
			args.iname = static_cast<std::string>(varg[++i]);
			continue;
		}
		if (arg == "-o" || arg == "--output"){
			if (i == carg - 1) throw std::invalid_argument("An argument after " + arg + " was expected.");
			args.oname = std::string(varg[++i]);
			continue;
		}

		throw std::invalid_argument("Unknown argument " + arg + ".");
	}
	return args;
}

int main(int carg, const char ** varg){
	ModeSpecifier args = parseArgs(carg, varg);
	args.validate();

	HuffmanStructure huff_str;
	if (args.type == ModeSpecifier::ActionType::Decode){
		huff_str.decode(args.iname, args.oname);
		
		std::cout << huff_str.getCodeSize()  << std::endl
			 	  << huff_str.getTextSize()  << std::endl
			 	  << huff_str.getTableSize() << std::endl;
		return 0;
	}
	if (args.type == ModeSpecifier::ActionType::Encode){
		huff_str.encode(args.iname, args.oname);
		
		std::cout << huff_str.getTextSize()  << std::endl
			 	  << huff_str.getCodeSize()  << std::endl
			 	  << huff_str.getTableSize() << std::endl;
		return 0;
	}
	return 1;
	//Err. What is going on?
}