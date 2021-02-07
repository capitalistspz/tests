#pragma once
#include <vector>
template <typename T>
struct bst_node {
	bst_node(T item) {
		value = item;
	}
	// Child nodes
	bst_node<T> *left = nullptr, *right = nullptr, *parent;

	// Value held by node
	T value;
};
template <typename T>
struct bst {
	bst(T item) {
		root = new bst_node<T>(item);
		++count;
	}
	bst() { root = nullptr; }

	// Append a value to the binary search tree
	// Time complexity is probably O(h) where h is height of tree
	void add(const T item) {
		if (root) {
			bst_node<T> *iter = root, *prev = nullptr;
			bool less;
			// Traverse until reaching an empty space, and insert the value in that empty space
			while (iter != nullptr) {
				prev = iter; // Parent node
				less = (item < iter -> value);
				iter = (less) ? iter -> left : iter -> right;
			}
			if (less){
				prev -> left = new bst_node<T>(item);
				iter = prev->left;
			}
			else {
				prev -> right = new bst_node<T>(item);
				iter = prev->right;
			}
			iter->parent = prev;

		}
		else {
			root = new bst_node<T>(item);
		}
		++count;
	}
	// Find value and return pointer to it
	T* find(const T item) {
		auto temp = find_node_of(item);
		// Return nullptr if not found
		return (temp) ? &(temp->value): nullptr;
	}
	// Remove a single instance of a value from the binary search tree
	void remove(T item) {
		// Find node of the value
		bst_node<T>* ptr = find_node_of(item, root);
		// If it wasn't found do nothing
		if (!ptr) return;
		// Traverse down to the lowest value of right hand side of value node
		bst_node<T>* right = find_min_from(ptr->right);

		/* If the item is at the root, the right node becomes the root,
			the furthest down on the right tree links to the left of the original
		*/
		if (ptr == root) {
			root = ptr->right;
			right->left = ptr->left;
		}

		else {
			// Get parent of value node
			bst_node<T>* parent = (ptr->parent);
			// Assign the position of the original to the original's right side
			if (parent->left == ptr)
				parent->left = right;
			else
				parent->right = right;
		}
		delete ptr;
	}

	// Finds all values in the tree and outputs them to a an ordered vector
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
// Internal methods
private:
	// Find the node that holds that value and return a pointer to it
	// Time complexity is probably O(log n)
	bst_node<T>* find_node_of(const T item, bst_node<T>* root) {
		auto iter = root;
		while (iter != nullptr) {
			// If value is found, return pointer to value
			if (iter -> value == item) break;

			// If the item's value is less than the pivot's, go left, if it is more than or equal, go right
			iter = (item < iter -> value) ? iter -> left : iter -> right;

		}
		return iter;
	}
	// Continually traverses left from that starting point, returning the last non-null node
	// Time complexity is probably O(h)
	bst_node<T>* find_min_from(bst_node<T>* ptr) {
		while (ptr -> left)
			ptr = ptr -> left;
		return ptr;
	}
	// Continually traverses right from that starting point, returning the last non-null node
	// Time complexity is probably O(h)
	bst_node<T>* find_max_from(bst_node<T>* ptr) {
		while (ptr -> right)
			ptr = ptr -> right;
		return ptr;
	}
// Private fields
private:
	bst_node<T>* root;
	std::size_t count = 0;
};
