#include <iostream>
#include "List.h"
#include "Test\DequeTest.h"
#include "Test\Unordered_setTest.h"
#include "Test\VectorTest.h"
#include "Test\ListTest.h"
#include "Test\QueueTest.h"
#include "Test\PriorityQueueTest.h"

int main(void)
{
	miniSTL::DequeTest::testAllCases();
	miniSTL::Unordered_setTest::testAllCases();
	miniSTL::VectorTest::testAllCases();
	miniSTL::ListTest::testAllCases();
	miniSTL::QueueTest::testAllCases();
	miniSTL::PriorityQueueTest::testAllCases();
}
