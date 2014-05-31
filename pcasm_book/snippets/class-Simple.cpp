class Simple {
	public:
		Simple();
		~Simple();

		int get_data(void) const;
		void set_data(int);
	private:
		int data;
};

Simple::Simple() {
	data = 0;
}

Simple::~Simple() {
	/* empty */
}

int Simple::get_data(void) const {
	return data;
}

void Simple::set_data(int x) {
	data = x;
}
