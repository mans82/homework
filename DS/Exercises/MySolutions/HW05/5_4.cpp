#include <iostream>
#include <string>

namespace mans {
	template <typename T>
	class Stack {
		private:
			static constexpr unsigned int initialSizeOfElementsArray = 1;

			T* elements = new T[initialSizeOfElementsArray];

			int alloc_size = initialSizeOfElementsArray;
			int noe = 0;

			void doubleCapacity() {
				this->alloc_size *= 2;
				T* newElementsArray = new T[this->alloc_size];

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
			void push(T x) {
				if (isStackFull()) {
					doubleCapacity();
				}

				elements[noe++] = x;
			}

			T peek() {
				return this->elements[noe - 1];
			}

			T pop() {
				return this->elements[--noe];
			}

			int size() {
				return this->noe;
			}

			bool empty() {
				return this->noe == 0;
			}

			~Stack() {
				delete[] this->elements;
			}
	};
}

enum class ExprOperator : char {
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	POW = '^',
	PAR_OPEN = '(',
	DUMMY = '#'
};

bool operator<=(ExprOperator a, ExprOperator b) {
	int precedence_a, precedence_b;

	switch (a) {
		case ExprOperator::DUMMY:
		case ExprOperator::PAR_OPEN:
			precedence_a = 0;
			break;
		case ExprOperator::ADD:
		case ExprOperator::SUB:
			precedence_a = 1;
			break;
		case ExprOperator::MUL:
		case ExprOperator::DIV:
			precedence_a = 2;
			break;
		case ExprOperator::POW:
			precedence_a = 3;
	}
	
	switch (b) {
		case ExprOperator::DUMMY:
		case ExprOperator::PAR_OPEN:
			precedence_b = 0;
			break;
		case ExprOperator::ADD:
		case ExprOperator::SUB:
			precedence_b = 1;
			break;
		case ExprOperator::MUL:
		case ExprOperator::DIV:
			precedence_b = 2;
			break;
		case ExprOperator::POW:
			precedence_b = 3;
	}

	return precedence_a <= precedence_b;
}

bool isOperator(const char c) {
	switch (c) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '(':
		case ')':
			return true;
	}
	return false;
}

std::string toPostfix(const std::string infixExpr) {
	mans::Stack<ExprOperator> operators{};
	operators.push(ExprOperator::DUMMY); // To prevent the stack from becomming empty

	std::string result {};

	for (char c : infixExpr) {
		if (!isOperator(c)) result += c;
		else if (c == ')') {
			while (operators.peek() != ExprOperator::PAR_OPEN)
				result += static_cast<char>(operators.pop());
			operators.pop(); // Pop the reminaing opening parenthesis
			continue;
		} else if (c == '(')
			operators.push(ExprOperator::PAR_OPEN);
		else {

			ExprOperator curOp = static_cast<ExprOperator>(c);
			
			while (operators.peek() != ExprOperator::DUMMY && curOp <= operators.peek()) {
				result += static_cast<char>(operators.pop());
			}

			operators.push(curOp);
		}
	}

	while (operators.peek() != ExprOperator::DUMMY) {
		result += static_cast<char>(operators.pop());
	}

	return result;
}

int main() {
	
	std::string input;
	std::cin >> input;

	std::cout << toPostfix(input) << std::endl;
	return 0;
}
