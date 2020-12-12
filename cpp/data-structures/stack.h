#ifndef STACK_H
#define STACK_H
#include "node.h"

template <typename T>
struct Stack
{
	Stack();
	Stack(shared_ptr<Node<T>> _top) : top(_top) { size += 1; }
	Stack(Node<T>& _top) {	top = make_shared<Node<T>> (top); size += 1; }
	Node<T> pop(); // Removes top node and returns it.
	void push(shared_ptr<Node<T>> newTop); // Add new top node
	void push(Node<T> &newTop); // Deletes
	bool isEmpty(); // Check if the stack has no member Node<T>.
	size_t getSize(); // Gets the number of elements in the stack.
	bool hasValue(T val); // Linear search for value
	Node<T>* begin(); // Begin iterator
private:
	std::shared_ptr<Node<T>> top; // Top node
	size_t size = 0; // Keeps track of the stack size
};

#endif
