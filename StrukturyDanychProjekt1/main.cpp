#include <iostream>
#include <fstream>
#include <chrono>
#include <typeinfo>

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
		if (index >= size) /*throw out_of_range("Index out of range");*/ return T();
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
		/*throw invalid_argument("Value not found");*/ return T();
	}
private:
	SNode<T>* head;
	SNode<T>* tail;
	unsigned int size;
};

template<typename T>
class DArrElement {
public:
	DArrElement() : value(T()) {}
	DArrElement(T val) : value(val) {}
	T getValue() const {
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
	void insertOnEmpty(T val) {
		arr[size++] = DArrElement<T>(val);
	}
	void insertOnFront(T val) {
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
		//delete[] arr;
		size = 0;
	}
	T findByIndex(unsigned int index) {
		if (index >= size) /*throw out_of_range("Index out of range");*/ return T();
		return arr[index].getValue();
	}
	T findByValue(T val) {
		for (unsigned int i = 0; i < size; i++) {
			if (arr[i].getValue() == val) return arr[i].getValue();
		}
		/*throw invalid_argument("Value not found");*/ return T();
	}
private:
	DArrElement<T>* arr;
	unsigned int size;
	unsigned int capacity;
};


int main() {
	unsigned int iteracje = 1000;
	ofstream file;

	// SLinkedList

	file.open("SLinkedlistFrontInsertTime.csv");
	SLinkedList<int> list;

	for (int i = -5; i < 0; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Dodawanie elementów na pocz¹tek listy
		auto start = chrono::high_resolution_clock::now();
		list.addFront(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	list.clearList(); // Czyszczenie listy przed kolejnym pomiarem
	file.open("SLinkedlistBackInsertTime.csv");

	for (int i = -5; i < 0; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Dodawanie elementów na koniec listy
		auto start = chrono::high_resolution_clock::now();
		list.addBack(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	list.clearList(); // Czyszczenie listy przed kolejnym pomiarem
	file.open("SLinkedlistAtInsertTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Dodawanie elementów na zadany indeks listy
		auto start = chrono::high_resolution_clock::now();
		list.addAt(i, -i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	list.clearList(); // Czyszczenie listy przed kolejnym pomiarem
	file.open("SLinkedlistRemoveFrontTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Usuwanie elementów z pocz¹tku listy
		auto start = chrono::high_resolution_clock::now();
		list.removeFront();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	list.clearList(); // Czyszczenie listy przed kolejnym pomiarem
	file.open("SLinkedlistRemoveBackTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Usuwanie elementów z koñca listy
		auto start = chrono::high_resolution_clock::now();
		list.removeBack();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	list.clearList(); // Czyszczenie listy przed kolejnym pomiarem
	file.open("SLinkedlistRemoveAtTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = iteracje; i > 0; i--) { // Usuwanie elementów z zadanym indeksem listy
		auto start = chrono::high_resolution_clock::now();
		list.removeAt(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	list.clearList(); // Czyszczenie listy przed kolejnym pomiarem
	file.open("SLinkedlistFindByIndexTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Szukanie elementów po indeksie listy
		auto start = chrono::high_resolution_clock::now();
		list.findByIndex(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	list.clearList(); // Czyszczenie listy przed kolejnym pomiarem
	file.open("SLinkedlistFindByValueTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie listy pocz¹tkowymi wartoœciami
		list.addFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Szukanie elementów po wartoœci w liœcie
		auto start = chrono::high_resolution_clock::now();
		list.findByValue(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	

	// DArray

	file.open("DArrayFrontInsertTime.csv");
	DArray<int> arr;

	for (int i = -5; i < 0; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Dodawanie elementów na pocz¹tek tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.insertOnFront(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	arr.clearArray(); // Czyszczenie tablicy przed kolejnym pomiarem
	file.open("DArrayBackInsertTime.csv");

	for (int i = -5; i < 0; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Dodawanie elementów na koniec tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.insertOnBack(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	arr.clearArray(); // Czyszczenie tablicy przed kolejnym pomiarem
	file.open("DArrayAtInsertTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Dodawanie elementów na zadany indeks tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.insertAt(i, -i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	arr.clearArray(); // Czyszczenie tablicy przed kolejnym pomiarem
	file.open("DArrayRemoveFrontTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Usuwanie elementów z pocz¹tku tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.removeFront();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	arr.clearArray(); // Czyszczenie tablicy przed kolejnym pomiarem
	file.open("DArrayRemoveBackTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Usuwanie elementów z koñca tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.removeBack();
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	arr.clearArray(); // Czyszczenie tablicy przed kolejnym pomiarem
	file.open("DArrayRemoveAtTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = iteracje; i > 0; i--) { // Usuwanie elementów z zadanym indeksem tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.removeAt(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	arr.clearArray(); // Czyszczenie tablicy przed kolejnym pomiarem
	file.open("DArrayFindByIndexTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Szukanie elementów po indeksie w tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.findByIndex(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	arr.clearArray(); // Czyszczenie tablicy przed kolejnym pomiarem
	file.open("DArrayFindByValueTime.csv");

	for (int i = -5; i < iteracje; i++) { // Wype³nienie tablicy pocz¹tkowymi wartoœciami
		arr.insertOnFront(i);
	}

	for (int i = 0; i < iteracje; i++) { // Szukanie elementów po wartoœci w tablicy
		auto start = chrono::high_resolution_clock::now();
		arr.findByValue(i);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		file << duration.count() << endl;
	}

	file.close();
	
	return 0;
}