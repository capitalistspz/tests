#pragma once
#include <utility>
#include <iterator>
using std::move;
namespace pz {
	template <typename T>
	struct stack {
	protected:
		// Stack node
		struct node {
			const T value;
			node* next = nullptr;
		};
	public:
		// Iterator
		struct const_iterator {
			const_iterator(node* pointer) : ptr(pointer) {};
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using pointer = T*;
			using reference = const T&;
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
			const reference operator*() const { return ptr->value; }
			const pointer operator->() const { return &(ptr->value); }
		protected:
			node* ptr;
		};
	public:
		// Default constructor
		stack() = default;

		// Copy constructor
		stack(const stack<T>& other) {
			node* otherNodes = other.top;
			node** newNodes = &top;
			// Go down from top to bottom allocating nodes for the stack being constructed,
			// copying the value from the original stack to the new stack
			while (otherNodes) {
				*newNodes = new node{ otherNodes->value };
				otherNodes = otherNodes->next;
				newNodes = &((*newNodes)->next);
			}
		}
		
		// Move constructor
		stack(stack<T>&& other) noexcept {
			// Exchange values
			top = other.top;
			other.top = nullptr;
			count = other.count;
			other.count = 0;
		}
		void push (const T& element){
			node* next = top;

			// Set the top to the new element
			top = new node{ element };

			// Make the top node point to the former top node
			top->next = next;
			++count;
		}
		void push(T&& element) {
			node* next = top;
			top = new node{ move(element) };
			top->next = next;
			++count;
		}
		T pop() {
			// Store the value of the top node
			const T val = move(top->value);
			node* old_top = top;

			// Set the next node as the new top of the stack
			top = top->next;
			
			// Deallocate the previous top node
			delete old_top;
			--count;
			return val;
		}
		T peek() const { return top->value; }
		bool empty() const noexcept { return !top; }
		const_iterator cbegin() const { return const_iterator(top); }
		const_iterator cend() const { return const_iterator(nullptr); }
		~stack() {
			node* it = top;
			node* temp = nullptr;
			// Iterate through deallocating all the nodes;
			while (it) {
				temp = it;
				it = it->next;
				delete temp;
			}
		}
	protected:
		node* top = nullptr;
		size_t count = 0;
	};
}
