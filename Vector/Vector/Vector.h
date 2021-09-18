#pragma once
#include <cassert>
#define DEFAULT_CAPACITY 4
using Rank = int;

template<class T>
class Vector {
private:
	int _capacity; int _size; T* _elem;

private:
	void copyFrom(T const* A, Rank lo, Rank hi);		//复制构造
	void expand();
	void shrink();
public:
	Vector(int s = 0, int c = DEFAULT_CAPACITY, T const& e = NULL);
	Vector(T const* A, Rank lo, Rank hi);
	Vector(T const* A, Rank n);
	Vector(Vector<T> const& V, Rank lo, Rank hi);
	Vector(Vector<T> const& V);
	~Vector();

	Rank insert(T const& e, Rank r);	//插入一个数据
	Rank insert(T const& e);
};

template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	assert(lo < hi);
	_elem = new T[_capacity = (hi - lo) << 1];
	for (_size = 0; lo < hi; _size++, lo++)
		_elem[_size] = A[lo];
}

template<class T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<class T>
void Vector<T>::shrink() {
	if (_capacity >> 1 < DEFAULT_CAPACITY) return;
	if (_capacity >> 2 < _size) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >> 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<class T>
Vector<T>::Vector(int s, int c, T const& e) {
	assert(s <= c);
	_elem = new T[_capacity = c];
	for (_size = 0; _size < s; _size++) 
		_elem[_size] = e;
}

template<class T>
Vector<T>::Vector(T const* A, Rank lo, Rank hi) {
	copyFrom(A, lo, hi);
}

template<class T>
Vector<T>::Vector(T const* A, Rank n) {
	copyFrom(A, 0, n);
}

template<class T>
Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi) {
	copyFrom(V._elem, lo, hi);
}

template<class T>
Vector<T>::Vector(Vector<T> const& V) {
	copyFrom(V._elem, 0, V._size);
}

template<class T>
Vector<T>::~Vector() {
	delete[] _elem;
}

template<class T>
Rank Vector<T>::insert(T const& e, Rank r) {
	assert(r >= 0 && r <= _size);
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;
	return r;
}

template<class T>
Rank Vector<T>::insert(T const& e) {
	insert(e, _size);
}