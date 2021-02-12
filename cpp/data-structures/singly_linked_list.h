#pragma once
#include <stdexcept>
#include <vector>

template <typename T>
class singly_linked_list {
	template <typename T>
	struct singly_linked_node {
		singly_linked_node(T value) : val(value) {};
		// Holds the value stored in the node
		T val;

		// Pointer to the next node
		singly_linked_node<T>* next = nullptr;
	};
public:
	using node = singly_linked_node<T>;

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

		// While there is a node at that location
		while (node* temp = *iter) {
			// Compare the value of the node with the element
			if (temp->val == element) {
				// Replace the node with the one it has its next
				*iter = temp->next;

				// Deallocate memory used for the deleted node
				delete (temp);
				--count;
				break;
			}

			// Move onto the next node
			iter = &((*iter)->next);
			
		}
	}

	// Linear search for the element and return a pointer to it. 
	// Takes O(n) time.
	T* find(T element) {
		return &(find_node(element)->val);
	}

	// Returns the value in that "position".
	// Takes O(n) time.
	T& get_at(size_t pos) const {
		return get_node_at(pos).val;
	}

	// Returns a pointer to the first node. 
	// Takes O(n) time.
	T* get_front() const noexcept { return &first->val; }

	// Returns true if the list has any elements. 
	// Takes O(1) time.
	bool empty() const noexcept { return !first; }

	// Output the list to an output stream.
	// Takes O(n) time.
	friend std::ostream& operator<< (std::ostream& os, const singly_linked_list<T>& list) {
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
	~singly_linked_list() {
		clear();
	}
protected:
	// Iterates through nodes until a certain number of nodes have been traversed and return the node. 
	// Takes O(n) time.
	node& get_node_at(size_t pos) const {
		node* iter = first;
		if (pos < count) {
			for (std::size_t i = 0; i < pos; ++i)
				iter = iter->next;
			return *iter;
		}
		else
			throw std::out_of_range("Index was out of range.\n");
	}

	// Linear search through the variables.
	// Takes O(n) time.
	node* find_node(T element) { 
		// Get address of the address of the first node
		node** iter = &first;

		// While it isn't nullptr or the sought out variable.
		while (*iter && (*iter) -> val != element) {
			// Move onto the next node
			iter = &((*iter)->next);
		}
		return *iter;
	}
private:
	size_t count = 0;
	node *first = nullptr;
};
