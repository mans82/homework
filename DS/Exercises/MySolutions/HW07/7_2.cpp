#include <iostream>
#include <functional>
#include <vector>

namespace containers {

	template <class C>
	class Heap {
	private:
		C cmp {};
		std::vector<int> data {};
		int parentOf(int);
		int greaterChildOf(int);

	public:
		void add(int);
		int top();
		void pop();
		int size();
	};

	template <class C>
	int Heap<C>::parentOf(int x) {
		return ((x + 1) / 2) - 1;
	}

	template <class C>
	int Heap<C>::greaterChildOf(int x) {
		int child1 = ((x + 1) * 2) - 1;
		int child2 = child1 + 1;

		if (child2 >= this->data.size() || cmp(this->data[child1], this->data[child2])) return child1;
		return child2;
	}

	template <class C>
	void Heap<C>::add(int x) {
		this->data.push_back(x);
		int curIndex = this->data.size() - 1;

		// sift up
		while (curIndex > 0 && !cmp(this->data[parentOf(curIndex)], this->data[curIndex])) {
			std::swap(this->data[parentOf(curIndex)], this->data[curIndex]);
			curIndex = parentOf(curIndex);
		}
	}

	template <class C>
	int Heap<C>::top() {
		return this->data.front();
	}

	template <class C>
	void Heap<C>::pop() {
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

	template <class C>
	int Heap<C>::size() {
		return this->data.size();
	}
}

int main() {
	containers::Heap<std::greater_equal<int>> firstHalf {};
	containers::Heap<std::less_equal<int>> secondHalf {};

	int n;
	std::cin >> n;

	for (int i = 0; i < n; i++) {
		int x;
		double median;
		std::cin >> x;

		if (i == 0) {
			secondHalf.add(x);
			std::cout << x << ".0" << std::endl;
			continue;
		}

		if (x < secondHalf.top()) {
			firstHalf.add(x);

			if (firstHalf.size() - 1 == secondHalf.size()) {
				int temp = firstHalf.top();
				firstHalf.pop();
				secondHalf.add(temp);
			}
		} else {
			secondHalf.add(x);

			if (secondHalf.size() - 1 > firstHalf.size()) {
				int temp = secondHalf.top();
				secondHalf.pop();
				firstHalf.add(temp);
			}
		}

		if (i % 2 == 0) {
			median = secondHalf.top();
		} else {
			median = (firstHalf.top() + secondHalf.top()) / (double)2.0;
		}

		std::printf("%.1lf\n", median);
	}

	return 0;

}
