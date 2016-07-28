#ifndef _PRIORITY_QUEUE_TEST_H_
#define _PRIORITY_QUEUE_TEST_H_

#include "TestUtil.h"

#include "../Queue.h"
#include <queue>

#include <algorithm>
#include <cassert>
#include <string>

namespace miniSTL {
	namespace PriorityQueueTest {
		template<class T>
		using stdPQ = std::priority_queue < T >;
		template<class T>
		using tsPQ = miniSTL::priority_queue < T >;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();

		void testAllCases();
	}
}

#endif