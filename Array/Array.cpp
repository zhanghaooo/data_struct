class Array {
private:
	int* data;
	unsigned int size;
	unsigned int capacity;
public:
	Array() : size(0), capacity(10), data(new int[capacity]) {}
	Array(unsigned int n) : size(n), capacity(2 * size), data(new int[capacity] {0}) {}

	unsigned int getSize() {
		return this->size;
	}

	unsigned int getCapacity() {
		return this->capacity;
	}

	unsigned int isEmpty() {
		return this->size == 0;
	}

	unsigned int insert(unsigned int index, int e) {
		if (this->size == this->capacity || index > this->size) {
			//throw error
		}
		for (unsigned int i = this->size; i > index; --i)
			this->data[i] = this->data[i - 1];
		this->data[index] = e;
		++this->size;
	}

	void pushBack(int e) {
		this->insert(this->size, e);
	}

	int& operator[](int i) {
		if (i >= this->size) {
			//throw error
		}
		return this->data[i];
	}
};