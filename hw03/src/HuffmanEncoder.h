#ifndef HW03_HUFFMANENCODER_H
#define HW03_HUFFMANENCODER_H

#include "HuffmanTree.h"

template<typename Iterator, typename Container>
class HuffmanEncoder {
protected:
    HuffmanTree<Iterator, Container> tree;
    FrequencyTable<Iterator, Container> table;
public:
    void initTable(Iterator begin, Iterator end);
    Container & encode(Iterator begin, Iterator end, Container & dest);
};

template<typename Iterator, typename Container>
void HuffmanEncoder<Iterator, Container>::initTable(Iterator begin, Iterator end){
    table.fillTable(begin, end);
    tree.build(table);
}

template<typename Iterator, typename Container>
Container & HuffmanEncoder<Iterator, Container>::encode(Iterator begin, Iterator end, Container & dest){
    table.exportBinary(dest);
    for (Iterator it = begin; it != end; ++it){
        std::string code = tree.getCode(*it);
        for (auto symbol: code)
            dest.push_back(symbol);
    }
    return dest;
}

#endif //HW03_HUFFMANENCODER_H
