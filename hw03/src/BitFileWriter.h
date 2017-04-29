#ifndef HW03_BITFILEWRITER_H
#define HW03_BITFILEWRITER_H


#include <fstream>

class BitFileWriter {
private:
    std::ofstream out;
    uint8_t for_record = 0;
    std::size_t cnt = 0;
    void writeByte();

public:
    BitFileWriter(const std::string & filename);

    void push_back(bool symbol);
    void push_back(char symbol);
    void flush();

    void open(const std::string & filename);
    void close();
};


#endif //HW03_BITFILEWRITER_H
