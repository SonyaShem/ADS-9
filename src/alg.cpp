// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <vector>
#include  "tree.h"

PMTree::PMTree(std::vector<char> in) {
    root = new Node('\0');
    std::sort(in.begin(), in.end());
    buildTree(root, in);
}
PMTree::~PMTree() {
    clearTree(root);
}
Node* PMTree::getRoot() const {
    return root;
}
void PMTree::buildTree(Node* current, std::vector<char> remaining) {
    if (remaining.empty()) return;
    for (size_t i = 0; i < remaining.size(); ++i) {
        Node* child = new Node(remaining[i]);
        current->children.push_back(child);
        std::vector<char> nextRemaining = remaining;
        nextRemaining.erase(nextRemaining.begin() + i);
        buildTree(child, nextRemaining);
    }
}
void clearTree(Node* current) {
    if (!current) return;
    for (size_t i = 0; i < current->children.size(); ++i) {
        clearTree(current->children[i]);
    }
    delete current;
}
void collectPerms(Node* node, std::vector<char>& currentPath,
                  std::vector<std::vector<char>>& result) {
    if (!node) return;
    if (node->value != '\0') {
        currentPath.push_back(node->value);
    }
    if (node->children.empty() && node->value != '\0') {
        result.push_back(currentPath);
    } else {
        for (size_t i = 0; i < node->children.size(); ++i) {
            collectPerms(node->children[i], currentPath, result);
        }
    }
    if (node->value != '\0') {
        currentPath.pop_back();
    }
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> currentPath;
    collectPerms(tree.getRoot(), currentPath, result);
    return result;
}
std::vector<char> getPerm1(const PMTree& tree, int num) {
    if (num <= 0) return std::vector<char>();
    std::vector<std::vector<char>> all = getAllPerms(tree);
    if (num > static_cast<int>(all.size())) return std::vector<char>();
    return all[num - 1];
}
int factorial(int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i) res *= i;
    return res;
}
std::vector<char> getPerm2(const PMTree& tree, int num) {
    if (num <= 0) return std::vector<char>();
    Node* current = tree.getRoot();
    if (!current || current->children.empty()) return std::vector<char>();
    int n = current->children.size();
    int totalPerms = factorial(n);
    if (num > totalPerms) return std::vector<char>();
    std::vector<char> result;
    int k = num - 1;
    while (!current->children.empty()) {
        int m = current->children.size();
        int subTreeCount = factorial(m - 1);
        int idx = k / subTreeCount;
        k = k % subTreeCount;
        current = current->children[idx];
        result.push_back(current->value);
    }
    return result;
}
