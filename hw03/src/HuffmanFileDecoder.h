#ifndef HW03_HUFFMANFILEDECODER_H
#define HW03_HUFFMANFILEDECODER_H

#include <iterator>
#include "HuffmanDecoder.h"
#include "BitFileReader.h"
#include "ByteFileWriter.h"

template<class Container = std::string>
class HuffmanFileDecoder : protected HuffmanDecoder<BitFileReader, Container> {
private:
public:
    void decodeFile(const std::string & in_file, Container & dest);
};

template<class Container>
void HuffmanFileDecoder<Container>::decodeFile(const std::string & in_file, Container & dest){
    BitFileReader fileReader(in_file);

    fileReader = HuffmanDecoder<BitFileReader, Container>::initTable(std::move(fileReader));
    HuffmanDecoder<BitFileReader, Container>::decode(std::move(fileReader), BitFileReader(), dest);
}


#endif //HW03_HUFFMANFILEDECODER_H
