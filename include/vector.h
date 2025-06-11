#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

template <typename T>
class Vector {
private:
	T* arr;
	int len;
	int cap;

	void double_capacity();

public:
	// Constructors and Destructor
	Vector();
	Vector(int count, T value);
	Vector(const Vector<T> &other);
	~Vector();

	// Operators
	Vector<T> &operator=(const Vector<T> &other);
	T &operator[](int index);
	const T &operator[](int index) const;
	bool operator==(const Vector<T> &other) const;
	bool operator!=(const Vector<T> &other) const;
	Vector<T> operator+(const Vector<T> &other) const;
	Vector<T> &operator+=(const Vector<T> &other);

	// Modifiers
	void push(T value);
	void pop();
	void insert_at(int index, T value);
	void delete_at(int index);
	void reserve(int new_cap);
	void clear();
	void swap(Vector<T> &other);
	void shrink_to_fit();
	void reverse();

	// Accessors
	bool empty() const;
	int size() const;

	T &at(int index);
	const T &at(int index) const;

	T &front();
	const T &front() const;

	T &back();
	const T &back() const;

	int find(T value);
};

#include "../include/Vector.h"

template<typename T>
void Vector<T>::double_capacity()
{
	cap = cap == 0 ? 1 : (cap * 2);
	T* new_arr = new T[cap];
	for (int i = 0; i < len; ++i)
		new_arr[i] = arr[i];

	delete[] arr;
	arr = new_arr;
}

template<typename T>
Vector<T>::Vector() : arr{nullptr}, len{0}, cap{0} {}

template<typename T>
Vector<T>::Vector(int count, T value) : len{count}, cap{count}
{
	arr = new T[cap];
	for (int i = 0; i < len; ++i)
		arr[i] = value;
}

template<typename T>
Vector<T>::Vector(const Vector<T> &other) : len{other.len}, cap{other.cap}
{
	if (other.cap == 0) return;

	arr = new T[cap];
	for (int i = 0; i < len; ++i)
		arr[i] = other.arr[i];
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] arr;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other)
{
	if (this != &other)
	{
		delete[] arr;
		len = other.len;
		cap = other.cap;

		if (cap == 0) arr = nullptr;
		else arr = new T[cap];

		for (int i = 0; i < len; ++i)
		{
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

template<typename T>
T &Vector<T>::operator[](int index) { return arr[index]; }

template<typename T>
const T &Vector<T>::operator[](int index) const { return arr[index]; }

template<typename T>
bool Vector<T>::operator==(const Vector<T> &other) const
{
	if (len != other.len) return false;
	for (int i = 0; i < len; ++i)
		if (arr[i] != other.arr[i]) return false;

	return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> &other) const { return !(*this ==
other); }

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &other) const
{
	Vector new_vec;
	new_vec.cap = len + other.len;
	new_vec.len = new_vec.cap;
	new_vec.arr = new T[new_vec.cap];

	for (int i = 0; i < len; ++i)
		new_vec.arr[i] = arr[i];
	for (int i = len; i < new_vec.len; ++i)
		new_vec.arr[i] = other.arr[i - len];

	return new_vec;
}

template<typename T>
Vector<T> &Vector<T>::operator+=(const Vector<T> &other)
{
	*this = *this + other;
	return *this;
}

template<typename T>
void Vector<T>::push(T value)
{
	if(len + 1 > cap) double_capacity();
	arr[len] = value;
	++len;
}

template<typename T>
void Vector<T>::pop() { if(len != 0) --len; }

template<typename T>
void Vector<T>::insert_at(int index, T value)
{
	if (index > len || index < 0) throw(std::out_of_range("Invalid index"));
	if (++len > cap) double_capacity();

	for(int i = len - 1; i > index; ++i)
		arr[i] = arr[i - 1];
	arr[index] = value;
}

template<typename T>
void Vector<T>::delete_at(int index)
{
	if (index >= len || index < 0) throw(std::out_of_range("Invalid index"));
	--len;
	for(int i = index; i < len; ++i)
		arr[i] = arr[i + 1];
}

template<typename T>
void Vector<T>::reserve(int new_cap)
{
	if(new_cap <= cap)
		throw(std::runtime_error("Cannot reserve less than current capacity"));

	cap = new_cap;
	T* new_arr = new T[cap];
	for (int i = 0; i < len; ++i)
		new_arr[i] = arr[i];

	delete[] arr;
	arr = new_arr;
}

template<typename T>
void Vector<T>::clear()
{
	delete[] arr;
	arr = nullptr;
	len = 0; cap = 0;
}

template<typename T>
void Vector<T>::swap(Vector<T> &other)
{
	std::swap(this->arr, other.arr);
	std::swap(this->cap, other.cap);
	std::swap(this->len, other.len);
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
	if (len == 0)
	{
		delete[] arr;
		arr = nullptr;
		cap = 0;
	}
	else if (len != cap)
	{
		cap = len;
		T* new_arr = new T[len];
		for(int i = 0; i < len; ++i)
			new_arr[i] = arr[i];

		delete[] arr;
		arr = new_arr;
	}
}

template<typename T>
void Vector<T>::reverse()
{
	for (int i = 0; i < len/2; ++i)
		std::swap(arr[i], arr[len - i -1]);
}

template<typename T>
bool Vector<T>::empty() const { return (len == 0); }

template<typename T>
int Vector<T>::size() const { return len; }

template<typename T>
T &Vector<T>::at(int index)
{
	if (index < 0 || index >= len)
		throw(std::out_of_range("Accessing out of bounds value"));
	return arr[index];
}

template<typename T>
const T &Vector<T>::at(int index) const
{
	if (index < 0 || index >= len)
		throw(std::out_of_range("Accessing out of bounds value"));
	return arr[index];
}

template<typename T>
T &Vector<T>::front()
{
	if (len == 0)
		throw(std::out_of_range("Empty vector array"));
	return arr[0];
}

template<typename T>
const T &Vector<T>::front() const
{
	if (len == 0)
		throw(std::out_of_range("Empty vector array"));
	return arr[0];
}

template<typename T>
T &Vector<T>::back()
{
	if (len == 0)
		throw(std::out_of_range("Empty vector array"));
	return arr[len - 1];
}

template<typename T>
const T &Vector<T>::back() const
{
	if (len == 0)
		throw(std::out_of_range("Empty vector array"));
	return arr[len - 1];
}

template<typename T>
int Vector<T>::find(T value)
{
	for (int i = 0; i < len; ++i)
		if(arr[i] == value) return i;
	return -1;
}


#endif //VECTOR_H
