#include <iostream>
#include <string>

namespace mans {
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
			static constexpr unsigned int initialSizeOfElementsArray = 1;

			int* elements = new int[initialSizeOfElementsArray];

			int alloc_size = initialSizeOfElementsArray;
			int noe = 0;

			int* front = nullptr;
			int* rear = nullptr;

			void doubleCapacity() {
				this->alloc_size *= 2;

				int* newElementsArray = new int[this->alloc_size];

				// Copy elements from old array to the new one
				for (int i = 0; i < noe; i++) {
					newElementsArray[i] = this->elements[i];
				}

				// Update queue pointers
				this->front = (this->front - this->elements) + newElementsArray;
				this->rear = (this->rear - this->elements) + newElementsArray;

				delete[] this->elements;
				this->elements = newElementsArray;
			}

			void shiftElementsToBeginning() {
				for (int i = 0; i < this->noe; i++) {
					this->elements[i] = this->front[i];
				}

				this->front = this->elements;
				this->rear = this->elements + this->noe - 1;
			}

			bool isQueueFull() {
				return this->noe == this->alloc_size;
			}

			bool isRearAtTheEnd() {
				return this->rear == this->front + this->noe - 1;
			}

		public:
			void enqueue(int x) {
				if (this->isQueueFull()) {
					this->doubleCapacity();
				}

				if (this->isRearAtTheEnd()) {
					this->shiftElementsToBeginning();
				}

				if (this->rear == nullptr) {
					this->elements[0] = x;
					this->front = this->rear = this->elements;
				} else {
					*(++this->rear) = x;
				}

				this->noe++;
			}

			void dequeue() {
				if (this->noe == 0) return;
				this->front++;
				this->noe--;
			}

			int peek() {
				return *(this->front);
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
					cout << this->front[i];
					if (i < this->noe - 1) cout << ", ";
				}

				cout << ']' << endl;
			}
	};
}

// Driver code
int main() {
	using std::cin;
	using std::cout;
	using std::endl;

	mans::Stack mainStack {};
	mans::Queue mainQueue {};

	std::string command;

	while (true) {
		cin >> command;

		if (command == "break") break;
		else if (command == "stack") {
			cin >> command;
			if (command == "push") {
				int x;
				cin >> x;

				mainStack.push(x);
			} else if (command == "pop") {
				if (!mainStack.empty()) {
					mainStack.pop();
				}
			} else if (command == "peek") {
				if (mainStack.empty()) cout << "null" << endl;
				else cout << mainStack.peek() << endl;
			} else if (command == "empty") {
				cout << (mainStack.empty() ? "true" : "false") << endl;
			}
		} else if (command == "queue") {
			cin >> command;
			if (command == "add") {
				int x;
				cin >> x;

				mainQueue.enqueue(x);
			} else if (command == "remove") {
				mainQueue.dequeue();
			} else if (command == "peek") {
				if (mainQueue.empty()) cout << "null" << endl;
				else cout << mainQueue.peek() << endl;
			} else if (command == "size") {
				cout << mainQueue.size() << endl;
			}
		}
	}
	
	mainStack.printElements();
	mainQueue.printElements();

	return 0;
	
}
