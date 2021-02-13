#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>

template <typename T>
struct dynamic_array {
	dynamic_array(const std::size_t size = 0){
		real_size = size;
		size_ = size;
		arr = new T[size];
	}

	// Copy constructor, copies all elements from the other array rather referencing it
	// Takes O(n) time.
	dynamic_array(const dynamic_array<T>& dyn_arr) {
		size_ = dyn_arr.size();
		real_size = size_;
		arr = new T[size_];
		std::copy(dyn_arr.begin(), dyn_arr.end(), arr);
	}
	// Add an element to the array.
	void append(const T element) {
		if (size_ < real_size)
			//// Simply increase accessible size and place. 
			// O(1) time.
			arr[size_++] = element;
		else {
			//// Allocate more space to the array. 
			// O(n) time. Allocated space increases by n space.

			// Creating the new array
			real_size = std::pow(2U, power++); 
			T* new_arr = new T[real_size];

			// Copy all elements from old array to new along with the new element.
			std::copy(arr, arr + size_, new_arr);
			new_arr[size_++] = element;

			// Replace old array with new array.
			delete arr;
			arr = new_arr;

		}
	}
	// For reading from an index.
	// Takes O(1) time.
	T operator[](const std::size_t index) const {
		if (index < size_)
			return arr[index];
		else
			throw std::out_of_range("Index out of range");
	}

	// For reading from and writing to an index.
	// Takes O(1) time.
	T& operator[](const std::size_t index) {
		if (index < size_)
			return arr[index];
		else
			throw std::out_of_range("Index out of range");
	}
	// Creates copy array from inclusive start to exclusive end.
	// Takes O(n) time.
	dynamic_array<T> sub_array(const std::size_t start, const std::size_t end, const bool reverse = false) const {
		// Only allow the function to work if the start and end positions are valid
		if (start < size_ && end <= size_) {
			// Create an array with the length
			dynamic_array<T> sub(end - start);

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

	// Joins two arrays together resulting in a new one. 
	// Takes O(n) time.
	dynamic_array<T> operator+(const dynamic_array<T> &other) {
		// Create an array big enough to accomodate all the values
		auto new_size = size_ + other.size();
		dynamic_array<T> out(new_size);

		// Copy elements into the new array
		std::copy(arr, arr + size_, out.begin());

		// Copy onto where the first array ended
		std::copy(other.begin(), other.end(), out.begin() + size_);

		return out;
	}

	// Extend an array using another array. 
	// Takes O(n) time.
	void extend(const dynamic_array<T>& other) {
		// Get total number of elements
		const auto new_size = other.size() + size_;

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
			power = 0;
			size_ = new_size;
			real_size = new_size;
			delete arr;
			arr = new_arr;
		}
	}

	// Removes all elements and deallocates the memory. 
	// Takes O(1) time.
	void clear() {
		// Deletes the array
		delete arr;
		arr = nullptr;

		// Both sizes set to 0 to allow append to reallocate the array.
		size_ = 0;
		real_size = 0;
		power = 0;
	}
	// Returns the number of elements in the array. 
	// Takes O(1) time.
	std::size_t size() const noexcept { return size_; }

	// Returns a pointer to the first element. 
	// Takes O(1) time.
	T* begin() const { return arr; }

	// Returns a pointer to the last element.
	// Takes O(1) time.
	T* end() const { return arr + size_; }

	// Allows the array to be displayed using cout.
	// Takes O(n) time.
	friend std::ostream& operator<<(std::ostream& os, const dynamic_array<T>& dyn_arr) {
		return os << dyn_arr.to_string();
	}

	// Returns whether the area is empty.
	// Takes O(1) time.
	bool empty() const noexcept { return !size_; }

	// Remove the element at the back of the array.
	// Takes O(1) time.
	void remove_back() noexcept {
		// Doesn't actually remove it, just reduces the visible size
		// Removing what is already there is pointless because as soon as something gets added, it will be replaced anyway
		if (size_)
			--size_;
	}
	// Remove the element at that index from the array.
	// Takes O(n) time.
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

	// Returns a string representation of the array.
	// Takes O(n) time.
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
	// Copy all elements into a vector to be outputted.
	// Takes O(n) time. 
	std::vector<T> to_vector() {
		std::vector<T> vec(size_);
		std::copy(arr, arr + size_, vec.begin());
		return vec;
	}
	// Return the internal array.
	// Takes O(1) time.
	T* data() const noexcept {
		return arr;
	}

	// Preallocates a certain amount of memory for the array
	// Takes O(n) time.
	void reserve(const std::size_t count) {
		// Avoids allocating more space when enough is allocated
		if (count > real_size) {
			T* new_arr = new T[count];

			// Copy all elements through to the new array
			std::copy(arr, arr + size_, new_arr);

			// Change the array and size
			power = 0;
			real_size = count;
			delete arr;
			arr = new_arr;
		}
	}
private:
	// Internal array
	T* arr = nullptr;

	// Total size
	std::size_t real_size = 0;

	// Externally accessible size
	std::size_t size_ = 0;

	// Power to be raised by when the array is expanded
	std::size_t power = 0;
};
