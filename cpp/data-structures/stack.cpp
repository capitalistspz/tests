#include "stack.h"
// Comments in header file 
template <typename T>
Node<T> Stack<T>::pop() {
	std::shared_ptr<Node> x = top;
	top = top->next;
	x->next = nullptr;
	--size;
	return *x;
}

template <typename T>
void Stack<T>::push(std::shared_ptr<Node<T>> newTop) {
	newTop->next = top;
	top = newTop;
	++size;
}
template <typename T>
void Stack<T>::push(Node<T> &newTop) {
	newTop.next = top;
	top = std::make_shared<Node<T>>(newTop);
	++size;
}
template <typename T>
bool Stack<T>::isEmpty() {
	return top != nullptr;
}
template <typename T>
size_t Stack<T>::getSize() {
	return size;
}
template <typename T>
bool Stack<T>::hasValue(T val) {
	std::shared_ptr<Node<T>> iter = top;
	while (iter != nullptr) {
		if (iter->val == val)
			return true;
		iter = iter->next;
	}
	return false;
}

template <typename T>
Node<T>* Stack<T>::begin() {
	return top;
}
