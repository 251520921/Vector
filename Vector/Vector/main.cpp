#include <iostream>
#include "Vector.h"

int main() {
	Vector<int> v1;
	v1.insert(0,0);
	v1.insert(1,0);
	v1.insert(2,0);
	v1.insert(3,0);
	v1.insert(4,0);
	v1.insert(3,0);
	v1.insert(4);
	v1.insert(1);
	v1.insert(8);
	v1.insert(7);
	v1.insert(6);

	v1.bubbleSort();
	v1.uniquify();
	int r = v1.binSerachB(-5);
	std::cout << r << std::endl;
	return 0;
}