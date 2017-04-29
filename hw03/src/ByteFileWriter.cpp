#include "ByteFileWriter.h"


ByteFileWriter::ByteFileWriter(const std::string & filname){
    out.open(filname);
}

void ByteFileWriter::push_back(char symbol){
    out << symbol;
}

void ByteFileWriter::close(){
    assert(out.is_open());
    out.close();
}
