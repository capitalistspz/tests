// Stores sizeof(int) * 8 bools in one integer
struct multi_bit {
	inline void set(int index, bool state) {
		// 1. Set the index bit to true on a seperate int.
		// 2. Invert the number to set that bit to false and create a mask
		// 3. AND mask with value to get the value with the selected bit set to false
		// 4. Shift the input bool to the selected bit's position
		// 5. OR masked value and other int bit to set the bit to value of what ever the bool is
		value = (/*2*/ ~
			(/*1*/ 1 << index)
			/*3*/ & value)
			/*5*/ |
			(/*4*/ state << index);
	}
	inline bool get(int index) {
		return (value >> index) & 1;
	}
	inline bool flip_all() {
		value = ~value;
	}
protected:
	int value = 0;
};
