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
	Rank bubble(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);

public:
	Vector(int s = 0, int c = DEFAULT_CAPACITY, T const& e = NULL);
	Vector(T const* A, Rank lo, Rank hi);
	Vector(T const* A, Rank n);
	Vector(Vector<T> const& V, Rank lo, Rank hi);
	Vector(Vector<T> const& V);
	~Vector();

	Vector<T>& operator=(Vector<T> const& rhs);
	T& operator[](Rank r);
	operator T* () const;

	Rank insert(T const& e, Rank r);	//插入一个数据
	Rank insert(T const& e);
	int remove(Rank lo, Rank hi);
	T remove(Rank r);

	//无序向量
	Rank find(T const& e, Rank lo, Rank hi) const;
	Rank find(T const& e) const;
	int duplicate();
	//排序
	void bubbleSort(Rank lo, Rank hi);
	void bubbleSort();
	void mergeSort(Rank lo, Rank hi);
	void mergeSort();
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
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<class T>
Rank Vector<T>::bubble(Rank lo, Rank hi) {
	Rank last = lo;
	while (++lo < hi)
		if (_elem[lo - 1] > _elem[lo]) {
			last = lo;
			std::swap(_elem[lo - 1], _elem[lo]);//main函数里包含了iosteram
		}
	return last;
}

template<class T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	Rank i = 0; T* A = _elem + lo;
	Rank j = 0; int lb = mi - lo; T* B = new T[lb];
	for (Rank i = 0; i < lb; i++) B[i] = A[i];
	Rank k = 0; int lc = hi - mi; T* C = _elem + mi;
	while ((j < lb) && (k < lc))
		A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
	while (j < lb)
		A[i++] = B[j++];
	delete[] B;
	
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
Vector<T>& Vector<T>::operator=(Vector<T> const& rhs) {
	if (_elem) delete[] _elem;
	copyFrom(rhs._elem, 0, rhs._size);
	return *this;
}

template<class T>
T& Vector<T>::operator[](Rank r) {
	return _elem[r];
}

template<class T>
Vector<T>::operator T* () const {
	return _elem;
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
	return insert(e, _size);
}

template<class T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0;
	if (hi > _size) hi = _size;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template<class T>
T Vector<T>::remove(Rank r) {
	assert(r < _size);
	T t = _elem[r];
	remove(r, r + 1);
	return t;
}

template<class T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	assert(lo < hi);
	if (hi > _size) hi = _size;
	while (lo < hi-- && e != _elem[hi]);
	return hi;
}

template<class T>
Rank Vector<T>::find(T const& e) const {
	return find(e, 0, _size);
}

template<class T>
int Vector<T>::duplicate() {
	int oldSize = _size;
	int i = 1;
	while(i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	return oldSize - _size;
}

template<class T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (lo < (hi = bubble(lo, hi)));
}

template<class T>
void Vector<T>::bubbleSort() {
	bubbleSort(0, _size);
}

template<class T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	assert(lo >= 0 && lo < hi);
	if (hi > _size) hi = _size;
	if (hi - lo < 2) return;
	int mi = (lo + hi) / 2;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<class T>
void Vector<T>::mergeSort() {
	mergeSort(0, _size);
}