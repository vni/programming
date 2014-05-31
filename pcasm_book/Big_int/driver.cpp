#include "Big_int.h"
#include <iostream>

using namespace std;

int main() {
	try {
		            /*12345678901234567*/
		Big_int b(5, "8000000000000a00b");
		Big_int a(5, "80000000000010230");
		Big_int c = a + b;
		cout << a << " + " << b << " = " << c << endl;
		for (int i = 0; i < 2; i++) {
			c = c + a;
			cout << "c = " << c << endl;
		}
		cout << "c-1 = " << c - Big_int(5, 1) << endl;
		Big_int d(5, "12345678");
		cout << "d = " << d << endl;
		cout << "c == d " << (c == d) << endl;
		cout << "c > d " << (c > d) << endl;

	} catch (const char *str) {
		cerr << "Caught: " << str << endl;
	} catch (Big_int::Overflow) {
		cerr << "Overflow" << endl;
	} catch (Big_int::Size_mismatch) {
		cerr << "Size mismatch" << endl;
	}
	return 0;
}
