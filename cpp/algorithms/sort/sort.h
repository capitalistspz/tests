#include <vector>
// Auxiliary functions
template <typename T>
void Swap (T &a, T &b){
  T temp = a;
  a = b;
  b = temp;
}

int ilog(unsigned int x) {
	return (x > 1) ? 1 + ilog(x / 10) : 0;
}

// Sorts

// Counting sort with buckets
void counting_sort(std::vector<unsigned int> &arr, int rad) { // Counting sort
	std::vector<int> tempArr[10]; // Creates an array of vectors, one for each digit from 0-9
	for (auto i : arr)
		tempArr[(i / rad) % 10].push_back(i);
	/*
	// Rad
	Rad is the column being evaluated
	e.g. if number 30 is entered, rad is 10, if 3 is picked, rad is 1.
	// Position : (i / rad % 10)
	Position is based on the value of the digit, if number is 162 and rad is 10, position will be 6
	*/
	arr.clear(); // Clear original array
	for (auto i : tempArr)
		for (auto j : i)
			arr.push_back(j); // Adds numbers back into original array
}
// Radix sort using counting sort with buckets
void radix_sort(std::vector<unsigned int> &arr) { // Least Siginificant Digit Radix Sort
	unsigned int max = 0;
	for (auto i : arr) {
		max = (i > max) ? i : max;
	}
	int radix = 10;
	for (int i = 1; max / i > 0; i*= radix) {
		counting_sort(arr, i);
	}
}
