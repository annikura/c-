#ifndef HW03_HUFFMAN_H
#define HW03_HUFFMAN_H

#include "BitFileWriter.h"
#include "BitFileReader.h"
#include "HuffmanNode.h"
#include "HuffmanTree.h"

template<class Iterator, class Container>
Container & huffmanEncode(Iterator begin, Iterator end, const HuffmanTree<Iterator, Container> & tree, Container & dest){
    for (Iterator it = begin; it != end; ++it){
        std::string code = tree.getCode(*it);
        for (auto symbol: code)
            dest.push_back(symbol);
    }
    return dest;
};

template<class Iterator, class Container>
Container & huffmanDecode(Iterator begin, Iterator end, const HuffmanTree<Iterator, Container> & tree, Container & dest){
    for (Iterator it = begin; it != end; ++it){
        uint8_t symbol;
        it = tree.getSymbol(it, end, symbol);
        dest.push_back(symbol);
    }
    return dest;
};

#endif //HW03_HUFFMAN_H
