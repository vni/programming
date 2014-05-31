#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>

#include "Big_int.h"

Big_int::Big_int(size_t size, unsigned initial_value)
	: size_(size)
{
	number_ = new unsigned[size_];
	::memset(number_, 0, sizeof(unsigned)*size_);
	number_[0] = initial_value;
}

Big_int::Big_int(size_t size, const char *initial_value)
	: size_(size)
{
	size_t len = ::strlen(initial_value);
	number_ = new unsigned[size];
	int i;

	int str_pos = len>8 ? len-8 : 0;
	for (i = 0; i < static_cast<ssize_t>(size) && str_pos >= 0; i++, str_pos -= 8) {
		int status = ::sscanf(initial_value + str_pos, "%8x", &number_[i]);
		if (1 != status) {
			delete[] number_;
			throw Bad_initial_value();
		}
	}

	if (0 <= str_pos)
		throw Overflow();

	if (-8 != str_pos) {
		char format[5];

		::sprintf(format, "%%%dx", -str_pos);
		int status = ::sscanf(initial_value, format, &number_[i]);
		if (1 != status) {
			delete [] number_;
			throw Bad_initial_value();
		}
		i++;
	}

	for (; i < static_cast<ssize_t>(size); i++)
		number_[i] = 0;
}

Big_int::Big_int(const Big_int &bigi)
	: size_(bigi.size_)
{
	number_ = new unsigned[bigi.size_];
	::memcpy(number_, bigi.number_, size_*sizeof(unsigned));
}

const Big_int &Big_int::operator=(const Big_int &bigi) {
	if (this != &bigi) {
		if (bigi.size_ != size_) {
			size_ = bigi.size_;
			delete [] number_;
			number_ = new unsigned[size_];
		}
		memcpy(number_, bigi.number_, size_*sizeof(unsigned));
	}
	return *this;
}

bool operator==(const Big_int &op1, const Big_int &op2) {
	int s1 = op1.size_;
	int s2 = op2.size_;

	if (s1 == s2)
		return ::memcmp(op1.number_, op2.number_, sizeof(unsigned)*s1) == 0;
	else
		throw Big_int::Size_mismatch();
}

bool operator<(const Big_int &op1, const Big_int &op2) {
	int s1 = op1.size_;
	int s2 = op2.size_;

	if (s1 == s2) {
		for (int i = s1-1; i >= 0; i--)
			if (op1.number_[i] < op2.number_[i])
				return true;
			else if (op1.number_[i] > op2.number_[i])
				return false;
		return false;
	}
	else
		throw Big_int::Size_mismatch();
}

ostream &operator<<(ostream &os, const Big_int &bigi) {
	ios::fmtflags oldflags = os.setf(ios::hex, ios::basefield);
	char old_fill = os.fill('0');
	bool leading_zero = true;

	for (int i = bigi.size_ - 1; i >= 0; i--) {
		if (!leading_zero)
			os.width(8);

		if (bigi.number_[i] != 0)
			leading_zero = false;
		else if (i != 0 && leading_zero)
			continue;

		os << bigi.number_[i];
	}

	os.fill(old_fill);
	os.setf(oldflags, ios::basefield);

	return os;
}
