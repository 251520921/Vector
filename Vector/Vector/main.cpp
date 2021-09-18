#include <iostream>
#include "Vector.h"

int main() {
	Vector<int> v1;
	Vector<int> v2(3, 5, 100);
	Vector<int> v3(v2);

	v3.insert(101, 0);
	v3.insert(120, 0);
	v3.insert(121);
	v3.insert(167);
	v3.insert(188);
}