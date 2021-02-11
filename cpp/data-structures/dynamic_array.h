#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>

template <typename T>
struct dynamic_array {
	dynamic_array(std::size_t size = 0){
		// The array size is set to the exact size input to save space
		real_size = size;
		size_ = size;
		arr = new T[size];
	}

	// Add an element to the array.
	void append(const T element) {
		if (size_ < real_size)
			//// Simply increase accessible size and place. O(1) time.
			arr[size_++] = element;
		else {
			//// Allocate more space to the array. O(n) time. O(n^2) space.

			// Creating the new array
			real_size = real_size * real_size + 1; // n * n + 1 space
			T* new_arr = new T[real_size];

			// Copy all elements from old array to new along with the new element.
			std::copy(arr, arr + size_, new_arr);
			new_arr[size_++] = element;

			// Replace old array with new array.
			delete arr;
			arr = new_arr;

		}
	}
	// For reading from an index. O(1) time.
	T operator[](std::size_t index) const {
		if (index < size_)
			return arr[index];
		else
			throw std::out_of_range("Index out of range");
	}

	// For reading from and writing to an index. O(1) time.
	T& operator[](std::size_t index) {
		if (index < size_)
			return arr[index];
		else
			throw std::out_of_range("Index out of range");
	}
	// Creates copy array from inclusive start to exclusive end. O(n) time.
	dynamic_array<T> sub_array(std::size_t start, std::size_t end, bool reverse = false) {
		// Only allow the function to work if the start and end positions are valid
		if (start < size_ && end <= size_) {

			// Get the length of the array
			const auto length = end - start;

			// Create an array with that length
			dynamic_array<T> sub(length);

			// Copy the elements to the new array. Takes (end-start) time
			if (!reverse)
				std::copy(arr + start, arr + end, sub.begin());
			else
				std::reverse_copy(arr + start, arr + end, sub.begin());

			return sub;
		}
		else 
			throw std::out_of_range("Index out of range");
	}

	// Joins two arrays together resulting in a new one. O(n) time.
	dynamic_array<T> operator+(const dynamic_array<T> &other) {
		// Create an array big enough to accomodate all the values
		auto new_size = size_ + other.size();
		dynamic_array<T> out(new_size);

		// Copy elements into the new array
		std::copy(arr, arr + size_, out.begin());
		std::copy(other.begin(), other.end(), out.end());

		return out;
	}

	// Extend an array using another array. O(n) time.
	void extend(const dynamic_array<T>& other) {
		// Get total number of elements
		auto new_size = other.size() + size_;
		// If all elements are able to fit in the existing array, copy them in.
		if (new_size <= real_size) {
			std::copy(other.begin(), other.end(), arr + size_);
			size_ = new_size;
		}
		// If not, create a brand new array with the capacity to fit both
		else {
			// Create new array
			T* new_arr = new T[new_size];

			// Copy values from original array to new array
			std::copy(arr, arr + size_, new_arr);

			// Copy the values from the other array
			std::copy(other.begin(), other.end(), new_arr + size_);

			// Change sizes to match and replace original array with new larger array
			size_ = new_size;
			real_size = new_size;
			delete arr;
			arr = new_arr;
		}
	}

	// Removes all elements from the array. O(1) time.
	void clear() {
		// Deletes the array
		delete arr;

		// Both sizes set to 0 to allow append to reallocate the array.
		size_ = 0;
		real_size = 0;
	}
	// Returns the number of elements in the array. O(1) time.
	std::size_t size() const noexcept { return size_; }

	// Returns a pointer to the first element. O(1) time.
	T* begin() const { return arr; }

	// Returns a pointer to the last element. O(1) time.
	T* end() const { return arr + size_; }

	// Allows the array to be displayed using cout. O(n) time.
	friend std::ostream& operator<<(std::ostream& os, const dynamic_array<T>& dyn_arr) {
		return os << dyn_arr.to_string();
	}

	// Returns whether the area is empty. O(1) time.
	bool empty() const noexcept { return !size_; }

	// Remove the element at the back of the array. O(1) time.
	void remove_back() {
		// Doesn't actually remove it, just reduces the visible size
		// Removing what is already there is rather pointless as when something gets added, it will be replaced anyway
		if (size_)
			--size_;
	}
	// Remove the element at that index from the array. O(n) time.
	void remove_at(std::size_t index) {
		// Moves back all elements by one starting from the element after the one being removed
		// Does nothing if the size is 0.
		// Takes (size - index) time;
		if (size_) {
			for (; index < size_; ++index)
				arr[index] = arr[index + 1];
			--size_;
		}
		
	}

	// Returns a string representation of the array. O(n) time.
	std::string to_string() const {
		std::stringstream ss;
		ss << '[';
		if (size_){
			const auto last = size_ - 1;
			for (std::size_t i = 0; i < last; ++i)
				ss << arr[i] << ", ";
			ss << arr[last];
		}
		ss << ']';
		return ss.str();
	}

	// Return the internal array. O(1) time.
	T* data() noexcept {
		return arr;
	}
private:
	// Internal array
	T* arr = nullptr;

	// Total size
	std::size_t real_size = 0;

	// Externally accessible size
	std::size_t size_ = 0;
};
