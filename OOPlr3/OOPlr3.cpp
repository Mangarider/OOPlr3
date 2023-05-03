#include <iostream>
#include <string>
using namespace std;

class A {
public:
	int a;
	string str;
	A() {
		a = rand();
		str = "elem: " + to_string(a);
	}
	int get_a() {
		return a; 
	}
	string get_str() {
		return str;
	}
};
ostream& operator<<(ostream& os, const A& obj) {
	return os << obj.str;
}

template <typename t>

class container {
private:
	t* array = NULL;
	int size;
	int capacity;
public:

	container(): capacity(1), size(0) {
		array = new t[capacity];
	}

	container(int cpct) {
		this->capacity = cpct;
		array = new t[capacity];
		size = 0;
	}

	void growArr() {
		t* temp = new t[capacity * 2];
		capacity *= 2;
		for (int i = 0; i <= size; ++i) {
			temp[i] = array[i];
		}
		array = temp;
	}

	void reduceArr() {
		capacity = size;
		t* temp = new t[capacity];
		for (int i = 0; i <= size; ++i)
			temp[i] = array[i];
		delete[] array;
		array = temp;
	}

	int search(t obj) {
		for (int i = 0; i < size; ++i) {
			if (array[i] == obj) return i;
		}
		return -1;
	}

	void push_back(t obj) {
		push_middle(size, obj);
	}

	void push_middle(int index, t obj) {
		if (size == 0 || index <= size) {
			if (size == capacity)
				growArr();
			for (int i = size; i > index; --i)
				array[i] = array[i - 1];
			array[index] = obj;
			size++;
		}
	}

	void push_first(t obj) {
		push_middle(0, obj);
	}

	t remove_last() {
		return remove_middle(size - 1);
	}

	t remove_middle(int index) {
		if (index > 0 && index < size) {
			t a = array[index];
			for (int i = index; i < size; ++i) {
				array[i] = array[i + 1];
			}
			array[size - 1] = 0;
			size--;
			if (size == (capacity / 2))
				reduceArr();
			return a;
		}
		return NULL;
	}

	t remove_first() {
		return remove_middle(0);
	}

	t pop_last() {
		return pop_middle(size-1);
	}

	t pop_middle(int index) {
		if (index < size)
		return array[index];
		return NULL;
	}

	t pop_first() {
		return pop_middle(0);
	}

	t getAt(int index) {
		if ((index < size) && (index >= 0)) {
			return array[index];
		}
		return NULL;
	}

	t set_last() {
		return set_middle(size - 1);
	}

	t set_middle(int index, t obj) {
		if ((index < size) && (index >= 0)) {
			array[index] = obj;
		}
		return NULL;
	}

	t set_first() {
		return set_middle(0);
	}

	int get_size() {
		return size;
	}

};
int main() {
		srand(time(NULL));
		container<A*> arr;
		clock_t start = clock();
		for (int i = 0; i < 1000; ++i) {
			arr.push_back(new A());
		}
		for (int i = 0; i < 1000; ++i) {
			switch (rand() % 8)
			{
			case 0:
				arr.push_back(new A());
				break;
			case 1:
				if (arr.get_size()) {
					arr.remove_middle(rand() % arr.get_size());
				}
				break;
			case 2:
				if (arr.get_size()) {
					arr.pop_last();
				}
				break;
			case 3:
				arr.remove_last();
				break;
			case 5:
				arr.set_middle(rand() % arr.get_size(), new A());
				break;
			case 6:
				arr.search((new A()));
				break;
			case 7:
				arr.pop_middle(rand() % arr.get_size());
				break;
			}
		}
		clock_t end = clock();
		double seconds = (double)(end - start) / CLOCKS_PER_SEC;
		for (int i = 0; i < arr.get_size(); ++i) {
			std::cout << *arr.pop_middle(i) << "\n";
		}
		std::cout << "\n";
		std::cout << "Seconds to complete " << seconds << '\n';
		std::cout << "Array size " << arr.get_size() << '\n';

}