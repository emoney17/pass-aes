#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

class Tree
{
    private:
        size_t dirs = 0;
        size_t files = 0;

        std::vector<std::string> inner_pointers = { "├── ", "│   " };
        std::vector<std::string> final_pointers = { "└── ", "    " };
    public:
        void walk(std::string directory, std::string prefix);
        void summary();
};

#endif // !TREE_HPP
