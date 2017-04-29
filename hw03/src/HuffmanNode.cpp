#include <cassert>
#include <iostream>
#include "HuffmanNode.h"

std::size_t HuffmanNode::getId(){
    static std::size_t shared_id = 0;
    return shared_id++;
}

HuffmanNode::HuffmanNode(std::size_t cnt, uint8_t smbl) :
        count(cnt),
        symbol(smbl),
        id(getId()) { };

HuffmanNode *HuffmanNode::getChild(bool bit) const{
    return (bit ? right : left);
}

char HuffmanNode::getChildCode(HuffmanNode * child) const{
    assert(child->id == left->id || child->id == right->id);
    return (child == left ? '0' : '1');
}

HuffmanNode *HuffmanNode::getParent() const{
    return parent;
}

uint8_t HuffmanNode::getSymbol() const{
    return symbol;
}

bool HuffmanNode::isLeaf() const{
    return left == nullptr && right == nullptr;
}

void HuffmanNode::tieChildren(HuffmanNode *l, HuffmanNode *r){
    assert(l != nullptr);
    assert(r != nullptr);
    count = l->count + r->count;
    id = getId();
    left = l, right = r;
//    std::cerr << "Parent: " << this->id << " Left: " << left->id <<
//                                           " Right: " << right->id << std::endl;
}

void HuffmanNode::tieParent() {
    assert(left != nullptr);
    assert(right != nullptr);
    left->parent = right->parent = this;
}

bool HuffmanNode::less::operator()(HuffmanNode a, HuffmanNode b){
    return a.count < b.count || (a.count == b.count && a.id < b.id);
}
