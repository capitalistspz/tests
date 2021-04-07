#pragma once
#include <iostream>
#include <type_traits>
namespace pz {
	template <typename T>
	struct heap_array {
		heap_array(const int size) : count(size), arr(new T[size]) {}
		heap_array(const int size, const T& fill_value) : count(size), arr(new T[size]) {
			auto x = arr;
			const auto end = arr + count;
			while (x != end)
				*x++ = fill_value;
		}
		// Copy constructor
		heap_array(const heap_array& other): count(other.count), arr(new T[other.count]) {
			for (auto i = 0; i < count; ++i)
				arr[i] = other.arr[i];
		}

		T operator[](const std::size_t index) const {
			if (index < count)
				return arr[index];
			else
				throw std::out_of_range("Index out of range");
		}

		T& operator[](const std::size_t index) {
			if (index < count)
				return arr[index];
			else
				throw std::out_of_range("Index out of range");
		}
		T* begin() { return arr; }
		T* end() { return arr + count; }
		friend std::ostream& operator <<(std::ostream& os, const heap_array& arr) {
			os << '[';
			if (arr.count) {
				const auto last = arr.count - 1;
				for (std::size_t i = 0; i < last; ++i)
					os << arr.arr[i] << ", ";
				os << arr.arr[last];
			}
			os << ']';
			return os;
		}
		~heap_array() {
			delete[] arr;
		}
		const int count;
	protected:
		T* arr;
	};
}
