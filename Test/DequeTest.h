#ifndef _DEQUE_TEST_H_
#define _DEQUE_TEST_H_

#include "TestUtil.h"

#include "../Deque.h"
#include <deque>

#include <cassert>
#include <string>

namespace miniSTL {
	namespace DequeTest {
		template<class T>
		using stdDQ = std::deque < T >;
		template<class T>
		using tsDQ = miniSTL::deque < T >;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();
		void testCase5();
		void testCase6();

		void testAllCases();
	}
}

#endif