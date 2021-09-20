#include <iostream>
#include "Vector.h"

int main() {
	Vector<int> v1;
	v1.insert(0);
	v1.insert(1);
	v1.insert(2);
	v1.insert(3);
	v1.insert(4);
	v1.insert(5);


	int r = v1.find(1);
	std::cout << r << std::endl;
	return 0;
}