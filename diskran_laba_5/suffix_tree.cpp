#include <algorithm>
#include <iostream>
#include "suffix_tree.h"

TNode::TNode(const std::string &text, TNode* const &node) 
{
    parent = node;
    suffixLink = nullptr;
    begin = text.size() - 1;
    length = MAX_LENGTH;
    node->edges.insert(std::pair<char, TNode *>(text.back(), this));
}

TNode::TNode(const std::vector<char> &words, const char &spec) 
{
    parent = nullptr;
    suffixLink = nullptr;
    begin = 0;
    length = 0;
    suffixLink = new TNode(words, spec, this);
}

//Buddy node create
TNode::TNode(const std::vector<char> &alpha, const char &spec, TNode * const &root) 
{
    parent = nullptr;
    suffixLink = nullptr;
    begin = 0;
    length = 0;
    for (auto it:alpha)
        edges.insert(std::pair<char, TNode *>(it, root));
    edges.insert(std::pair<char, TNode *>(spec, root));
}

TNode::TNode(const std::string &text, TNode* const &node, const std::size_t &pos) 
{
    suffixLink = nullptr;
    begin = node->begin;
    length = pos;
    parent =node->parent;
    edges = { std::pair<char, TNode *>(text[node->begin + pos], node) };
    new TNode(text, this);
    node->parent->edges.at(text[node->begin]) = this;
    node->parent = this;
    node->begin = node->begin + pos;
    if (node->length != MAX_LENGTH)
        node->length = node->length - pos;
}
TNode::~TNode()
{
    for (auto &edge : edges) 
        delete edge.second;
}

TSuffixTree::TSuffixTree(const std::vector<char> &ch, const char &spec) 
{
    text = "";
    activeCharIdx = 0;
    activeLength = 0;
    active_vertex = root = new TNode(ch, spec);
}
void TSuffixTree::PushBack(const char &new_ch)
{
    text.push_back(new_ch);
    std::map<char, TNode *>::iterator it = active_vertex->edges.end();
    TNode *last_visit = nullptr;
    while ((activeLength < active_vertex->length && text[active_vertex->begin + activeLength] != new_ch)
           || (it = active_vertex->edges.find(new_ch), activeLength >= active_vertex->length
                                                       && it == active_vertex->edges.end())) 
    {
        //Create new external vertex
        if (activeLength < active_vertex->length && text[active_vertex->begin + activeLength] != new_ch) 
        {
            TNode *temp = new TNode(text, active_vertex, activeLength);
            if (last_visit != nullptr) 
                last_visit->suffixLink = temp;// в эту вершину необходимо добавить суффиксную ссылку
            last_visit = active_vertex->parent;
            active_vertex = last_visit->parent->suffixLink->edges.at(text[activeCharIdx]);
            if (active_vertex == root)
            {
                --activeLength;
                ++activeCharIdx;
            }
            for (std::size_t length; activeLength > active_vertex->length; activeLength -= length) 
            {
                length = active_vertex->length;
                activeCharIdx += length;
                active_vertex = active_vertex->edges.at(text[activeCharIdx]);
            }
        } 
        else 
        {
            //create leaf
            new TNode(text, active_vertex);
            if (last_visit != nullptr) 
            {
                last_visit->suffixLink = active_vertex;
                last_visit = nullptr;
            }
            if (active_vertex != root) 
            {
                active_vertex = active_vertex->suffixLink;
                activeLength = active_vertex->length;
            }
        }
    }
    if (last_visit != nullptr)
        last_visit->suffixLink = active_vertex;
    if (activeLength >= active_vertex->length && it != active_vertex->edges.end() && it->second->begin < text.size() - 1) 
    {
        activeLength = 1;//новая вершина на дуге, которую необходимо разбить
        active_vertex = it->second;// a|bbb
        activeCharIdx = active_vertex->begin;
    }
    else 
        ++activeLength;
}
void TSuffixTree::DFS(TNode * const &curr, std::vector<std::size_t> &result, const std::size_t &summary) const
{
    if (curr->edges.empty()) 
    {
        result.push_back(text.size() - summary);
        return;
    }
    for (auto it : curr->edges) 
    {
        std::size_t temp = summary;
        if (it.second->length == MAX_LENGTH) 
            temp += text.size() - it.second->begin;
        else
            temp += it.second->length;
        DFS(it.second, result, temp);
    }
}

TSuffixTree::~TSuffixTree() 
{
    root->suffixLink->edges.clear();
    delete root->suffixLink;
    delete root;
}

TSuffixArray::TSuffixArray(const TSuffixTree &tree)
{
    text = tree.text;
    tree.DFS(tree.root, array, 0);
}
std::vector<std::size_t> TSuffixArray::Find(const std::string &pattern) const 
{
    std::pair<std::vector<std::size_t>::const_iterator, std::vector<std::size_t>::const_iterator> range(array.begin(), array.end());
    for (std::size_t i = 0; i < pattern.size() && range.first != range.second; ++i) 
    {
        range = equal_range(range.first, range.second, MAX_LENGTH,
                            [this, &pattern, &i] (std::size_t first, std::size_t second) -> bool {
            if (first == MAX_LENGTH) {
                return bool(pattern[i] < text[i + second]);
            } else {
                return bool(text[i + first] < pattern[i]);
            }
        });
    }
    std::vector<std::size_t> result(range.first, range.second);
    std::sort(result.begin(), result.end());
    return result;
}

TSuffixArray::~TSuffixArray() {}