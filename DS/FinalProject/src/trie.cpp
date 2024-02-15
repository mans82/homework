#include <string>
#include <functional>

#include "trie.h"

namespace containers {
    int Trie::indexOf(char c) {
        if (c >= 'a' && c <= 'z') return c - 'a';
        if (c >= 'A' && c <= 'Z') return c - 'A' + ('z' - 'a' + 1);
        if (c >= '0' && c <= '9') return c - '0' + 2 * ('z' - 'a' + 1);
        return -1;
    }

    TrieNode* Trie::findNode(const std::string& k) {
        TrieNode* curNode = root;
        for (char c : k) {
            if (curNode->children[indexOf(c)] == nullptr) return nullptr;
            else curNode = curNode->children[indexOf(c)];
        }
        return curNode->isEndOfWord ? curNode : nullptr;
    }

    void Trie::insert(const std::string& k, int data) {
        TrieNode* curNode = root;
        for (char c : k) {
            if (curNode->children[indexOf(c)] == nullptr) {
                curNode->children[indexOf(c)] = new TrieNode {{}, false, 0};
            }
            curNode = curNode->children[indexOf(c)];
        }

        curNode->isEndOfWord = true;
        curNode->data = data;
    }

    bool Trie::exists(const std::string& k) {
        return findNode(k);
    }

    int Trie::find(const std::string& k) {
        TrieNode* foundNode = findNode(k);
        return foundNode ? foundNode->data : -1;
    }

    void Trie::remove(const std::string& k) {
        removeNode(k, root, 0);
    }

    TrieNode* Trie::removeNode(const std::string& k, TrieNode* root, int depth) {
        if (root == nullptr) return nullptr;
        
        if (k.size() == depth) {
            root->isEndOfWord = false;
            if (isLeaf(root)) {
                delete root;
                return nullptr;
            }
        } else {
            auto& child = root->children[indexOf(k[depth])];
            child = removeNode(k, child, depth + 1);

            if (isLeaf(root)) {
                delete root;
                return nullptr;
            }
        }

        return root;
    }

    bool Trie::isLeaf(TrieNode* node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) return false;
        }

        return true;
    }
}