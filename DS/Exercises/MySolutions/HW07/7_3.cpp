#include <iostream>
#include <functional>
#include <vector>

namespace containers {

	template <class C, class T>
	class Heap {
	private:
		C cmp {};
		std::vector<T> data {};
		int parentOf(int);
		int greaterChildOf(int);

	public:
		void add(T);
		T top();
		void pop();
		int size();
	};

	struct Elem {
		int num;
		int arrayIndex;

		
	};

	template <class C, class T>
	int Heap<C, T>::parentOf(int x) {
		return ((x + 1) / 2) - 1;
	}

	template <class C, class T>
	int Heap<C, T>::greaterChildOf(int x) {
		int child1 = ((x + 1) * 2) - 1;
		int child2 = child1 + 1;

		if (child2 >= this->data.size() || cmp(this->data[child1], this->data[child2])) return child1;
		return child2;
	}

	template <class C, class T>
	void Heap<C, T>::add(T x) {
		this->data.push_back(x);
		int curIndex = this->data.size() - 1;

		// sift up
		while (curIndex > 0 && !cmp(this->data[parentOf(curIndex)], this->data[curIndex])) {
			std::swap(this->data[parentOf(curIndex)], this->data[curIndex]);
			curIndex = parentOf(curIndex);
		}
	}

	template <class C, class T>
	T Heap<C, T>::top() {
		return this->data.front();
	}

	template <class C, class T>
	void Heap<C, T>::pop() {
		std::swap(this->data.front(), this->data.back());
		this->data.pop_back();
		
		// sift down
		int curIndex = 0;
		while (greaterChildOf(curIndex) < this->data.size() && cmp(this->data[greaterChildOf(curIndex)], this->data[curIndex])) {
			int greaterChild = greaterChildOf(curIndex);
			std::swap(this->data[curIndex], this->data[greaterChild]);
			curIndex = greaterChild;
		}
	}

	template <class C, class T>
	int Heap<C, T>::size() {
		return this->data.size();
	}
	
	bool operator<=(const Elem& a, const Elem& b) {
		return a.num <= b.num;
	}
}

int main() {
	int k;
	std::cin >> k;

	std::vector<std::vector<containers::Elem>> arrays(k);
	std::vector<int> ptrs (k, 0);

	for (int i = 0; i < k; i++) {
		int ki;
		std::cin >> ki;

		for (int j = 0; j < ki; j++) {
			int curInput;
			std::cin >> curInput;

			arrays[i].push_back({curInput, i});
		}
	}

	containers::Heap<std::less_equal<containers::Elem>, containers::Elem> ptrHeap;

	for (int i = 0; i < k; i++) {
		ptrHeap.add(arrays[i][0]);
	} 

	while (ptrHeap.size() > 0) {
		auto curElem = ptrHeap.top();
		ptrHeap.pop();

		int curPtr = ++ptrs[curElem.arrayIndex];
		if (curPtr < arrays[curElem.arrayIndex].size()) ptrHeap.add(arrays[curElem.arrayIndex][curPtr]);

		std::cout << curElem.num << ' ';
	}

	std::cout << std::endl;
	return 0;
} 
