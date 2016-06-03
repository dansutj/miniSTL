#include "Vector.h"
#include <iostream>
#include "Algorithm.h"
#include "Test\VectorTest.h"
using namespace std;

int main(void)
{
	miniSTL::vector<string> a;
	for (int i = 0; i < 1000000; ++i)
		a.push_back(to_string(i));
	cout << a.size() << endl;
}
