#pragma once

#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <cmath>

namespace pz {
	template <typename T>
	struct dynamic_array {
		dynamic_array(size_t count = 0) : visible(count), allocated(count), arr(new T[count]) {}
		// Copy constructor, copies all elements from the other array rather referencing it
		// Takes O(n) time.
		dynamic_array(const dynamic_array<T>& dyn_arr) {
			allocated = (visible = dyn_arr.visible);
			arr = new T[allocated];
			std::copy(dyn_arr.begin(), dyn_arr.end(), arr);
		}
		// Move constructor
		dynamic_array(dynamic_array<T>&& dyn_arr) noexcept {
			visible = std::exchange(dyn_arr.visible, 0);
			allocated = std::exchange(dyn_arr.allocated, 0);
			power = std::exchange(dyn_arr.power, 0);
			arr = std::exchange(dyn_arr.arr, nullptr);
		}

		~dynamic_array() {
			delete[] arr;
		}
		// Add an element to the array.
		void push_back(const T element) {
			if (visible >= allocated) {
				//// Allocate more space to the array. 
				// O(n) time. Allocated space increases by n space.

				// Creating the new array
				allocated = std::pow(2U, power++);
				T* new_arr = new T[allocated];

				// Move all elements from old array to new array.
				std::move(arr, arr + visible, new_arr);

				// Replace old array with new array.
				delete[] arr;
				arr = new_arr;
			}
			arr[visible++] = std::move(element);
		}
		// For reading from an index.
		// Takes O(1) time.
		T operator[](const std::size_t index) const {
			if (index < visible)
				return arr[index];
			else
				throw std::out_of_range("Index out of range");
		}

		// For reading from and writing to an index.
		// Takes O(1) time.
		T& operator[](const std::size_t index) {
			if (index < visible)
				return arr[index];
			else
				throw std::out_of_range("Index out of range");
		}
		// Creates copy array from inclusive start to exclusive end.
		// Takes O(n) time.
		dynamic_array<T> sub_array(const std::size_t start, const std::size_t end, const bool reverse = false) const {
			// Only allow the function to work if the start and end positions are valid
			if (start < visible && end <= visible) {
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
		dynamic_array<T> operator+(const dynamic_array<T>& other) {
			// Create an array big enough to accomodate all the values
			const auto new_size = visible + other.visible;
			dynamic_array<T> out(new_size);

			// Copy elements into the new array
			std::copy(arr, arr + visible, out.begin());

			// Copy onto where the first array ended
			std::copy(other.begin(), other.end(), out.begin() + visible);
			return out;
		}

		// Extend an array using another array. 
		// Takes O(n) time.
		void extend(const dynamic_array<T>& other) {
			// Get total number of elements
			const auto new_size = other.visible + visible;

			// If all elements are able to fit in the existing array, copy them in.
			if (new_size <= allocated) {
				std::copy(other.begin(), other.end(), arr + visible);
			}
			// If not, create a brand new array with the capacity to fit both
			else {
				// Create new array
				T* new_arr = new T[new_size];

				// Copy values from original array to new array
				std::move(arr, arr + visible, new_arr);

				// Copy the values from the other array
				std::copy(other.begin(), other.end(), new_arr + visible);

				// Change sizes to match and replace original array with new larger array
				power = 0U;
				allocated = new_size;
				delete[] arr;
				arr = new_arr;
			}
			visible = new_size;
		}

		// Removes all elements and deallocates the memory. 
		// Takes O(1) time.
		void clear() {
			// Deletes the array
			delete[] arr;
			arr = nullptr;

			// All set to 0 to allow push back to reallocate the array.
			visible = 0;
			allocated = 0;
			power = 0;
		}

		// Returns the number of elements in the array. 
		// Takes O(1) time.
		std::size_t size() const noexcept { return visible; }

		// Returns a pointer to the first element. 
		// Takes O(1) time.
		T* begin() const { return arr; }

		// Returns a pointer to the last element.
		// Takes O(1) time.
		T* end() const { return arr + visible; }

		// Allows the array to be displayed using cout.
		// Takes O(n) time.
		friend std::ostream& operator<<(std::ostream& os, const dynamic_array<T>& dyn_arr) {
			return os << dyn_arr.to_ss().str();
		}

		// Returns whether the area is empty.
		// Takes O(1) time.
		bool empty() const noexcept { return !visible; }

		// Remove the element at the back of the array.
		// Takes O(1) time.
		void pop_back() noexcept {
			// Doesn't actually remove it, just reduces the visible size
			// Removing what is already there is pointless because as soon as something gets added, it will be replaced anyway
			if (visible)
				--visible;
		}
		// Remove the element at that index from the array.
		// Takes O(n) time.
		void remove_at(std::size_t index) noexcept {
			// Moves back all elements by one starting from the element after the one being removed
			// Does nothing if the size is 0.
			// Takes (size - index) time;
			
			if (visible && index < visible) {
				for (; index < visible; ++index)
					arr[index] = std::move(arr[index + 1]);
				--visible;
			}

		}

		// Returns a string representation of the array.
		// Takes O(n) time.
		std::stringstream to_ss() const {
			std::stringstream ss;
			ss << '[';
			if (visible) {
				const auto last = visible - 1;
				for (std::size_t i = 0; i < last; ++i)
					ss << arr[i] << ", ";
				ss << arr[last];
			}
			ss << ']';
			return ss;
		}
		// Copy all elements into a vector to be outputted.
		// Takes O(n) time. 
		std::vector<T> to_vector() {
			std::vector<T> vec(visible);
			std::copy(arr, arr + visible, vec.begin());
			return vec;
		}
		// Return the internal array.
		// Takes O(1) time.
		T* data() const noexcept { return arr; }

		// Preallocates a certain amount of memory for the array to hold [count] elements
		// Takes O(n) time.
		void reserve(const std::size_t count) {
			// Avoids allocating more space when enough is allocated
			if (count > allocated) {
				T* new_arr = new T[count];

				// Copy all elements through to the new array
				for (auto i = 0u; i < visible; ++i)
					new_arr[i] = std::move(arr[i]);

				// Change the array and size
				power = 0;
				allocated = count;
				delete[] arr;
				arr = new_arr;
			}
		}
		
	private:
		static std::size_t log2(std::size_t num) {
			std::size_t count{0};
			for (; num > 1; num /= 2)
				++count;
			return count;
		}
	protected:
		// Internal array
		T* arr = nullptr;

		// Number of elements allocated
		std::size_t allocated = 0;

		// Number of accessible elements
		std::size_t visible = 0;

		// Power to be raised by when the array is expanded
		std::size_t power = 0;
	};
}
