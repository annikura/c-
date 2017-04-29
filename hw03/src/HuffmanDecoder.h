#ifndef HW03_HUFFMANDECODER_H
#define HW03_HUFFMANDECODER_H


#include "HuffmanTree.h"

template<typename Iterator, typename Container>
class HuffmanDecoder {
protected:
    HuffmanTree<Iterator, Container> tree;
    FrequencyTable<Iterator, Container> table;
public:
    Iterator initTable(Iterator begin);
    Container & decode(Iterator begin, Iterator end, Container & dest);
};



template<typename Iterator, typename Container>
Iterator HuffmanDecoder<Iterator, Container>::initTable(Iterator begin){
    Iterator it = table.importBinary(std::move(begin));
    tree.build(table);
    return it;
}

template<typename Iterator, typename Container>
Container & HuffmanDecoder<Iterator, Container>::decode(Iterator begin, Iterator end, Container & dest) {
    for (Iterator it = std::move(begin); it != end; ++it){
        uint8_t symbol;
        it = tree.getSymbol(std::move(it), std::move(end), symbol);
        dest.push_back(static_cast<char>(symbol));
    }
    return dest;
}

#endif //HW03_HUFFMANDECODER_H
