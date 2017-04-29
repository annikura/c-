#ifndef HW03_HUFFMANTREE_H
#define HW03_HUFFMANTREE_H

#include <list>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <algorithm>
#include "HuffmanNode.h"
#include "FrequencyTable.h"

template<class Iterator, class Container>
class HuffmanTree {
private:
    std::list<HuffmanNode> vertices;
    std::map<uint8_t, HuffmanNode *> symbol_v;
    HuffmanNode root;
    HuffmanNode * placeTopVertexIntoTree(std::set<HuffmanNode, HuffmanNode::less> &vertex_set);
public:
    void build(const FrequencyTable<Iterator, Container> & frequency_table);
    Iterator getSymbol(Iterator begin, Iterator end, uint8_t & symbol) const;
    std::string getCode(uint8_t symbol) const;
};


template<class Iterator, class Container>
HuffmanNode * HuffmanTree<Iterator, Container>::placeTopVertexIntoTree(std::set<HuffmanNode, HuffmanNode::less> &vertex_set){
    /*
     * Erases top vertex from given set and adds it to the tree structure
     */
    HuffmanNode vertex = *vertex_set.begin();
    vertices.push_back(vertex);
    vertex_set.erase(vertex);
    if (vertex.isLeaf())
        symbol_v[vertex.getSymbol()] = &vertices.back();
    else
        vertices.back().tieParent();
    return &vertices.back();
}

template<class Iterator, class Container>
void HuffmanTree<Iterator, Container>::build(const FrequencyTable<Iterator, Container> & frequency_table){
    std::set<HuffmanNode, HuffmanNode::less> vertex_set;
    for (auto el: frequency_table.getMap()) {
        vertex_set.insert(HuffmanNode(el.second, el.first));
        if (frequency_table.size() == 1)
            vertex_set.insert(HuffmanNode(el.second, el.first));
    }
    HuffmanNode tmp_v;
    while (vertex_set.size() > 1){
        HuffmanNode * left = placeTopVertexIntoTree(vertex_set);
        HuffmanNode * right = placeTopVertexIntoTree(vertex_set);
        tmp_v.tieChildren(left, right);
        vertex_set.insert(tmp_v);
    }
    root = *vertex_set.begin();
    root.tieParent();
}

template<class Iterator, class Container>
Iterator HuffmanTree<Iterator, Container>::getSymbol(Iterator begin, Iterator end, uint8_t & symbol) const{
    HuffmanNode const * cur = &root;
    for (Iterator it = std::move(begin); it != end; ++it){
        cur = cur->getChild(*it);
        if (cur->isLeaf()){
            symbol = cur->getSymbol();
            return it;
        }
    }
    return end;
}

template<class Iterator, class Container>
std::string HuffmanTree<Iterator, Container>::getCode(uint8_t symbol) const{
    std::string ret;
    for (HuffmanNode *cur = symbol_v.find(symbol)->second; cur != &root; cur = cur->getParent()){
        ret += (cur->getParent())->getChildCode(cur);
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

#endif //HW03_HUFFMANTREE_H
