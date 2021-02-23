#pragma once
template <typename T>
struct stack {
	// Adds an element to the top of the stack
	void push(const T& element) {
		// Allocate the top node
		node* newNode = new node{ element, nullptr };

		// The new node's next value is the top node
		newNode->next = top;

		// Set the new node as the top node
		top = newNode;
	}

	// Removes top element from the stack and returns it
	T pop() {
		node* temp = top;

		// Value to be returned
		T out = top->val;

		// Top is now the next node
		top = top->next;

		// Deallocate memory
		delete temp;

		return out;
	}

	// Return the top value in the stack
	T peek() const { return top->val; }

	// Returns whether the stack is empty
	bool empty() const { return !top; }
private:
	static struct node {
		// Value of the number
		T val;
		// Pointer to next node
		node* next = nullptr;
	};
	node* top = nullptr;
};
