#ifndef _QUEUE_TEST_H_
#define _QUEUE_TEST_H_

#include "TestUtil.h"

#include "../Queue.h"
#include <queue>

#include <cassert>
#include <string>

namespace miniSTL {
	namespace QueueTest {
		template<class T>
		using stdQ = std::queue < T >;
		template<class T>
		using tsQ = miniSTL::queue < T >;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();

		void testAllCases();
	}
}

#endif