extern "C" int printf(const char *, ...);

struct Bar {
    Bar() {
        printf("Default constructor. Bar::Bar()\n");
    }

    Bar(Bar const& other) {
        printf("Copy constructor. Bar::Bar(Bar const& other)\n");
    }

    Bar(int v) : val(v) {
        printf("int constructor. Bar::Bar(int v: %d)\n", v);
    }

    Bar& operator=(Bar const& other) {
        printf("Assign operator. Bar& Bar::operator=(Bar const& other)\n");
    }

    Bar(Bar&& other) {
        printf("Move constructor. Bar::Bar(Bar&& other)\n");
    }

    Bar& operator=(Bar&& other) {
        printf("Move operator. Bar& Bar::operator=(Bar&& other)\n");
    }

    ~Bar() {
        printf("Destructor. Bar::~Bar()\n");
    }

    private:
    int val = 0;
};

int main() {
    Bar bar = static_cast<Bar&&>(Bar(42));
}
