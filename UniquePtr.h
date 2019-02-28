#include <iostream>
template<typename T>
class UniquePtr
{
public:
    explicit UniquePtr(T* ptr);
    ~UniquePtr();

    T* operator->() const;
    T& operator*() const;
	operator bool() const;
    T* get() const;

private:
    // Prevent coping 
    UniquePtr(UniquePtr const&);
    UniquePtr& operator=(UniquePtr const&);

    T* m_ptr;
};


template<typename T>
UniquePtr<T>::UniquePtr(T* ptr)
{
	m_ptr = ptr;
}


template<typename T>
UniquePtr<T>::~UniquePtr()
{
	delete (m_ptr);
}


template<typename T>
T* UniquePtr<T>::operator->() const
{
	return m_ptr;
}


template<typename T>
T* UniquePtr<T>::get() const
{
   if(m_ptr)
       return m_ptr;
   return NULL;
}

template<typename T>
T& UniquePtr<T>::operator*()  const
{
	return *m_ptr;
}

template<typename T>
UniquePtr<T>::operator bool()  const
{
	if (m_ptr)
		return true;
	return false;
}

