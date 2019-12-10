// this is a very simple implementation of smart pointer
// It do not implement an apropriate copy or move semantics
//

// this is a some-kind-of analogy to uniq_ptr


#include <iostream>
#include <cstring>

template<typename T>
class simple_pointer {
public:
    /// default-constructor is not allowed
    simple_pointer() = delete;

    simple_pointer(T *p) : m_ptr(p) {
        std::cout << "simple_pointer(T *p)\n";
    }

    /// copy-constructor is not allowed
    simple_pointer(const simple_pointer &copy) = delete;

    /// move-constructor is allowed
    simple_pointer(simple_pointer &&mv) {
        std::cout << "simple_pointer move-ctor\n";
        m_ptr = mv.m_ptr;
        mv.m_ptr = nullptr;
    }

    ~simple_pointer() {
        std::cout << "~simple_pointer\n";
        if (m_ptr) delete m_ptr;
    }

    /// copy-assign operator is disabled
    simple_pointer& operator=(const simple_pointer &rhs) = delete;

    /// move-operator is allowed
    simple_pointer& operator=(simple_pointer&& rhs) {
        if (m_ptr) {
            delete m_ptr;
        }

        m_ptr = rhs.m_ptr;
        rhs.m_ptr = nullptr;
        return *this;
    }

    T& operator*() {
        std::cout << "simple_pointer::operator*()\n";
        return *m_ptr;
    }

    T* operator->() {
        std::cout << "simple_pointer::operator->()\n";
        return m_ptr;
    }

private:
    T *m_ptr{nullptr};
};

class Animal {
public:
    Animal(const char *name) {
        int sz = std::strlen(name) + 1;
        m_name = new char[sz];
        std::cout << "Animal()\n";
        std::strncpy(m_name, name, sz);
    }

    ~Animal() {
        std::cout << "~Animal()\n";
        delete[] m_name;
    }

    void sayHi() {
        std::cout << "Hi, I'm an animal called " << m_name << "\n";
    }
private:
    char *m_name;
};

int main() {
    simple_pointer<Animal> sp(new Animal("sobachka"));

    sp->sayHi();

    auto nsp = std::move(sp);
    nsp->sayHi();
}
