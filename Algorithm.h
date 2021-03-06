#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <string>
#include "Iterator.h"
#include "TypeTraits.h"


namespace miniSTL
{
	/*
	* fill
	* Algorithm Complexity: O(N)
	*/
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	template<>
	inline void fill(char *first, char *last, const char& value)
	{
		memset(first, value, last - first);
	}

	template<>
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, value, (last - first) * sizeof(wchar_t));
	}

	/*
	* fill_n
	* Algorithm Complexity: O(N)
	*/
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}

	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}

	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	/*
	* make_heap
	* Algorithm Complexity: O(N)
	*/
	template<class RandomAccessIterator, class Compare>
	static void up(RandomAccessIterator first, RandomAccessIterator last,
	RandomAccessIterator head, Compare comp) 
	{
		if (first != last) 
		{
			int idx = last - head - 1;
			auto pIdx = (idx - 1) / 2;

			for (auto cur = last - 1; pIdx >= 0 && cur != head; pIdx = (idx - 1) / 2) 
			{
				auto parent = head + pIdx;
				if (comp(*parent, *cur))
					miniSTL::swap(*parent, *cur);
				cur = parent;
				idx = cur - head;
			}
		}
	}

	template<class RandomAccessIterator, class Compare>
	static void down(RandomAccessIterator first, RandomAccessIterator last,
	RandomAccessIterator head, Compare comp)
	{
		if (first != last) 
		{
			auto idx = first - head;
			auto cIdx = idx * 2 + 1;
			for (auto cur = first; cIdx < (last - head) && cur != last; cIdx = idx * 2 + 1) 
			{
				auto child = head + cIdx;
				if ((child + 1) < last && *(child + 1) > *child)
					child = child + 1;

				if (comp(*cur, *child))
					miniSTL::swap(*cur, *child);
				cur = child;
				idx = cur - head;
			}
		}
	}

	template <class RandomAccessIterator>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
		make_heap(first, last,
			typename miniSTL::less<miniSTL::iterator_traits<RandomAccessIterator>::value_type>());
	}

	template <class RandomAccessIterator, class Compare>
	void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		const auto range = last - first;
		for (auto cur = first + range / 2; cur >= first; --cur) {
			down(cur, last, first, comp);
		}
	}

	/*
	* push_heap
	* Algorithm Complexity: O(N)
	*/
	template <class RandomAccessIterator>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
		push_heap(first, last,
			miniSTL::less<typename miniSTL::iterator_traits<RandomAccessIterator>::value_type>());
	}

	template <class RandomAccessIterator, class Compare>
	void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		up(first, last, first, comp);
	}

	/*
	* pop_heap
	* Algorithm Complexity: O(N)
	*/
	template <class RandomAccessIterator>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
		pop_heap(first, last,
			miniSTL::less<typename miniSTL::iterator_traits<RandomAccessIterator>::value_type>());
	}

	template <class RandomAccessIterator, class Compare>
	void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		miniSTL::swap(*first, *(last - 1));
		if (last - first > 2)
			down(first, last - 1, first, comp);
	}

	/*
	* sort_heap
	* Algorithm Complexity: O(N)
	*/
	template <class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
		return miniSTL::sort_heap(first, last,
			miniSTL::less<typename miniSTL::iterator_traits<RandomAccessIterator>::value_type>());
	}
	template <class RandomAccessIterator, class Compare>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
		for (auto cur = last; cur != first; --cur) {
			pop_heap(first, cur, comp);
		}
	}
	/*
	 * accumulate
	 * Algorithm Complexity: O(N)
	 */
	 template <class InputIterator, class T>
	 T accumulate(InputIterator first, InputIterator last, T init)
	 {
	 	for(; first != last; ++first)
	 		init = init + *first;
	 	return init;
	 }

	 template<class InputIterator, class T, class BinaryOperation>
	 T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation op)
	 {
	 	for(; first != last; ++first)
	 		init = op(init, *first);
	 	return init;
	 }


	/*
	 * for_each
	 * Algorithm Complexity: O(N)
	 */
	 template <class InputIterator, class Function>
	 Function for_each(InputIterator first, InputIterator last, Function f)
	 {
	  	for(; first != last; ++first)
	  		f(*first);
	  	return f;
	 }

	/*
	 * count
	 * Algorithm Complexity: O(N)
	 */
	template <class InputIterator, class T>
	typename iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const T& val){
			typename iterator_traits<InputIterator>::difference_type n = 0;
			for(; first != last; ++first)
			{
				if(*first == val)
					++n;
			}
			return n;
	}

	/*
	 * count_if
	 * Algorithm Complexity: O(N)
	 */
	template <class InputIterator, class UnaryPredicate>
	typename iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, UnaryPredicate pred){
			typename iterator_traits<InputIterator>::difference_type n = 0;
			for(; first != last; ++first)
			{
				if(pred(*first))
					++n;
			}
			return n;
	}


	/*
	 * find
	 * Algorithm Complexity: O(N)
	 */
	template <class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& val){
		for(; first != last; ++first){
			if(*first == val)
				break;
		}
		return first;
	}

	/*
	 * find_if
	 * Algorithm Complexity: O(N)
	 */
	template <class InputIterator, class UnaryPredicate>
	InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred){
		for(; first != last; ++first){
			if(pred(*first))
				break;
		}
		return first;
	}


	/*
	 * find_if_not
	 * Algorithm Complexity: O(N)
	 */
	template <class InputIterator, class UnaryPredicate>
	InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred){
		for(; first != last; ++first){
			if(!pred(*first))
				break;
		}
		return first;
	}

	/*
	 * distance
	 * Algorithm Complexity: O(N)
	 */
	 template <class InputIterator>
	 typename iterator_traits<InputIterator>::difference_type
	  	_distance(InputIterator first, InputIterator last, input_iterator_tag){
	  		typename iterator_traits<InputIterator>::difference_type dist = 0;
	  		while(first++ != last){
	  			++dist;
	  		}
	  		return dist;
	 }

	 template <class RandomIterator>
	 typename iterator_traits<RandomIterator>::difference_type
	 	_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag){
	 		auto dist = last - first;
	 		return dist;
	 }

	 template <class Iterator>
	 typename iterator_traits<Iterator>::difference_type
	 	distance(Iterator first, Iterator last){
	 		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	 		return _distance(first, last, iterator_category());
	 }

	/*
	 * advance
	 * Algorithm Complexity: O(N)
	 */	
	template <class InputIterator, class Distance>
	void _advance(InputIterator& it, Distance n, input_iterator_tag){
		assert(n >= 0);
		while(n--){
			++it;
		}
	}

	template <class BidirectionIterator, class Distance>
	void _advance(BidirectionIterator& it, Distance n, bidirectional_iterator_tag){
		if(n < 0)
		{
			while(n++){
				--it;
			}
		}
		else
		{
			while(n--){
				++it;
			}
		}
	}

	template <class RandomIterator, class Distance>
	void _advance(RandomIterator& it, Distance n, random_access_iterator_tag){
		if(n < 0) {
			it -= (-n);
		}
		else{
			it += n;
		}
	}

	template <class InputIterator, class Distance>
	void advance(InputIterator& it, Distance n){
		typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
		return _advance(it, n, iterator_category());
	}


	/*
	 * sort
	 * Algorithm Complexity: O(NlogN)
	 */	
	template <class RandomIterator, class BinaryPredicate>
	static void mid3(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
		auto mid = first + (last - first) / 2;

		if (pred(*mid, *first)) {
			swap(*mid, *first);
		}

		if (pred(*(last - 1), *mid)) {
			swap(*(last - 1), *mid);
		}

		if (pred(*(last - 1), *first)) {
			swap(*(last - 1), *first);
		}

		swap(*mid, *first);
	}

	template <class RandomIterator, class BinaryPredicate>
	static void bubble_sort(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
		auto len = last - first;
		for (int i = 0; i != len - 1; ++i)
		{
			bool swaped = false;
			for (auto p = first; p != (last - i - 1); ++p)
			{
				if (pred(*(p + 1), *p)) {
					swap(*(p + 1), *p);
					swaped = true;
				}
			}
			if (!swaped)
				break;
		}
	}

	template <class RandomIterator>
	void sort(RandomIterator first, RandomIterator last){
		return sort(first, last, std::less<typename iterator_traits<RandomIterator>::value_type>());
	}

	template <class RandomIterator, class BinaryPredicate>
	void sort(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
		if (first >= last || first + 1 == last)
			return;

		if (last - first <= 20)//区间长度小于等于20的采用冒泡排序更快
		{
			bubble_sort(first, last, pred);
			return;
		}

		mid3(first, last, pred);
		auto p1 = first;
		auto p2 = last;

		while (p1 < p2)
		{
			while ((p1 < last - 1) && pred(*++p1, *first));
			while ((first < p2) && !pred(*--p2, *first));

			if (p1 >= p2) break;
			swap(*p1, *p2);
		}

		swap(*p2, *first);
		sort(first, p2, pred);
		sort(p2 + 1, last, pred);
	}

	/*
	 * copy
	 * Algorithm Complexity: O(N)
	 */	
	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _true_type) {
		auto dist = distance(first, last);
		memcpy(result, first, sizeof(*first) * dist);
		advance(result, dist);
		return result;
	}

	template<class InputIterator, class OutputIterator>
	OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type) {
		while (first != last) {
			*result = *first;
			++result;
			++first;
		}
		return result;
	}

	template<class InputIterator, class OutputIterator, class T>
	OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, T*) {
		typedef typename miniSTL::_type_traits<T>::is_POD_type is_pod;
		return __copy(first, last, result, is_pod());
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
		return _copy(first, last, result, value_type(first));
	}

	template<>
	inline char *copy(char *first, char *last, char *result) {
		auto dist = last - first;
		memcpy(result, first, sizeof(*first) * dist);
		return result + dist;
	}

	template<>
	inline wchar_t *copy(wchar_t *first, wchar_t *last, wchar_t *result) {
		auto dist = last - first;
		memcpy(result, first, sizeof(*first) * dist);
		return result + dist;
	}
}


#endif