#ifndef NODE_H
#define NODE_H
#include <memory>
#include <utility>
#include <iostream>

using std::shared_ptr, std::make_shared;

template <typename T>
struct Node {
	Node(T _val, std::shared_ptr<Node> _next = nullptr) : val(_val), next(_next){}
	Node(T _val, Node &_next): val(_val), next(make_shared<Node>(_next)){}
	T val;
	std::shared_ptr<Node> next;
};

#endif
