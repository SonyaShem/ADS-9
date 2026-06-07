// Copyright 2022 NNTU-CS
#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree testTree(in);
    std::vector<std::vector<char>> perms = getAllPerms(testTree);
    std::cout << "All perms for 1,2,3:" << std::endl;
    for (size_t i = 0; i < perms.size(); ++i) {
        for (size_t j = 0; j < perms[i].size(); ++j) std::cout << perms[i][j];
        std::cout << std::endl;
    }
    std::vector<char> res1 = getPerm1(testTree, 2);
    std::vector<char> res2 = getPerm2(testTree, 2);
    std::cout << "getPerm1(2): ";
    for (size_t i = 0; i < res1.size(); ++i) std::cout << res1[i];
    std::cout << "\ngetPerm2(2): ";
    for (size_t i = 0; i < res2.size(); ++i) std::cout << res2[i];
    std::cout << std::endl;
    std::ofstream dataFile("result/data.txt");
    dataFile << "n getAllPerms getPerm1 getPerm2\n";
    for (int n = 1; n <= 9; ++n) {
        std::vector<char> alphabet;
        for (int i = 0; i < n; ++i) alphabet.push_back('1' + i);
        PMTree tree(alphabet);
        int total = 1;
        for (int i = 1; i <= n; ++i) total *= i;
        int targetNum = (rand() % total) + 1;
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<char>> a = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double tAll = std::chrono::duration<double, std::micro>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        std::vector<char> p1 = getPerm1(tree, targetNum);
        end = std::chrono::high_resolution_clock::now();
        double tP1 = std::chrono::duration<double, std::micro>(end - start).count();
        start = std::chrono::high_resolution_clock::now();
        std::vector<char> p2 = getPerm2(tree, targetNum);
        end = std::chrono::high_resolution_clock::now();
        double tP2 = std::chrono::duration<double, std::micro>(end - start).count();
        dataFile << n << " " << tAll << " " << tP1 << " " << tP2 << "\n";
        std::cout << "n=" << n << " processed." << std::endl;
    }
    dataFile.close();
    return 0;
}
