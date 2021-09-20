#include <iostream>
#include "Vector.h"

int main() {
	Vector<int> v1;
	v1.insert(0,0);
	v1.insert(1,0);
	v1.insert(2,0);
	v1.insert(3,0);
	v1.insert(4,0);
	v1.insert(5,0);
	v1.insert(6);
	v1.insert(7);

	v1.mergeSort();
	int r = v1.find(1);
	std::cout << r << std::endl;
	return 0;
}