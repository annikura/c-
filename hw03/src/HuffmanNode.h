#ifndef HW03_HUFFMANNODE_H
#define HW03_HUFFMANNODE_H

#include <cstdint>

class HuffmanNode {
private:
    HuffmanNode *left = nullptr,
                *right = nullptr,
                *parent = nullptr;
    std::size_t id, count;
    uint8_t symbol;

    std::size_t getId();
public:
    HuffmanNode() = default;
    HuffmanNode(std::size_t cnt, uint8_t smbl);
    HuffmanNode *getChild(bool bit) const;
    char getChildCode(HuffmanNode * child) const;
    HuffmanNode *getParent() const;
    uint8_t getSymbol() const;
    bool isLeaf() const;
    void tieChildren(HuffmanNode *l, HuffmanNode *r);
    void tieParent();

    class less{
    public:
        bool operator()(HuffmanNode a, HuffmanNode b);
    };
};


#endif //HW03_HUFFMANNODE_H
