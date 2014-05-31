#include <iostream>

using namespace std;

class A {
	public:
		virtual void m1() { cout << "A::m1()" << endl; }
		virtual void m2() { cout << "A::m2()" << endl; }
		int ad;
};

class B: public A {
	public:
		virtual void m1() { cout << "B::m1()" << endl; }
		int bd;
};

void print_vtable(A *pa) {
	unsigned *p = reinterpret_cast<unsigned *>(pa);
	void **vt = reinterpret_cast<void **>(p[0]);
	cout << hex << "vtable address " << vt << endl;
	for (int i = 0; i < 2; i++)
		cout << "dword " << i << ": " << vt[i] << endl;

	void (*m1func_pointer)(A *);
	m1func_pointer = reinterpret_cast<void (*)(A *)>(vt[0]);
	m1func_pointer(pa);

	void (*m2func_pointer)(A *);
	m2func_pointer = reinterpret_cast<void (*)(A *)>(vt[1]);
	m2func_pointer(pa);
}

int main() {
	A a;
	cout << "a: " << endl;
	print_vtable(&a);

	B b1, b2;
	cout << "b1: " << endl;
	print_vtable(&b1);
	cout << "b2: " << endl;
	print_vtable(&b2);

	return 0;
}
