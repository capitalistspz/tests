#pragma once
#include <utility>
#include <vector>
namespace pz {
	template <typename T>
	struct vector_stack {
		void push(const T& element){ vec.push_back(element); }
		void push(T&& element) { vec.push_back(std::forward<T>(element)); }
		T pop() {
			auto temp = vec[vec.size() - 1];
			vec.pop_back();
			return temp;
		}

		T peek() const {
			return vec[vec.size() - 1];
		}
		friend std::ostream& operator<< (std::ostream& os, const vector_stack& stack) {
			os << '[';
			const auto size = stack.vec.size();
			if (size) {
				for (std::size_t i = 1; i < size; ++i)
					os << stack.vec[size - i] << ", ";
				os << stack.vec[0];
			}
			os << ']';
			return os;
		}
		auto size() const { return vec.size(); }
	protected:
		std::vector<T> vec;
	};
}
