#ifndef STACK_H
#define STACK_H
#include "node.h"

template <typename T>
struct Stack
{
	Stack(shared_ptr<Node<T>> _top = nullptr) : top(_top) { size += 1; }
	Stack(Node<T>& _top) {	top = make_shared<Node<T>> (top); size += 1; }
	Node<T> pop(); // Remove top Node<T>
	void push(shared_ptr<Node<T>> newTop); // Add new top Node<T>
	void push(Node<T> &newTop);
	bool isEmpty(); // Check if the stack has no member Node<T>s.
	size_t getSize();
	bool hasValue(T val);
	Node<T>* begin();
private:
	std::shared_ptr<Node<T>> top;
	size_t size = 0;
};

#endif
