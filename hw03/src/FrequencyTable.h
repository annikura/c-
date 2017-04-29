#ifndef HW03_FREQUENCYTABLE_H
#define HW03_FREQUENCYTABLE_H

#include <map>
#include <fstream>
#include <iostream>

template <typename Container, typename T>
static Container & writeBinaryItem(Container & dest, T obj){
    for (size_t index = 0; index < sizeof(obj) * 8; index++) {
        std::cout << static_cast<bool>((obj >> index) & 1);
        dest.push_back(static_cast<bool>((obj >> index) & 1));
    }
    std::cout << std::endl;
    return dest;
}

template <typename Iterator, typename T>
static Iterator readBinaryItem(Iterator begin, T & obj) {
    Iterator it = std::move(begin);
    for (size_t index = 0; index < sizeof(obj) * 8; index++) {
        obj |= (static_cast<size_t >(*it) << static_cast<size_t >(index));
        ++it;
    }
    return it;
}

template <class Iterator, class Container>
class FrequencyTable {
private:
    std::map<uint8_t, size_t> table;
public:
    FrequencyTable() = default;
    FrequencyTable(Iterator begin, Iterator end);
    Iterator importBinary(Iterator begin);
    Container & exportBinary(Container & dest);
    size_t operator[](uint8_t key) const;
    size_t operator[](uint8_t key);
    void fillTable(Iterator begin, Iterator end);
    const std::map<uint8_t, size_t> & getMap() const;
    size_t size() const;
};

template <class Iterator, class Container>
FrequencyTable<Iterator, Container>::FrequencyTable(Iterator begin, Iterator end) {
    fillTable(begin, end);
}

template <class Iterator, class Container>
Iterator FrequencyTable<Iterator, Container>::importBinary(Iterator begin) {
    std::cout << "Binary\n";
    size_t size = 0;
    Iterator it = readBinaryItem(std::move(begin), size);
    for (size_t index = 0; index < size; index++){
        uint8_t  symbol = 0;
        size_t frequency = 0;
        it = readBinaryItem(std::move(it), symbol);
        it = readBinaryItem(std::move(it), frequency);
        table[symbol] = frequency;
    }
    return it;
}

template <class Iterator, class Container>
Container & FrequencyTable<Iterator, Container>::exportBinary(Container & dest) {
    writeBinaryItem(dest, size());
    for (auto el: table) {
        writeBinaryItem(dest, el.first);
        writeBinaryItem(dest, el.second);
    }
    return dest;
}

template <class Iterator, class Container>
size_t FrequencyTable<Iterator, Container>::operator[](uint8_t key) const{
    return table.find(key)->second;
}

template <class Iterator, class Container>
size_t FrequencyTable<Iterator, Container>::operator[](uint8_t key){
    return table[key];
}

template <class Iterator, class Container>
void FrequencyTable<Iterator, Container>::fillTable(Iterator begin, Iterator end) {
    for (Iterator it = begin; it != end; ++it)
        table[*it]++;
}

template <class Iterator, class Container>
const std::map<uint8_t, size_t> & FrequencyTable<Iterator, Container>::getMap() const{
    return table;
}

template <class Iterator, class Container>
size_t FrequencyTable<Iterator, Container>::size() const {
    return table.size();
}

#endif //HW03_FREQUENCYTABLE_H
