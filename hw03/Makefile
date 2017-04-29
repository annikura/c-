.PHONY: all clean 

CC = g++
CFLAGS = -std=c++11 -g -Isrc -Wall -Wextra -Wshadow -fsanitize=undefined -D_GLIBCXX_DEBUG

main.cpp = src/main.cpp
HuffmanNode.cpp = src/HuffmanNode.cpp
BitFileWriter.cpp = src/BitFileWriter.cpp
BitFileReader.cpp = src/BitFileReader.cpp
ByteFileWriter.cpp = src/ByteFileWriter.cpp

HuffmanNode.h = src/HuffmanNode.h
BitFileWriter.h = src/BitFileWriter.h
BitFileReader.h = src/BitFileReader.h
ByteFileWriter.h = src/ByteFileWriter.h
FrequencyTable.h = src/FrequencyTable.h
HuffmanTree.h = src/HuffmanTree.h
HuffmanEncoder.h = src/HuffmanEncoder.h
HuffmanDecoder.h = src/HuffmanDecoder.h

test.cpp = test_dir/test.cpp

test.o = bin/test.o
main.o = bin/main.o
HuffmanNode.o = bin/HuffmanNode.o
BitFileWriter.o = bin/BitFileWriter.o
BitFileReader.o = bin/BitFileReader.o
ByteFileWriter.o = bin/ByteFileWriter.o

all: main test

main: bin $(main.o) $(HuffmanNode.o) $(BitFileReader.o) $(BitFileWriter.o) $(ByteFileWriter.o)
	$(CC) $(CFLAGS) $(main.o) $(HuffmanNode.o) $(BitFileReader.o) $(BitFileWriter.o) $(ByteFileWriter.o) -o main

test: bin $(test.o) $(HuffmanNode.o) $(BitFileReader.o) $(BitFileWriter.o) $(ByteFileWriter.o)
	$(CC) $(CFLAGS) $(test.o) $(HuffmanNode.o) $(BitFileReader.o) $(BitFileWriter.o) $(ByteFileWriter.o) -o test -lgtest

$(test.o): $(test.cpp) $(FrequencyTable.h)
	$(CC) -c $(CFLAGS) $(test.cpp) -o $(test.o)

$(main.o): $(main.cpp) $(FrequencyTable.h) $(HuffmanTree.h) $(HuffmanEncoder.h) $(HuffmanDecoder.h)
	$(CC) -c  $(main.cpp) -o $(main.o) $(CFLAGS)
	
$(HuffmanNode.o): $(HuffmanNode.cpp) $(HuffmanNode.h)
	$(CC) -c  $(HuffmanNode.cpp) -o $(HuffmanNode.o) $(CFLAGS)

$(BitFileWriter.o): $(BitFileWriter.cpp) $(BitFileWriter.h)
	$(CC) -c  $(BitFileWriter.cpp) -o $(BitFileWriter.o) $(CFLAGS)

$(BitFileReader.o): $(BitFileReader.cpp) $(BitFileReader.h)
	$(CC) -c  $(BitFileReader.cpp) -o $(BitFileReader.o) $(CFLAGS)

$(ByteFileWriter.o): $(ByteFileWriter.cpp) $(ByteFileWriter.h)
	$(CC) -c  $(ByteFileWriter.cpp) -o $(ByteFileWriter.o) $(CFLAGS)

bin:
	mkdir bin

clean:
	rm -rf bin main test


	
