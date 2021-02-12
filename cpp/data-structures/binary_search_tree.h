#pragma once
#include <vector>
#include <cstdlib>
#include <functional>
template <typename T>
struct bst_node {
	bst_node(T item) {
		value = item;
	}
	// Child nodes
	bst_node<T> *left = nullptr, *right = nullptr, *parent = nullptr;

	// Value held by node
	T value;
};
template <typename T>
// Binary search tree. Only works with comparable types
struct bst {
	bst(T item) {
		root = new bst_node<T>(item);
		count = 1;
	}
	bst() { root = nullptr; }
	
	// Prevent the tree from being copied
	// Takes O(0) time because the function doesn't even exist during runtime
	bst(const bst<T>& other) = delete;
	void operator=(const bst<T>& other) = delete;

	/// Returns whether the structure is empty
	// Takes O(1) time.
	bool empty() { return !root; }

	// Append a value to the binary search tree
	void add(const T item) {
		bst_node<T> **iter = &root, *prev = nullptr;

		// Traverse until reaching an empty space, and insert the value in that empty space
		while (bst_node<T> *temp =  *iter) {
			// Parent node
			prev = *iter;

			// Go left if lesser, else go right
			iter = (item < temp->value) ? &temp->left : &temp->right;
		}
		*iter = new bst_node<T>(item);
		(*iter)->parent = prev;
		++count;
	}

	// Find value and return pointer to it
	const T* find(const T item) {
		bst_node<T> temp = *find_node_of(item);
		// Return the address of the value or return nullptr
		return (temp) ? &(temp->value): nullptr;
	}

	// Remove a single instance of a value from the binary search tree
	void remove(const T item) {
		// Find node of the value
		bst_node<T>** ptr = find_node_of(item, root);
		// If it wasn't found do nothing
		if (bst_node<T>* selected = *ptr) {
			// Traverse down to the lowest value of right hand side of value node
			bst_node<T> **low_right = find_min_from(selected->right);

			// The furthest down on the right tree now links to the left of the original
			*low_right = selected->left;

			// The node is replace by its right
			*ptr = selected->right;
			delete selected;

			--count;
		};
		
	}
	/// Number of elements in binary search tree.
	// Takes O(1) time.
	std::size_t size() const {
		return count;
	}

	// Finds all values in the tree and outputs them to a an ordered vector
	// Takes O(n) time.
	std::vector<T> to_vector() {
		std::vector<T> arr;
		std::function<void(bst_node<T>*)> collect = [&collect, &arr]
		(bst_node<T>* node) {
			if (node) {
				collect(node -> left);
				arr.push_back(node -> value);
				collect(node -> right);
			}
		}; collect(root);
		return arr;
	}
	
	// Rebalances the tree for faster traversal
	void rebalance() {
		auto size = count;
		T *ordered = new T[size];
		std::size_t num = 0;

		// Removes all elements and adds them to an array in value order
		std::function<void(bst_node<T>*)> pop = [&num, &pop, ordered]
		(bst_node<T>* node) {
			if (node) {
				pop(node->left);
				*(ordered + num++) = node->value;
				pop(node->right);
				delete node;
			}
		}; pop(root);

		// Add the values into the new tree
		std::function<bst_node<T>* (std::size_t, std::size_t)> arr_to_bst = [ordered, &arr_to_bst]
		(std::size_t left, std::size_t right) {
			const auto size = right - left;

			// Middle index for section
			const auto mid = left + size / 2;
			
			// Create a node for value
			bst_node<T>* point = new bst_node<T>(ordered[mid]);

			// No splitting of single nodes
			if (size > 1) {
				point->left = arr_to_bst(left, mid);
				point->right = arr_to_bst(mid + 1, right);
			}

			return point;
		};
		root = arr_to_bst(0, count);

	}
	~bst() {
		clear(root);
	}
// Internal methods
private:
	// Find the node that holds that value and return a pointer to it
	bst_node<T>** find_node_of(const T item, bst_node<T>* local_root) {
		bst_node<T> **iter = &local_root;
		bst_node<T>* current = *iter;
		// Run until nullptr or value
		while (current && (current->value != item)) {
			// If the item's value is less than the pivot's, go left, if it is more than or equal, go right
			iter = (item < current->value) ? &(current->left) : &(current->right);
			current = *iter;
		}
		return iter;
	}
	// Continually traverses left from that starting point, returning the last non-null node
	bst_node<T>** find_min_from(bst_node<T>* ptr) {
		while (&ptr->left)
			ptr = ptr -> left;
		return &ptr;
	}
	// Continually traverses right from that starting point, returning the last non-null node
	bst_node<T>* find_max_from(bst_node<T>* ptr) {
		while (ptr -> right)
			ptr = ptr -> right;
		return ptr;
	}

	// Remove all nodes from the tree.
	// Takes O(n) time.
	void clear(bst_node<T>* node) {
		if (node) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
		count = 0;
	}
// Private fields
private:
	std::size_t count = 0;
protected:
	bst_node<T>* root;
};
