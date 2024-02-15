#include <iostream>
#include <string>

namespace mans {
	// The same implementation from question 1
	class Stack {
		private:
			static constexpr unsigned int initialSizeOfElementsArray = 1;

			int* elements = new int[initialSizeOfElementsArray];

			int alloc_size = initialSizeOfElementsArray;
			int noe = 0;

			void doubleCapacity() {
				this->alloc_size *= 2;
				int* newElementsArray = new int[this->alloc_size];

				// Copy elements from old array to new array
				for (int i = 0; i < this->noe; i++) {
					newElementsArray[i] = elements[i];
				}

				delete[] this->elements;
				this->elements = newElementsArray;
			}

			bool isStackFull() {
				return this->noe == this->alloc_size;
			}

		public:
			void push(int x) {
				if (isStackFull()) {
					doubleCapacity();
				}

				elements[noe++] = x;
			}

			int peek() {
				return this->elements[noe - 1];
			}

			int pop() {
				return this->elements[--noe];
			}

			int size() {
				return this->noe;
			}

			bool empty() {
				return this->noe == 0;
			}

			void printElements() {
				using std::cout;
				using std::endl;

				cout << '[';

				for (int i = 0; i < this->noe; i++) {
					cout << this->elements[i];
					if (i < this->noe - 1) cout << ", ";
				}

				cout << ']' << endl;
			}

			~Stack() {
				delete[] this->elements;
			}
	};

	class Queue {
		private:
			mans::Stack enqueued {};
			mans::Stack dequeued {};

			void pushAllOntoDequeued() {
				while (!this->enqueued.empty()) {
					this->dequeued.push(this->enqueued.pop());
				}
			}

		public:
			void enqueue(int x) {
				this->enqueued.push(x);
			}

			void dequeue() {
				if (this->dequeued.empty()) this->pushAllOntoDequeued();
				if (!this->dequeued.empty()) this->dequeued.pop();
			}

			void printElements() {
				using std::cout;
				using std::endl;

				cout << '[';

				while (!this->dequeued.empty()) {
					cout << this->dequeued.pop();
					if (!this->dequeued.empty() || !this->enqueued.empty()) cout << ", ";
				}

				this->pushAllOntoDequeued();

				while (!this->dequeued.empty()) {
					cout << this->dequeued.pop();
					if (!this->dequeued.empty()) cout << ", ";
				}
				
				cout << ']' << endl;
			}
	};
}

// Driver code
int main() {
	using std::cin;

	mans::Queue mainQueue {};

	std::string command;
	cin >> command;

	while (command != "print") {
		if (command == "add") {
			int x;
			cin >> x;

			mainQueue.enqueue(x);
		} else if (command == "remove") mainQueue.dequeue();
		cin >> command;
	}

	mainQueue.printElements();
	return 0;
}
