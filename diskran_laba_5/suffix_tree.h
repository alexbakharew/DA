#include <cstddef>
#include <map>
#include <vector>
#include <string>
#define MAX_LENGTH std::numeric_limits<std::size_t>::max()
class TNode 
{
public:
    using link = std::map<char, TNode *>;
    link edges;
    TNode *parent;
    TNode *suffixLink;
    std::size_t begin;
    std::size_t length;

    TNode(const std::string &, TNode * const &);
    TNode(const std::vector<char> &, const char &);
    TNode(const std::vector<char> &, const char &, TNode * const &);
    TNode(const std::string &, TNode * const &, const std::size_t &);

    virtual ~TNode();
};

class TSuffixTree;
class TSuffixArray;

class TSuffixArray
{
private:
    std::string text;
    std::vector<std::size_t> array;
public:
    explicit TSuffixArray(const TSuffixTree &);

    std::vector<std::size_t> Find(const std::string &pattern) const;

    virtual ~TSuffixArray();
};

class TSuffixTree
{
    public:
    std::string text;
    TNode *root;
    TNode *active_vertex;
    std::size_t activeLength;
    std::size_t activeCharIdx;

    void DFS(TNode * const &, std::vector<std::size_t> &, const std::size_t &) const;

    friend TSuffixArray::TSuffixArray(const TSuffixTree &);
    explicit TSuffixTree(const std::vector<char> &, const char &);
    void PushBack(char ch);
    virtual ~TSuffixTree();
};