#ifndef HW03_HUFFMANFILEENCODER_H
#define HW03_HUFFMANFILEENCODER_H

#include <iterator>
#include "HuffmanTree.h"
#include "HuffmanEncoder.h"
#include "BitFileWriter.h"

template<class Container = std::string>
class HuffmanFileEncoder : protected HuffmanEncoder<std::istream_iterator<uint8_t>, Container> {
private:
public:
    void encodeFile(const std::string & in_file, Container & dest);
};

template<class Container>
void HuffmanFileEncoder<Container>::encodeFile(const std::string & in_file, Container & dest){
    std::ifstream in(in_file);
    std::istream_iterator<uint8_t> in_iterator(in);
    std::istream_iterator<uint8_t> eos; // end-of-stream iterator

    HuffmanEncoder<std::istream_iterator<uint8_t>, Container>::initTable(in_iterator, eos);

    in.clear();
    in.seekg(0, std::ios::beg);

    in_iterator = std::istream_iterator<uint8_t>(in);
    HuffmanEncoder<std::istream_iterator<uint8_t>, Container>::encode(in_iterator, eos, dest);
    in.close();
}

#endif //HW03_HUFFMANFILEENCODER_H
