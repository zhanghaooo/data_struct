class Array {
private:
	int* data;
	unsigned int size;
	unsigned int capacity;
public:
	Array() : size(0), capacity(10), data(new int[capacity]()) {}
	Array(unsigned int n) : size(n), capacity(2 * size), data(new int[capacity]()) {}

	unsigned int getSize() {
		return this->size;
	}

	unsigned int getCapacity() {
		return this->capacity;
	}

	unsigned int isEmpty() {
		return this->size == 0;
	}

	void insert(unsigned int index, int e) {
		if (index > this->size) 
			throw out_of_range("array subscript out of range");
		if (this->size == this->capacity) {
			int *tem = new int[2*this->capacity]();
			for (int i = 0; i < this->size; ++i)
				tem[i] = this->data[i];
			delete[] this->data;
			this->data = tem;
			this->capacity *= 2;
		}
		for (unsigned int i = this->size; i > index; --i)
			this->data[i] = this->data[i - 1];
		this->data[index] = e;
		++this->size;
	}

	void pushBack(int e) {
		this->insert(this->size, e);
	}

	void erase(unsigned int n) {
		if (n >= this->size)
			throw out_of_range("array subscript out of range");
		for (int i = n; i < this->size - 1; ++i)
			this->data[i] = this->data[i + 1];
		--this->size;
		if (this->size == this->capacity / 4 && this->capacity > 1) {
			int *tem = new int[this->capacity / 2]();
			for (int i = 0; i < this->size; ++i)
				tem[i] = this->data[i];
			delete[] this->data;
			this->data = tem;
			this->capacity /= 2;
		}
	}

	void popBack() {
		this->erase(this->size - 1);
	}

	int& operator[](int i) {
		if (i >= this->size) {
			//throw error
		}
		return this->data[i];
	}
};