#pragma once

#include <functional>
#include <string>

#include "shapes.h"

namespace containers {

    constexpr int ALPHABET_SIZE = 26 + 26 + 10;
    struct TrieNode {
        TrieNode* children[ALPHABET_SIZE] {};
        bool isEndOfWord;
        int data;
    };

    class Trie {
    private:
        TrieNode* root = new TrieNode {{}, false, 0};

        int indexOf(char);
        TrieNode* findNode(const std::string&);
        TrieNode* removeNode(const std::string&, TrieNode*, int);
        bool isLeaf(TrieNode*);
    public:
        void insert(const std::string&, int data);
        bool exists(const std::string&);
        int find(const std::string&);
        void remove(const std::string&);
    };

}