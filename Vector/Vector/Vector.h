#pragma once
#include <cassert>
#define DEFAULT_CAPACITY 4
using Rank = int;

template<class T>
class Vector {
private:
	int _capacity; int _size; T* _elem;

private:
	void copyFrom(T const* A, Rank lo, Rank hi);		//���ƹ���
public:
	Vector(int s = 0, int c = 0, T const& e = NULL);
	Vector(T const* A, Rank lo, Rank hi);
	Vector(T const* A, Rank n);
	Vector(Vector<T> const& V, Rank lo, Rank hi);
	Vector(Vector<T> const& V);
	~Vector();
};

template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	assert(lo < hi);
	_elem = new T[_capacity = (hi - lo) << 1];
	for (_size = 0; lo < hi; _size++, lo++)
		_elem[_size] = A[lo];
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
	copyFrom(V._elem, 0, _size);
}

template<class T>
Vector<T>::~Vector() {
	delete[] _elem;
}