#include <iostream>
#include <vector>
#include <algorithm>

namespace myContainers {

	class Tree {
		public:
			struct TreeNode;

			Tree(int);
			TreeNode* root();
			void addNode(int, int);
			void convertToBST();

		private:
			TreeNode** allNodes;
			int _size = 0;

			void setValuesInOrder(Tree::TreeNode*, std::vector<int>, int&);
	};

	struct Tree::TreeNode {
		public:
			int data;
			TreeNode* parent;
			TreeNode* left;
			TreeNode* right;
	};

	void printPreOrder(Tree::TreeNode*);
	void printInOrder(Tree::TreeNode*);
	void printPostOrder(Tree::TreeNode*);

	// Implementations


	Tree::Tree(int nodes):
		allNodes {new TreeNode*[100000] {nullptr}}, _size {nodes}
	{
	}

	Tree::TreeNode* Tree::root() {
		for (int i = 0; i < 100000; i++) {
			if (this->allNodes[i] != nullptr && this->allNodes[i]->parent == nullptr) return this->allNodes[i];
		}

		return nullptr;
	}

	void Tree::addNode(int parent, int child) {
		if (allNodes[parent - 1] == nullptr) allNodes[parent - 1] = new Tree::TreeNode {parent, nullptr, nullptr, nullptr};
		if (allNodes[child - 1] == nullptr) allNodes[child - 1] = new Tree::TreeNode {child, nullptr, nullptr, nullptr};

		allNodes[child - 1]->parent = allNodes[parent - 1];
		if (allNodes[parent - 1]->left == nullptr) allNodes[parent - 1]->left = allNodes[child - 1];
		else allNodes[parent - 1]->right = allNodes[child - 1];
	} 

	void Tree::convertToBST() {
		std::vector<int> elements;
		for (int i = 0; i < 100000; i++) {
			if (allNodes[i] != nullptr) elements.push_back(allNodes[i]->data);
		}

		std::sort(elements.begin(), elements.end());

		int startingIndex = 0;
		setValuesInOrder(this->root(), elements, startingIndex);
	}

	void Tree::setValuesInOrder(Tree::TreeNode* root, std::vector<int> elements, int& index) {
		if (root == nullptr) return;
		setValuesInOrder(root->left, elements, index);
		root->data = elements[index++];
		setValuesInOrder(root->right, elements, index);
	}


	void printPreOrder(Tree::TreeNode* root) {
		if (root == nullptr) return;
		if (root->left == nullptr && root->right == nullptr) std::cout << root->data << ' ';
		else {
			printPreOrder(root->left);
			printPreOrder(root->right);
		}
	}

	void printInOrder(Tree::TreeNode* root) {
		if (root == nullptr) return;
		printInOrder(root->left);
		std::cout << root->data << ' ';
		printInOrder(root->right);
	}

	void printPostOrder(Tree::TreeNode* root) {
		if (root == nullptr) return;
		printPostOrder(root->left);
		printPostOrder(root->right);
		std::cout << root->data << ' ';
	}
}

int main() {
	int n;
	std::cin >> n;

	myContainers::Tree tree(n);

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		std::cin >> u >> v;

		tree.addNode(u, v);
	}

	auto root = tree.root();

	myContainers::printPreOrder(root);
	std::cout << std::endl;

	tree.convertToBST();
	root = tree.root();

	myContainers::printInOrder(root);
	std::cout << std::endl;
	myContainers::printPostOrder(root);
	std::cout << std::endl;

	return 0;
}
