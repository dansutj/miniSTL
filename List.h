#ifndef _LIST_H_
#define _LIST_H_

#include "Allocator.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"
#include "Utility.h"
#include <type_traits>

namespace miniSTL
{
	template <class T>
	class list;

	namespace Detail 
	{
		//class of Node
		template <class T>
		struct Node {
			T data;
			Node* prev;
			Node* next;
			list<T>* container;

			Node(const T& d, Node* p, Node* n, list<T>* c) :
				data(d), prev(p), next(n), container(c) {}

			bool operator == (const Node& n){
				return data == n.data && prev == n.prev &&
					next == n.next && container == n.container;
			}
		};

		//class of iterator
		template <class T>
		struct listIterator : public iterator<bidirectional_iterator_tag, T>
		{
			template <class T>
			friend class list;

		public:
			typedef Node<T>* nodeptr;
			nodeptr p;

		public:
			listIterator(nodeptr ptr = nullptr) : p(ptr) {}

			listIterator& operator++();
			listIterator operator++(int);
			listIterator& operator--();
			listIterator operator--(int);

			T& operator *() { return p->data; }
			T* operator ->() { return &operator*(); }

			template <class T>
			friend bool operator == (const listIterator& lhs, const listIterator& rhs);

			template <class T>
			friend bool operator != (const listIterator& lhs, const listIterator& rhs);
		};
	}
	//end of Detail

	//class of list
	template <class T>
	class list 
	{
		template <class T>
		friend struct listIterator;

	private:
		typedef allocator<Detail::Node<T>> nodeAllocator;
		typedef Detail::Node<T>* nodeptr;

	public:
		typedef T value_type;
		typedef Detail::listIterator<T> iterator;
		typedef Detail::listIterator<const T> const_iterator;
		typedef T& reference;
		typedef size_t size_type;

	private:
		iterator head;
		iterator tail;

	public:
		list();
		explicit list(size_t n, const value_type& val = value_type());

		template<class InputIterator>
		list(InputIterator first, InputIterator last);

		list(const list& l);
		list& operator = (const list& l);
		~list();

		bool empty() const { return head == tail; }
		size_t size() const;

		reference front() { return head.p->data; }
		reference back() { return tail.p->prev->data; }

		void push_front(const value_type& val);
		void pop_front();

		void push_back(const value_type& val);
		void pop_back();

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_t n, const value_type& val);

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		void swap(list& l);
		void clear();

		void splice(iterator position, list& l);
		void splice(iterator position, list& l, iterator i);
		void splice(iterator position, list& l, iterator first, iterator last);

		void remove(const value_type& val);

		template<class Predicate>
		void remove_if(Predicate pred);

		void unique();

		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred);

		void merge(list& l);

		template <class Compare>
		void merge(list& l, Compare comp);

		void sort();

		template <class Compare>
		void sort(list& l, Compare comp);

		void reverse();

	private:
		void ctorAux(size_type n, const value_type& val, std::true_type);

		template <class InputIterator>
		void ctorAux(InputIterator first, InputIterator last, std::false_type);

		nodeptr newNode(const T& val = T());
		void deleteNode(nodeptr ptr);

		void insert_aux(iterator position, size_type n, const T& val, std::true_type);

		template <class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
	
	public:
		template <class T>
		friend void swap(list<T>& x, list<T>& y);

		template<class T>
		friend bool operator==(const list<T>& lhs, const list<T>& rhs);

		template<class T>
		friend bool operator!=(const list<T>& lhs, const list<T>& rhs);
	};
}

#include "Detail\List.impl.h"
#endif // _LIST_H_
