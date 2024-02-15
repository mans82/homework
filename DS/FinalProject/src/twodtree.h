#pragma once

#include <functional>

#include "shapes.h"
#include "vector.h"

namespace containers {

    template <typename T>
    struct TreeNode {
        TreeNode<T>* left;
        TreeNode<T>* right;
        bool isX;
        Point point;
        T* data;
    };

    template <typename T>
    class TwoDTree {
    private:
        TreeNode<T>* root = nullptr;

        TreeNode<T>* findmin(TreeNode<T>*, bool dimIsX);
        TreeNode<T>* find(Point);
        TreeNode<T>* removeNode(TreeNode<T>*, Point);
        TreeNode<T>* nearestNode(TreeNode<T>*, Point, TreeNode<T>*);
        int squaredDistance(Point, Point);
        Vector<T*> rangeSearchNode(TreeNode<T>*, Rectangle);
        Vector<T*> rangeSearchNode(TreeNode<T>*, Circle);
        bool isInRectangle(Point, Rectangle);
        bool isInCircle(Point, Circle);
        void traverseNode(TreeNode<T>*, std::function<void(T*)>);
    public:
        void insert(Point, T*);
        void remove(Point);
        T* dataAt(Point);
        bool exists(Point);
        T* nearest(Point);
        Vector<T*> rangeSearch(Rectangle);
        Vector<T*> rangeSearch(Circle);
        void travereseAll(std::function<void(T*)>);
    };
}

// Implementation of template classes
namespace containers {

    template<typename T>
    void TwoDTree<T>::insert(Point p, T* data) {
        TreeNode<T>* newNode = new TreeNode<T> {nullptr, nullptr, true, p, data};
        if (root == nullptr) root = newNode;
        else {
            TreeNode<T>* curNode = root;
            TreeNode<T>* prevNode = nullptr;
            
            while (curNode != nullptr) {
                prevNode = curNode;

                if ((curNode->isX && p.x > curNode->point.x) || (!curNode->isX && p.y > curNode->point.y)) curNode = curNode->right;
                else curNode = curNode->left;
            }

            newNode->isX = !prevNode->isX;
            if ((prevNode->isX && p.x > prevNode->point.x) || (!prevNode->isX && p.y > prevNode->point.y)) prevNode->right = newNode;
            else prevNode->left = newNode;
        }
    }

    template<typename T>
    TreeNode<T>* TwoDTree<T>::removeNode(TreeNode<T>* root, Point p) {
        if (root == nullptr) return nullptr;

        if (root->point == p) {
            if (root->right != nullptr) {
                TreeNode<T>* minNode = findmin(root->right, root->isX);
                root->point = minNode->point;
                root->data = minNode->data;
                root->right = removeNode(root->right, minNode->point);
            } else if (root->left != nullptr) {
                TreeNode<T>* minNode = findmin(root->left, root->isX);
                root->point = minNode->point;
                root->data = minNode->data;
                root->right = removeNode(root->left, minNode->point);
                root->left = nullptr;
            } else {
                // delete root->data;
                delete root;
                return nullptr;
            }
            return root;
        } else {
            if (root->isX) {
                if (p.x > root->point.x) root->right = removeNode(root->right, p);
                else root->left = removeNode(root->left, p);
            } else {
                if (p.y >root->point.y) root->right = removeNode(root->right, p);
                else root->left = removeNode(root->left, p);
            }

            return root;
        }
    }

    template<typename T>
    void TwoDTree<T>::remove(Point p) {
        this->root = removeNode(root, p);
    }

    template<typename T>
    TreeNode<T>* TwoDTree<T>::findmin(TreeNode<T>* root, bool isX) {
        if (root == nullptr) return nullptr;
        if (!root->left && !root->right) return root;
        if (root->isX == isX) {
            TreeNode<T>* leftMin = findmin(root->left, isX);
            if (leftMin == nullptr) return root;
            else {
                if (isX) return leftMin->point.x < root->point.x ? leftMin : root;
                else return leftMin->point.y < root->point.y ? leftMin : root;
            }
        } else {
            TreeNode<T>* leftMin = findmin(root->left, isX);
            TreeNode<T>* rightMin = findmin(root->right, isX);
            if (isX) {
                // TreeNode<T>* minSubTree = leftMin && leftMin->point.x < rightMin->point.x ? leftMin : rightMin;
                TreeNode<T>* minSubTree;
                if (!leftMin) minSubTree = rightMin;
                else if (!rightMin) minSubTree = leftMin;
                else minSubTree = leftMin->point.x < rightMin->point.x ? leftMin : rightMin;

                // return minSubTree && minSubTree->point.x < root->point.x ? minSubTree : root;
                return !minSubTree ? root : (minSubTree->point.x < root->point.x ? minSubTree : root);
            } else {
                TreeNode<T>* minSubTree;
                if (!leftMin) minSubTree = rightMin;
                else if (!rightMin) minSubTree = leftMin;
                else minSubTree = leftMin->point.y < rightMin->point.y ? leftMin : rightMin;

                // return minSubTree && minSubTree->point.x < root->point.x ? minSubTree : root;
                return !minSubTree ? root : (minSubTree->point.y < root->point.y ? minSubTree : root);
            }
        }
    }

    template<typename T>
    TreeNode<T>* TwoDTree<T>::find(Point p) {
        TreeNode<T>* curNode = root;
        while (curNode != nullptr && curNode->point != p) {
            if ((curNode->isX && p.x > curNode->point.x) || (!curNode->isX && p.y > curNode->point.y)) curNode = curNode->right;
            else curNode = curNode->left;
        }
        return curNode;
    }

    template<typename T>
    T* TwoDTree<T>::dataAt(Point p) {
        TreeNode<T>* node = this->find(p);
        return node ? node->data : nullptr;
    }

    template<typename T>
    bool TwoDTree<T>::exists(Point p) {
        return find(p);
    }

    template<typename T>
    TreeNode<T>* TwoDTree<T>::nearestNode(TreeNode<T>* root, Point p, TreeNode<T>* best) {
        if (root == nullptr) return best;
        TreeNode<T>* curBest = best;
        if (best == nullptr || squaredDistance(root->point, p) < squaredDistance(curBest->point, p)) curBest = root;
        // Find the good child
        TreeNode<T>* goodChild;
        TreeNode<T>* badChild;
        if (root->isX) {
            if (root->left && p.x < root->point.x) {
                goodChild = root->left;
                badChild = root->right;
            } else {
                goodChild = root->right;
                badChild = root->left;
            }
        } else {
            if (root->left && p.y < root->point.y) {
                goodChild = root->left;
                badChild = root->right;
            } else {
                goodChild = root->right;
                badChild = root->left;
            }
        }

        curBest = nearestNode(goodChild, p, curBest);

        // Trying to guess if badChild can still be a relevant candidate
        if (badChild != nullptr) {
            int discriminatorDistSq;
            if (root->isX) {
                discriminatorDistSq = badChild->point.x - curBest->point.x;
            } else {
                discriminatorDistSq = badChild->point.y - curBest->point.y;
            }
            discriminatorDistSq *= discriminatorDistSq;
            if (discriminatorDistSq <= squaredDistance(curBest->point, p)) curBest = nearestNode(badChild, p, curBest);
        }

        return curBest;
    }

    template<typename T>
    int TwoDTree<T>::squaredDistance(Point a, Point b) {
        return ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
    }

    template<typename T>
    T* TwoDTree<T>::nearest(Point p) {
        return root ? nearestNode(root, p, nullptr)->data : nullptr;
    }

    template<typename T>
    Vector<T*> TwoDTree<T>::rangeSearch(Rectangle r) {
        return rangeSearchNode(root, r);
    }

    template<typename T>
    Vector<T*> TwoDTree<T>::rangeSearchNode(TreeNode<T>* root, Rectangle r) {
        Vector<T*> result;
        if (root == nullptr) return result;
        
        if (isInRectangle(root->point, r)) result.pushBack(root->data);

        if (root->isX) {
            if (r.topLeft.x <= root->point.x) {
                Vector<T*> branchResult = rangeSearchNode(root->left, r);
                for (int i = 0; i < branchResult.size(); i++) {
                    result.pushBack(branchResult[i]);
                }
            }
            if (r.bottomRight.x >= root->point.x) {
                Vector<T*> branchResult = rangeSearchNode(root->right, r);
                for (int i = 0; i < branchResult.size(); i++) {
                    result.pushBack(branchResult[i]);
                }
            }
        } else {
            if (r.topLeft.y >= root->point.y) {
                Vector<T*> branchResult = rangeSearchNode(root->right, r);
                for (int i = 0; i < branchResult.size(); i++) {
                    result.pushBack(branchResult[i]);
                }
            }
            if (r.bottomRight.y <= root->point.y) {
                Vector<T*> branchResult = rangeSearchNode(root->left, r);
                for (int i = 0; i < branchResult.size(); i++) {
                    result.pushBack(branchResult[i]);
                }
            }
        }

        return result;
    }

    template<typename T>
    bool TwoDTree<T>::isInRectangle(Point p, Rectangle r) {
        return p.x >= r.topLeft.x && p.x <= r.bottomRight.x && p.y <= r.topLeft.y && p.y >= r.bottomRight.y; 
    }

    template<typename T>
    Vector<T*> TwoDTree<T>::rangeSearch(Circle c) {
        return rangeSearchNode(root, c);
    }

    template<typename T>
    Vector<T*> TwoDTree<T>::rangeSearchNode(TreeNode<T>* root, Circle c) {
        Vector<T*> result;
        if (root == nullptr) return result;

        if (isInCircle(root->point, c)) result.pushBack(root->data);

        int centerDisc, rootDisc; // centerDiscriminator, rootDiscriminator
        if (root->isX) {
            centerDisc = c.center.x;
            rootDisc = root->point.x;
        } else {
            centerDisc = c.center.y;
            rootDisc = root->point.y;
        }
        if (centerDisc <= rootDisc) {
            Vector<T*> branchResult = rangeSearchNode(root->left, c);
            for (int i = 0; i < branchResult.size(); i++) result.pushBack(branchResult[i]);
            if (centerDisc + c.radius >= rootDisc) {
                branchResult = rangeSearchNode(root->right, c);
                for (int i = 0; i < branchResult.size(); i++) result.pushBack(branchResult[i]);
            }
        } else {
            Vector<T*> branchResult = rangeSearchNode(root->right, c);
            for (int i = 0; i < branchResult.size(); i++) result.pushBack(branchResult[i]);
            if (centerDisc - c.radius <= rootDisc) {
                branchResult = rangeSearchNode(root->left, c);
                for (int i = 0; i < branchResult.size(); i++) result.pushBack(branchResult[i]);
            }
        }

        return result;
    }

    template<typename T>
    bool TwoDTree<T>::isInCircle(Point p, Circle c) {
        return squaredDistance(p, c.center) <= c.radius * c.radius;
    }

    template<typename T>
    void TwoDTree<T>::traverseNode(TreeNode<T>* root, std::function<void(T*)> f) {
        if (root == nullptr) return;
        f(root->data);
        traverseNode(root->left, f);
        traverseNode(root->right, f);
    }

    template<typename T>
    void TwoDTree<T>::travereseAll(std::function<void(T*)> f) {
        traverseNode(root, f);
    }

}