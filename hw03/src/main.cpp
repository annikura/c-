#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include "huffman.h"
#include "HuffmanFileEncoder.h"
#include "HuffmanFileDecoder.h"

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
            args.oname = static_cast<std::string>(varg[++i]);
            continue;
        }

        throw std::invalid_argument("Unknown argument " + arg + ".");
    }
    return args;
}

int main(int carg, const char ** varg){
    ModeSpecifier args = parseArgs(carg, varg);
    args.validate();

    std::ios_base::sync_with_stdio(0);

    if (args.type == ModeSpecifier::ActionType::Encode){
        ByteFileWriter fileWriter(args.oname);
        HuffmanFileEncoder<ByteFileWriter> encoder;
        encoder.encodeFile(args.iname, fileWriter);
        fileWriter.close();
    }
    else if (args.type == ModeSpecifier::ActionType::Decode){
        BitFileWriter fileWriter(args.oname);
        HuffmanFileDecoder<BitFileWriter> decoder;
        decoder.decodeFile(args.iname, fileWriter);
        fileWriter.flush();
        fileWriter.close();
    }

    //Err. What is going on?
}