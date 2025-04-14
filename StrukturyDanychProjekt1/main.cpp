#include <iostream>

//#include <chrono>
// 
//auto start = chrono::high_resolution_clock::now();
//someAlgorithm(n);
//auto stop = chrono::high_resolution_clock::now();
//auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

//cout << "Time taken by function: "
//	<< duration.count() << " microseconds" << endl;

using namespace std;

template<typename T>
class SNode {
public:
	SNode(T val) : value(val), next(nullptr) {}
private:
	T value;
	SNode* next;
	template<typename> friend class SLinkedList;
};

template<typename T>
class SLinkedList {
public:
	SLinkedList() : head(nullptr), tail(nullptr), size(0) {}
	~SLinkedList() {
		while (head) {
			SNode<T>* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
	}
	void addOnEmpty(T val) {
		SNode<T>* newNode = new SNode<T>(val);
		head = newNode;
		tail = newNode;
		size++;
	}
	void addFront(T val) {
		if (head == nullptr) addOnEmpty(val);
		else {
			SNode<T>* newNode = new SNode<T>(val);
			newNode->next = head;
			head = newNode;
			size++;
		}
	}
	void addBack(T val) {
		if (tail == nullptr) addOnEmpty(val);
		else {
			SNode<T>* newNode = new SNode<T>(val);
			tail->next = newNode;
			tail = newNode;
			size++;
		}
	}
	void addAt(T val, unsigned int index) {
		if (index > size) return;
		if (index == 0) addFront(val);
		else if (index == size) addBack(val);
		else {
			SNode<T>* newNode = new SNode<T>(val);
			SNode<T>* current = head;
			for (unsigned int i = 1; i < index; i++) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
			size++;
		}
	}
	void removeFront() {
		if (head == nullptr) return;
		SNode<T>* temp = head;
		head = head->next;
		delete temp;
		size--;
		if (head == nullptr) tail = nullptr;
	}
	void removeBack() {
		if (tail == nullptr) return;
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
			size--;
		}
		else {
			SNode<T>* current = head;
			while (current->next != tail) {
				current = current->next;
			}
			delete tail;
			tail = current;
			tail->next = nullptr;
			size--;
		}
	}
	void removeAt(unsigned int index) {
		if (index >= size) return;
		if (index == 0) removeFront();
		else if (index == size - 1) removeBack();
		else {
			SNode<T>* current = head;
			for (unsigned int i = 1; i < index; i++) {
				current = current->next;
			}
			SNode<T>* temp = current->next;
			current->next = temp->next;
			delete temp;
			size--;
		}
	}
	void clearList() {
		while (head) {
			SNode<T>* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		size = 0;
	}
	T findByIndex(unsigned int index) {
		if (index >= size) throw out_of_range("Index out of range");
		SNode<T>* current = head;
		for (unsigned int i = 0; i < index; i++) {
			current = current->next;
		}
		return current->value;
	}
	T findByValue(T val) {
		SNode<T>* current = head;
		while (current) {
			if (current->value == val) return current->value;
			current = current->next;
		}
		throw invalid_argument("Value not found");
	}
private:
	SNode<T>* head;
	SNode<T>* tail;
	unsigned int size;
};

template<typename T>
class DArrElement {
public:
	DArrElement(T val) : value(val) {}
	getValue() const {
		return value;
	}
private:
	T value;
};

template<typename T>
class DArray {
public:
	DArray(unsigned int cap = 10) : size(0), capacity(cap) {
		arr = new DArrElement<T>[capacity];
	}
	~DArray() {
		delete[] arr;
	}
	void resizeAndCopy() {
		capacity *= 2;
		DArrElement<T>* newArr = new DArrElement<T>[capacity];
		for (unsigned int i = 0; i < size; i++) {
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
	};
	insertOnEmpty(T val) {
		arr[size++] = DArrElement<T>(val);
	}
	insertOnFront(T val) {
		if (size == 0) insertOnEmpty(val);
		else if (size == capacity) {
			resizeAndCopy();
			for (unsigned int i = size; i > 0; i--) {
				arr[i] = arr[i - 1];
			}
			arr[0] = DArrElement<T>(val);
			size++;
		}
		else {
			for (unsigned int i = size; i > 0; i--) {
				arr[i] = arr[i - 1];
			}
			arr[0] = DArrElement<T>(val);
			size++;
	}
	}
	void insertOnBack(T val) {
		if (size == 0) insertOnEmpty(val);
		else if (size == capacity) resizeAndCopy();
		arr[size++] = DArrElement<T>(val);
	}
	void insertAt(T val, unsigned int index) {
		if (index > size) return;
		else if (index == 0) insertOnFront(val);
		else if (index == size) insertOnBack(val);
		else {
			if (size == capacity) resizeAndCopy();
			for (unsigned int i = size; i > index; i--) {
				arr[i] = arr[i - 1];
			}
			arr[index] = DArrElement<T>(val);
			size++;
		}
	}
	void removeFront() {
		if (size == 0) return;
		for (unsigned int i = 0; i < size - 1; i++) {
			arr[i] = arr[i + 1];
		}
		size--;
	}
	void removeBack() {
		if (size == 0) return;
		delete arr[size - 1];
		size--;
	}
	void removeAt(unsigned int index) {
		if (index >= size) return;
		else if (index == 0) removeFront();
		else if (index == size - 1) removeBack();
		else {
			for (unsigned int i = index; i < size - 1; i++) {
				arr[i] = arr[i + 1];
			}
			size--;
		}
	}
	void clearArray() {
		delete[] arr;
		arr = new DArrElement<T>[capacity];
		size = 0;
	}
	T findByIndex(unsigned int index) {
		if (index >= size) throw out_of_range("Index out of range");
		return arr[index].getValue();
	}
	T findByValue(T val) {
		for (unsigned int i = 0; i < size; i++) {
			if (arr[i].getValue() == val) return arr[i].getValue();
		}
		throw invalid_argument("Value not found");
	}
private:
	DArrElement<T>* arr;
	unsigned int size;
	unsigned int capacity;
};


int main() {
	cout << "Hello World!" << endl;
	return 0;
}