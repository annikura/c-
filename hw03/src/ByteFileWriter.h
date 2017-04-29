#ifndef HW03_BYTEFILEWRITER_H
#define HW03_BYTEFILEWRITER_H


#include <fstream>
#include <cassert>

class ByteFileWriter {
private:
    std::ofstream out;
public:
    ByteFileWriter(const std::string & filname);
    void push_back(char symbol);
    void close();
};

#endif //HW03_BYTEFILEWRITER_H
