#ifndef HW03_BITFILEREADER_H
#define HW03_BITFILEREADER_H

#include <fstream>
#include <map>

class BitFileReader {
private:
    std::ifstream in;
    uint8_t read_byte = 0;
    std::string name = "";
    std::size_t cnt = 0;
    bool eof = true;
    static std::map<std::string, size_t> shared_space;

    void swap(BitFileReader & other);
public:
    BitFileReader() = default;
    BitFileReader(BitFileReader && other);
    BitFileReader(const std::string & filename);
    BitFileReader & operator=(BitFileReader other);

    bool operator*() const;
    bool isEof() const;
    BitFileReader & operator++();
    bool operator!=(const BitFileReader & other) const;
    uint8_t readByte();

    ~BitFileReader();
};



#endif //HW03_BITFILEREADER_H
