#include <iostream>

namespace myContainers {

	class Tree {
		public:
			struct TreeNode {
				int value;
				int totalChildren;
				TreeNode* parent;
				TreeNode* left;
				TreeNode* right;
			};


			TreeNode* root();
			void add(int);
			// void updateChlidrenCounts();

		private:
			TreeNode* _root = nullptr;
	};

	int countGreaterInBST(Tree::TreeNode*, int);
	int countNodes(Tree::TreeNode*);

	// Implementations

	Tree::TreeNode* Tree::root() {
		return this->_root;
	}

	void Tree::add(int value) {
		if (this->_root == nullptr) this->_root = new Tree::TreeNode {value, 0, nullptr, nullptr, nullptr};
		else {
			Tree::TreeNode* curNode = this->_root;
			Tree::TreeNode* parent = nullptr;
			while (curNode != nullptr) {
				parent = curNode;
				parent->totalChildren++;
				if (value > curNode->value) curNode = curNode->right;
				else curNode = curNode->left;
			}
			Tree::TreeNode* newNode = new Tree::TreeNode {value, 0, nullptr, nullptr, nullptr};
			if (value > parent->value) parent->right = newNode;
			else parent->left = newNode;
		}
	}
	
	int countGreaterInBST(Tree::TreeNode* root, int value) {
		if (root == nullptr) return 0;
		if (root->value > value) return 1 + countNodes(root->right) + countGreaterInBST(root->left, value);
		else return countGreaterInBST(root->right, value);
	}

	int countNodes(Tree::TreeNode* root) {
		if (root == nullptr) return 0;
		return 1 + root->totalChildren;
	}
}



int main() {
	int n, m;
	std::cin >> n >> m;

	myContainers::Tree tree;

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		std::cin >> u >> v;

		// tree.addNode(u, v);
	}

	// tree.updateChlidrenCounts();

	for (int i = 0; i < n; i++) {
		int nodeValue;
		std::cin >> nodeValue;
		tree.add(nodeValue);
	}

	auto root = tree.root();

	for (int i = 0; i < m; i++) {
		int query;
		std::cin >> query;
		std::cout << myContainers::countGreaterInBST(root, query) << '\n';
	}

	return 0;
}
