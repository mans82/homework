#include <bits/stdc++.h>

using namespace std;

struct Node {
	Node* next;
	int val;
};

Node* revList(Node* head, int n) {
	if (!head && !head->next) return head;

	Node* prev = nullptr;
	Node* cur = head;
	Node* next = head->next;

	for (int i = 0; i < n; i++) {

		cur->next = prev;

		prev = cur;
		cur = next;
		
		if (next) next = next->next;
	}

	head->next = cur;
	return prev;

}

void printList(Node* head) {
	Node* cur = head;

	while (cur) {
		cout << cur->val;
		cur = cur->next;
	}

	cout << '\n';
}

int lenList(Node* head) {
	Node* cur = head;
	int res = 0;

	while (cur) {
		res++;
		cur = cur->next;
	}

	return res;
}

Node* Baraxeshkn(Node* head, int k, int n) {
	if (k == 0) return head;
	int rlen = n / k;

	//Node* dummy = new Node {head, -1};
	Node dummyS {head, -1};
	Node* dummy = &dummyS;

	Node* cur = head;
	Node* prev = dummy;

	for (int i = 0; i < rlen; i++) {

		Node* revdList = revList(cur, k);
		prev->next = revdList;

		prev = cur;
		cur = cur->next;
	}

	Node* res = dummy->next;
	//delete dummy;
	return res;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int q, n;
	cin >> q >> n;

	Node dummyS {nullptr, -1};
	Node* dummy = &dummyS;

	Node* cur = dummy;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		cur->next = new Node {nullptr, x};
		cur = cur->next;
	}

	for (int i = 0; i < q; i++) {
		int k;
		cin >> k;
		dummy->next = Baraxeshkn(dummy->next, k, n);
	}

	printList(dummy->next);

}
