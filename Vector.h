#ifndef _VECTOR_H_
#define _VECTOR_H_


#include "Algorithm.h"
#include <type_traits>
#include <cassert>
#include "Iterator.h"
#include "Allocator.h"
#include "Utility.h"
#include "UninitializedFunctions.h"

namespace miniSTL
{
	template <class T, class Alloc = allocator<T>>
	class vector
	{
	private:
		T* start_;
		T* finish_;
		T* endOfStorage_;

		typedef Alloc dataAllocator;

	public:
		typedef T 					value_type;
		typedef T*					iterator;
		typedef const T*			const_iterator;
		typedef iterator   			pointer;
		typedef T&					reference;
		typedef const T&			const_reference;
		typedef size_t				size_type;
		typedef ptrdiff_t 			difference_type;

		//构造 复制 析构相关函数
		vector() : start_(0), finish_(0), endOfStorage_(0) {}
		vector(std::initializer_list<T> it);

		explicit vector(const size_type n);
		vector(const size_type n, const value_type& value);

		template<class InputIterator>
		vector(InputIterator first, InputIterator last);

		vector(const vector& v);
		vector(vector&& v);

		vector& operator=(const vector& v);
		vector& operator=(std::initializer_list<T> it);
		vector& operator=(vector&& v);
		~vector();

		//比较操作相关
		bool operator==(const vector& v) const;
		bool operator!=(const vector& v) const;

		//迭代器相关
		iterator begin() { return start_; }
		const_iterator begin() const { return start_; }
		const_iterator cbegin() const { return start_; }

		iterator end() { return finish_; }
		const_iterator end() const { return finish_; }
		const_iterator cend() const { return finish_; }

		//与容量相关
		difference_type size() const { return finish_ - start_; }
		difference_type capacity() const { return endOfStorage_ - start_; }
		bool empty() const { return start_ == finish_; }
		void resize(size_type n, value_type val = value_type());
		void reserve(size_type n);
		void shrink_to_fit();

		//访问元素相关
		reference operator[](const difference_type i) { return *(begin() + i); }
		const_reference operator[](const difference_type i) const { return *(cbegin + i); }
		reference front() { return *(begin()); }
		reference back() { return *(end() - 1); }
		pointer data() { return start_; }

		//修改容器相关的操作
		//清空容器, 销毁容器中的所有对象并使容器的size为0, 但不返回容器已有的空间
		void clear();
		void swap(vector& v);
		void push_back(const value_type& value);
		void pop_back();

		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, const size_type n, const value_type& val);

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		void insert(iterator position, std::initializer_list<T> it);
		
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
	
		//容器的空间配置器相关
		Alloc get_allocator() { return dataAllocator; }

	private:
		void destoryAndDeallocateAll();
		void allocateAndFillN(const size_type n, const value_type& value);
		
		template <class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last);

		template <class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type);
	
		template <class Integer>
		void vector_aux(Integer n, const value_type value, std::true_type);
	
		template <class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
	
		template <class Integer>
		void insert_aux(iterator position, Integer n, const value_type value, std::true_type);
	
		template <class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		
		void reallocateAndFillN(iterator position, const size_type n, const value_type& val);
		size_type getNewCapacity(size_type len) const;
	
	public:
		template <class T, class Alloc>
		friend bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);

		template <class T, class Alloc>
		friend bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
	};
}

#include "Detail\Vector.impl.h"
#endif