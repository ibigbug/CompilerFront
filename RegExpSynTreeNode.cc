#include "RegExpSynTreeNode.h"

#include <string>

RegExpSynTreeNode::RegExpSynTreeNode(const char*, const char*,
        RegExpSynTreeNodeType type, int pos)
    :isUnit_(0), position_(pos), type_(type)
{
}

RegExpSynTreeNode::RegExpSynTreeNode(RegExpSynTreeNodeType type, int pos)
    :isUnit_(0), position_(pos), type_(type)
{
}

bool RegExpSynTreeNode::IsLeafNode() const
{
    return type_ == RegExpSynTreeNodeType_Leaf;
}

const std::string& RegExpSynTreeNode::GetNodeText() const
{
    return text_;
}

// star node

RegExpSynTreeStarNode::RegExpSynTreeStarNode(int min, int max)
    :RegExpSynTreeNode(RegExpSynTreeNodeType_Star)
    ,min_(min), max_(max)
{
}

// leaf node

RegExpSynTreeLeafNode::RegExpSynTreeLeafNode(const char* s, const char* e, int pos)
    :RegExpSynTreeNode(s, e, RegExpSynTreeNodeType_Leaf, pos)
    ,leafType_(RegExpSynTreeNodeLeafNodeType_None)
{
    if (*s == '\\')
    {
        leafType_ = RegExpSynTreeNodeLeafNodeType_Esc;
        text_ = *(s + 1);
    }
    else if (*s == '[')
    {
        leafType_ = RegExpSynTreeNodeLeafNodeType_Alt;
        text_ = std::string(s + 1, e - s - 1);
    }
    else if (*s == '^')
    {
        leafType_ = RegExpSynTreeNodeLeafNodeType_Head;
        text_ = *s;
    }
    else if (*s == '$')
    {
        leafType_ = RegExpSynTreeNodeLeafNodeType_Tail;
        text_ = *s;
    }
    else if (*s == '.')
    {
        leafType_ = RegExpSynTreeNodeLeafNodeType_Dot;
        text_ = *s;
    }
    else
    {
        leafType_ = RegExpSynTreeNodeLeafNodeType_Norm;
        text_ = *s;
    }
}

