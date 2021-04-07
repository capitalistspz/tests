#pragma once
#include <stdexcept>
#include <vector>
template <typename T>
class slist {
protected:
	struct node {
		node(T value) : val(value) {};
		// Holds the value stored in the node
		T val;

		// Pointer to the next node
		node* next = nullptr;
	};
public:
	struct iterator {
		iterator(node* pointer) : ptr(pointer) {};
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		// Do not use this
		using difference_type = std::ptrdiff_t;

		iterator& operator++ () {
			ptr = ptr->next;
			return *this;
		}
		iterator operator++ (int) {
			iterator temp = *this;
			ptr = ptr->next;
			return temp;
		}
		bool operator == (const iterator& other) { return ptr == other.ptr; }
		bool operator != (const iterator& other) { return ptr != other.ptr; }
		reference operator*() { return ptr->val; }
		pointer operator->() { return &(ptr->val); }
	protected:
		node* ptr;
	};
	struct const_iterator {
		const_iterator(node* pointer) : ptr(pointer) {};
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		// Do not use this
		using difference_type = std::ptrdiff_t;

		const_iterator& operator++ () {
			ptr = ptr->next;
			return *this;
		}
		const_iterator operator++ (int) {
			const_iterator temp = *this;
			ptr = ptr->next;
			return temp;
		}
		bool operator == (const const_iterator& other) { return ptr == other.ptr; }
		bool operator != (const const_iterator& other) { return ptr != other.ptr; }
		const reference operator*() const { return ptr->val; }
		const pointer operator->() const { return &(ptr->val); }
	protected:
		node* ptr;
	};
public:
	// Adds an element onto the end of the list. 
	// Takes O(n) time.
	void append(T element) noexcept {
		//// Get the first node and iterate through until there is an empty space

		// Double pointer is used to shorten code and allow first to be replaced without making more comparisons
		node** iter = &first;

		// Iterate until there is no node
		while (*iter)
			iter = &((*iter)->next);

		// Assign a new node with the element's value
		*iter = new node(element);
		++count;
	}

	// Finds and deletes an element.
	// Takes O(n) time.
	void remove(T element) {
		// Get address of the address of the first node
		node** iter = &first;
		node* prev = nullptr;
		// While there are still nodes to traverse and the element hasn't been found
		while (*iter && (*iter)->val != element) {
			prev = *iter;
			// Move onto the next node
			iter = &((*iter)->next);
		}
		auto current = *iter;
		// Replace the node with the one it has its next
		*iter = (*iter)->next;

		// Deallocate memory used for the deleted node 
		delete current;
		--count;
		
	}

	// Linear search for the element and return a pointer to it. 
	// Takes O(n) time.
	T* find(T element) {
		return &((*find_node(element))->val);
	}

	// Returns an iterator at the start
	iterator begin() { return iterator(first); }

	// Returns an iterator with nullptr
	iterator end() { return iterator(nullptr); }

	// Returns a const iterator at the start
	const_iterator cbegin() { return const_iterator(first); }

	// Returns a const iterator with nullptr
	const_iterator cend() { return const_iterator(nullptr); }

	// Returns true if the list has any elements. 
	// Takes O(1) time.
	bool empty() const noexcept { return !first; }

	// Output the list to an output stream.
	// Takes O(n) time.
	friend std::ostream& operator<< (std::ostream& os, const slist<T>& list) {
		os << '[';
		node *iter = list.first;
		if (!list.empty()) {
			for (size_t i = 0; i < (list.count - 1); ++i) {
				os << iter->val << ", ";
				iter = iter->next;
			}
			os << iter->val;
		}
		os << ']';
		return os;
	}
	// Return the number of elements in the list.
	// Takes O(n) time.
	size_t size() const noexcept { return count;}

	// Returns a vector storing all the values from the list
	// Takes O(n) time.
	std::vector<T> to_vector() {
		std::vector<T> vec;
		vec.reserve(count);
		node *iter = first;
		while (iter) {
			vec.push_back(iter->val);
			iter = iter->next;
		}
		return vec;
	}

	// Remove all elements from the list
	// Takes O(n) time.
	void clear() {
		node *iter = first;
		node *prev = nullptr;
		while (iter) {
			prev = iter;
			iter = iter->next;
			delete prev;
		}
		first = nullptr;
		count = 0;
	}
	~slist() {
		clear();
	}
protected:
	// Linear search through the variables.
	// Takes O(n) time.
	node** find_node(T element) { 
		// Get address of the address of the first node
		node** iter = &first;

		// While it isn't nullptr or the sought out variable.
		while (*iter && (*iter) -> val != element) {
			// Move onto the next node
			iter = &((*iter)->next);
		}
		return iter;
	}
protected:
	size_t count = 0;
	node *first = nullptr;
};
