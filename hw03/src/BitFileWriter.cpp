#include <cassert>
#include "BitFileWriter.h"


void BitFileWriter::writeByte() {
    out.write(reinterpret_cast<char*>(&for_record), sizeof(for_record));
    cnt = for_record = 0;
}

BitFileWriter::BitFileWriter(const std::string & filename) {
    open(filename);
}

void BitFileWriter::push_back(bool symbol) {
    for_record |= (symbol << cnt++);
    if (cnt == 8)
        writeByte();
}


void BitFileWriter::push_back(char symbol){
    assert(symbol == '0' || symbol == '1');
    push_back(symbol == '1');
}

void BitFileWriter::flush() {
    writeByte();
}


void BitFileWriter::open(const std::string & filename) {
    assert(!out.is_open());
    out.open(filename, std::ios_base::binary);
    cnt = for_record = 0;
}
void BitFileWriter::close() {
    assert(out.is_open());
}
