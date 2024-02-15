#include <iostream>

namespace myContainers {

	class Tree {
		public:
			struct TreeNode;

			Tree(int);
			TreeNode* root();
			void addNode(int, int);

		private:
			TreeNode* allNodes;
			int _size = 0;
	};

	struct Tree::TreeNode {
		private:
			class ChildrenList{
				private:
					struct ListNode;

					ListNode* _first = nullptr;
					ListNode* _last = nullptr;
					int _size = 0;

				public:
					ListNode* first();
					ListNode* next(ListNode*);
					int size();

					void add(Tree::TreeNode*);
			};

		public:
			int data;
			TreeNode* parent;

			ChildrenList children {};
	};

	struct Tree::TreeNode::ChildrenList::ListNode {
		Tree::TreeNode* data;
		ListNode* next;
	};

	void printPreOrder(Tree::TreeNode*);
	void printInOrder(Tree::TreeNode*);
	void printPostOrder(Tree::TreeNode*);

	// Implementations

	Tree::TreeNode::ChildrenList::ListNode* Tree::TreeNode::ChildrenList::first() {
		return this->_first;
	}

	Tree::TreeNode::ChildrenList::ListNode* Tree::TreeNode::ChildrenList::next(ListNode* node) {
		return node->next;
	}
	
	int Tree::TreeNode::ChildrenList::size() {
		return this->_size;
	}

	void Tree::TreeNode::ChildrenList::add(TreeNode* data) {
		ListNode* newNode = new ListNode;

		newNode->data = data;
		newNode->next = nullptr;

		if (this->_size == 0)
			this->_first = this->_last = newNode;
		else {
			this->_last->next = newNode;
			this->_last = this->_last->next;
		}

		this->_size++;
	}


	Tree::Tree(int nodes):
		allNodes {new TreeNode[nodes]}, _size {nodes}
	{
		for (int i = 0; i < nodes; i++) {
			this->allNodes[i].data = i + 1;
			this->allNodes[i].parent = nullptr;
		}
	}

	Tree::TreeNode* Tree::root() {
		for (int i = 0; i < this->_size; i++) {
			if (this->allNodes[i].parent == nullptr) return &(this->allNodes[i]);
		}

		return nullptr;
	}

	void Tree::addNode(int parent, int child) {
		this->allNodes[child - 1].parent = &(this->allNodes[parent - 1]);
		this->allNodes[parent - 1].children.add(&(this->allNodes[child - 1]));
	} 


	void printPreOrder(Tree::TreeNode* root) {
		std::cout << root->data << ' ';

		auto currentChild = root->children.first();
		for (int i = 0; i < root->children.size(); i++) {
			printPreOrder(currentChild->data);
			currentChild = root->children.next(currentChild);
		}
	}

	void printInOrder(Tree::TreeNode* root) {
		auto currentChild = root->children.first();
		int totalChildren = root->children.size();
		int indexOfHalf = (totalChildren + (totalChildren % 2)) / 2; 
		int i;
		for (i = 0; i < indexOfHalf; i++) {
			printInOrder(currentChild->data);
			currentChild = root->children.next(currentChild);
		}

		std::cout << root->data << ' ';

		for (; i < totalChildren; i++) {
			printInOrder(currentChild->data);
			currentChild = root->children.next(currentChild);
		}
	}

	void printPostOrder(Tree::TreeNode* root) {
		auto currentChild = root->children.first();
		for (int i = 0; i < root->children.size(); i++) {
			printPostOrder(currentChild->data);
			currentChild = root->children.next(currentChild);
		}
		
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
	myContainers::printInOrder(root);
	std::cout << std::endl;
	myContainers::printPostOrder(root);
	std::cout << std::endl;

	return 0;
}
