#pragma once
#include <iostream>
template <class T>
class UniquePointer {
	T* unique;
	void free();
	void moveFrom(UniquePointer&& other);
public:
	UniquePointer(T* obj);
	UniquePointer(const UniquePointer& other) = delete;
	UniquePointer<T>& operator=(const UniquePointer& other) = delete;

	UniquePointer(UniquePointer&& other) noexcept;
	UniquePointer& operator=(UniquePointer&& other) noexcept;

	T* operator->();
	const T* operator->() const;

	const T& operator*() const;
	T& operator*();
	~UniquePointer();
};

template<class T>
void UniquePointer<T>::free()
{
	delete unique;
}

template<class T>
void UniquePointer<T>::moveFrom(UniquePointer&& other)
{
	unique = other.unique;
	other.unique = nullptr;
}

template<class T>
UniquePointer<T>::UniquePointer(T* obj) : unique(obj)
{
}

template<class T>
UniquePointer<T>::UniquePointer(UniquePointer&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
	// TODO: insert return statement here
}



template<class T>
T* UniquePointer<T>::operator->()
{
	return unique;
}

template<class T>
const T* UniquePointer<T>::operator->() const
{
	return unique;
}

template<class T>
const T& UniquePointer<T>::operator*() const
{
	return *unique;
	
}

template<class T>
T& UniquePointer<T>::operator*()
{
	return *unique;
}

template<class T>
UniquePointer<T>::~UniquePointer()
{
	free();
}
