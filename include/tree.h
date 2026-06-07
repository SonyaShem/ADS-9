// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
struct Node {
    char value;
    std::vector<Node*> children;
    Node(char val) : value(val) {}
};

class PMTree {
  private:
    Node* root;
    void buildTree(Node* current, std::vector<char> remaining);
    void clearTree(Node* current);
  public:
    PMTree(std::vector<char> in);
    ~PMTree();
    Node* getRoot() const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
