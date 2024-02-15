#include <vector>
#include <iostream>
#include <functional>

namespace containers {

	class RankManager {
	private:
		struct Student {
			int id;
			int solved;
			int penal;

			bool operator>(const Student&);
			bool operator==(const Student&);
			bool operator<(const Student&);
			bool operator>=(const Student&);
			bool operator<=(const Student&);
		};

		std::vector<Student> all;
		std::vector<int> heap {{0}};
		std::vector<int> heapIndex;
		std::vector<bool> inHeap;

		int size();

		int parentOf(int);
		int smallerChildOf(int);

		void siftUp(int);
		void siftDown(int);
		void fix(int);
		void remove(int);

	public:
		RankManager(int);

		int addSub(int, int);
	};

	// Impl
	
	bool RankManager::Student::operator>(const RankManager::Student& b) {
		return this->solved > b.solved || (this->solved == b.solved && this->penal < b.penal);
	}

	bool RankManager::Student::operator==(const RankManager::Student& b) {
		return this->solved == b.solved && this->penal == b.penal;
	}

	bool RankManager::Student::operator<(const RankManager::Student& b) {
		return !(*this > b || *this == b);
	}

	bool RankManager::Student::operator>=(const RankManager::Student& b) {
		return *this > b || *this == b;
	}

	bool RankManager::Student::operator<=(const RankManager::Student& b) {
		return *this < b || *this == b;
	}
	
	int RankManager::size() {
		return heap.size();
	}
	
	int RankManager::parentOf(int heapIndex) {
		return ((heapIndex + 1) / 2) - 1;
	}

	int RankManager::smallerChildOf(int heapIndex) {
		int child1 = ((heapIndex + 1) * 2) - 1;
		int child2 = child1 + 1;
		if (child1 > size() - 1) return -1;
		if (child2 > size() - 1) return child1;

		return std::min(child1, child2, [this](int a, int b) {return all[heap[a]] < all[heap[b]];});
	}

	void RankManager::siftUp(int heapIndex) {
		int curIndex = heapIndex;
		int parent = parentOf(heapIndex);
		while (curIndex > 0 && all[heap[parent]] > all[heap[curIndex]]) {
			std::swap(heap[curIndex], heap[parent]);
			std::swap(this->heapIndex[heap[curIndex]], this->heapIndex[heap[parent]]);
			curIndex = parent;
			parent = parentOf(curIndex);
		}
	}

	void RankManager::siftDown(int heapIndex) {
		int curIndex = heapIndex;
		int smallerChild = smallerChildOf(curIndex);

		while (smallerChild != -1 && all[heap[smallerChild]] < all[heap[curIndex]]) {
			std::swap(heap[curIndex], heap[smallerChild]);
			std::swap(this->heapIndex[heap[curIndex]], this->heapIndex[heap[smallerChild]]);
			curIndex = smallerChild;
			smallerChild = smallerChildOf(curIndex);
		}
	}

	void RankManager::fix(int heapIndex) {
		// At most, one of the following will actually work
		siftUp(heapIndex);
		siftDown(heapIndex);
	}

	void RankManager::remove(int heapIndex) {
		inHeap[heap[heapIndex]] = false;
		std::swap(heap[heapIndex], heap.back());
		std::swap(this->heapIndex[heap[heapIndex]], this->heapIndex[heap.back()]);
		heap.pop_back();
		siftDown(heapIndex);
	}

	RankManager::RankManager(int n): all(n), heapIndex(n), inHeap(n, false) {
		inHeap[0] = true;
		heapIndex[0] = 0;
		for (int i = 0; i < n; i++) {
			all[i].id = i + 1;
			all[i].solved = all[i].penal = 0;
		}
	}

	int RankManager::addSub(int id, int penal) {
		all[id - 1].solved++;
		all[id - 1].penal += penal;

		if (id == 1) {
			fix(heapIndex[0]);
			while (heap.size() > 0 && heap[0] != 0) {
				remove(0);
			}
		} else {
			if (inHeap[id - 1]) {
				if (all[id - 1] > all[0]) fix(heapIndex[id - 1]);
				else remove(heapIndex[id - 1]);
			} else {
				if (all[id - 1] > all[0]) {
					inHeap[id - 1] = true;
					heap.push_back(id - 1);
					heapIndex[id - 1] = size() - 1;
					siftUp(heapIndex[id - 1]);
				}
			}
		}

		return size();
	}
}

int main() {
	int n, m;
	std::cin >> n >> m;

	containers::RankManager manager(n);

	for (int i = 0; i < m; i++) {
		int id, penal;
		std::cin >> id >> penal;

		std::cout << manager.addSub(id, penal) << std::endl;
	}

	return 0;
}

