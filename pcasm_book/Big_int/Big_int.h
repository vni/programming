#ifndef Big_int_h
#define Big_int_h

#include <iostream>

using namespace std;

class Big_int {
	public:
		explicit Big_int(size_t size, unsigned initial_value = 0);
		Big_int(size_t size, const char *initial_value);
		Big_int(const Big_int &big_int_to_copy);
		~Big_int();

		size_t size() const;

		const Big_int &operator=(const Big_int &bit_int_to_copy);
		friend Big_int operator+(const Big_int &op1, const Big_int &op2);
		friend Big_int operator-(const Big_int &op1, const Big_int &op2);
		friend bool operator==(const Big_int &op1, const Big_int &op2);
		friend bool operator<(const Big_int &op1, const Big_int &op2);
		friend ostream &operator<<(ostream &os, const Big_int &op);

		/* Exceptions */
		class Overflow{};
		class Size_mismatch{};
		class Bad_initial_value{};

	private:
		size_t size_;
		unsigned *number_;
};

extern "C" {
	int add_big_ints(Big_int &res, const Big_int &op1, const Big_int &op2);
	int sub_big_ints(Big_int &res, const Big_int &op1, const Big_int &op2);
}

inline size_t Big_int::size() const {
	return size_;
}

inline Big_int::~Big_int() {
	delete [] number_;
}

inline Big_int operator+(const Big_int &op1, const Big_int &op2)
{
	Big_int result(op1.size());
	int res = add_big_ints(result, op1, op2);
	if (res == 1)
		throw Big_int::Overflow();
	if (res == 2)
		throw Big_int::Size_mismatch();
	return result;
}

inline Big_int operator-(const Big_int &op1, const Big_int &op2)
{
	Big_int result(op1.size());
	int res = sub_big_ints(result, op1, op2);
	if (res == 1)
		throw Big_int::Overflow();
	if (res == 2)
		throw Big_int::Size_mismatch();
	return result;
}

inline bool operator!=(const Big_int &op1, const Big_int &op2)
{
	return !(op1 == op2);
}

inline bool operator>(const Big_int &op1, const Big_int &op2)
{
	return op2 < op1;
}

inline bool operator<=(const Big_int &op1, const Big_int &op2)
{
	return !(op2 < op1);
}

inline bool operator>=(const Big_int &op1, const Big_int &op2)
{
	return !(op1 < op2);
}

#endif /* Big_int_h */
