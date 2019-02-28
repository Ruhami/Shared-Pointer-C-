#include <iostream>
template<typename T>
class SharedPtr
{
public:
	template<class U>
	friend class SharedPtr;

    explicit SharedPtr(T* ptr = NULL);
    SharedPtr(const SharedPtr& other);
    ~SharedPtr();
	template<class U>
	SharedPtr(const SharedPtr& other);

    T* operator->() const;
    T& operator*()  const;

	SharedPtr& operator= (const SharedPtr& other);
	SharedPtr& operator= (T* other);
	
	bool operator!=(const SharedPtr& other) const;
	bool operator==(const SharedPtr& other) const;

	operator bool() const;
    T* get() const;	
	
private:
	void release();
	void swap(SharedPtr& other);

	T* m_ptr;
	size_t* refCount;
};

template<typename T>
void SharedPtr<T>::release()
{
	--(*refCount);
	if (*refCount == 0)
	{
		delete (m_ptr);
		delete (refCount);
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr)try 
	:m_ptr(ptr),
	refCount(new size_t(1))
{
}
catch(std::bad_alloc& e)
{
	delete ptr;
	throw;
}

template<class U>
SharedPtr(const SharedPtr<U>& other)
{

}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other):m_ptr(other.m_ptr), refCount(other.refCount)
{
	++(*refCount);
}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
	release();
}

template<typename T>
void SharedPtr<T>::swap(SharedPtr<T>& other)
{
	std::swap(m_ptr, other.m_ptr);
	std::swap(refCount, other.refCount);
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	SharedPtr<T> copyOfMe(other);
	swap(copyOfMe);
	return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(T* other)
{
    release();
    m_ptr = other;
	refCount = new size_t(1);
	return *this;
}

template<typename T>
T* SharedPtr<T>::operator->() const
{
	return m_ptr;
}


template<typename T>
T* SharedPtr<T>::get() const
{
   if(m_ptr)
       return m_ptr;
   return NULL;
}

template<typename T>
T& SharedPtr<T>::operator*()  const
{
	return *m_ptr;
}

template<typename T>
SharedPtr<T>::operator bool()  const
{
	if (m_ptr)
		return true;
	return false;
}

template<typename T>
bool SharedPtr<T>::operator==(const SharedPtr<T>& other) const
{
	return *m_ptr == *other.m_ptr;  

}

template<typename T>
bool SharedPtr<T>::operator!=(const SharedPtr<T>& other) const
{
	return !(*this == other);
}





