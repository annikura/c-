#include <cassert>
#include "BitFileReader.h"

std::map<std::string, size_t> BitFileReader::shared_space;

void BitFileReader::swap(BitFileReader & other){
    in.swap(other.in);
    std::swap(cnt, other.cnt);
    std::swap(eof, other.eof);
    std::swap(read_byte, other.read_byte);
}

BitFileReader::BitFileReader(const std::string & filename){
    eof = false;
    cnt = read_byte = 0;
    in.open(filename, std::ios_base::binary);
    name = filename;
    BitFileReader::shared_space[filename]++;

    read_byte = readByte();
}


BitFileReader::BitFileReader(BitFileReader && other) :
        in(move(other.in)),
        read_byte(other.read_byte),
        cnt(other.cnt),
        eof(other.eof) {}


BitFileReader & BitFileReader::operator=(BitFileReader other){
    this->swap(other);
    return *this;
}

bool BitFileReader::operator*() const{
    return static_cast<bool>((read_byte >> cnt) & 1);
}

uint8_t BitFileReader::readByte(){
    uint8_t x;
    in.read(reinterpret_cast<char*>(&x), sizeof(x));
    return x;
}

BitFileReader & BitFileReader::operator++(){
    assert(!eof);
    if (++cnt == 8) {
        read_byte = readByte();
        cnt = 0;
        if (in.eof())
            eof = true;
    }
    return *this;
}

bool BitFileReader::isEof() const{
    return eof;
}

bool BitFileReader::operator!=(const BitFileReader & other) const{
    return eof != other.eof;
}

BitFileReader::~BitFileReader() {
    if (name != "") {
        BitFileReader::shared_space[name];
        if (BitFileReader::shared_space[name] == 0) {
            assert(in.is_open());
            in.close();
        }
    }
}