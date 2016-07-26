#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <utility>
#include "Detail\Ref.h"

namespace miniSTL
{
	template <class T>
	struct _default_delete {
		void operator()(T* ptr) { if (ptr) delete ptr; }
	};

	template <class T>
	struct _default_delete<T[]>{
		void operator()(T* ptr) { if (ptr) delete[] ptr; }
	};

	template <class T, class D = _default_delete<T>>
	class unique_ptr {
	public:
		typedef T element_type;
		typedef D deleter_type;
		typedef element_type* pointer;

	public:
		explicit unique_ptr(T* data = nullptr) : data_(data) {}
		unique_ptr(T* data, D del) : data_(data), deleter(del) {}

		unique_ptr(unique_ptr&& up) : data_(nullptr) {
			miniSTL::swap(data_, up.data_());
		}                                                              

		unique_ptr& operator=(unique_ptr&& up){
			if (this != &up){
				clean();
				miniSTL::swap(*this, up);
			}
			return *this;
		}

		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator=(const unique_ptr&) = delete;

		~unique_ptr() { clean(); }

		const element_type* get() const { return data_; }
		element_type* get() { return data_; }
		const deleter_type& get_deleter() const { return deleter; }
		deleter_type& get_deleter() { return deleter; }

		operator bool() const { return get() == nullptr; }

		element_type* release()
		{
			T* p = nullptr;
			miniSTL::swap(p, data_);
			return p;
		}

		void reset(pointer p = pointer())
		{
			clean();
			data_ = p;
		}

		void swap(unique_ptr& up) { miniSTL::swap(data_, up.data_); }

		const element_type& operator*() const { return *data_; }
		const element_type* operator->() const { return data_; }
		element_type& operator*() { return *data_; }
		element_type* operator->() { return data_; }

	private:
		inline void clean() {
			deleter(data_);
			data_ = nullptr;
		}

		element_type* data_;
		deleter_type deleter;
	};

	template <class T>
	class shared_ptr {
	public:
		typedef T element_type;
	private:
		template <class Type>
		using ref_t = Detail::ref_t<Type>;

	public:
		explicit shared_ptr(T* ptr = nullptr) : ref_(new ref_t<T>(ptr)) {}

		template <class D>
		shared_ptr(T* p, D del) : ref_t(new ref_t<T, del>(p)) {}

		shared_ptr(const shared_ptr& sp){
			copy_ref(sp.ref_);
		}

		shared_ptr& operator=(const shared_ptr& sp){
			if (this != &sp){
				decrease_ref();
				copy_ref(sp.ref_);
			}
			return *this;
		}

		~shared_ptr() { decrease_ref(); }

		const element_type& operator*() const { return *(get()); }
		const element_type* operator->() const { return get(); }
		element_type& operator*() { return *(get()); }
		element_type* operator->() { return get(); }

		const element_type* get() const { return ref_->get_data(); }
		element_type* get() { return ref_->get_data(); }
		size_t use_count() { return ref_->count(); }

		operator bool() const { return get() != nullptr; }

	private:
		void decrease_ref() 
		{
			if (ref_->get_data())
			{
				--*(ref_);
				if (use_count() == 0)
					delete ref_;
			}
		}

		void copy_ref(ref_t<T>* r)
		{
			ref_ = r;
			++*(ref_);
		}

	private:
		ref_t<T>* ref_;
	};

	template <class T, class... Args>
	shared_ptr<T> make_shared(Args&&... args) {
		return shared_ptr<T>(new T(std::forward<Args>(args)...));
	}
}


#endif // _MEMORY_H_