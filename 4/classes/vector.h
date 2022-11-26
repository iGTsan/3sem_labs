/** \file
 * \brief Файл с моей реализацие STL контейнера vector
 */

#ifndef CLASSES_VECTOR_H_
#define CLASSES_VECTOR_H_

#include <cstddef>

namespace std {
	template <typename T>
	class MyVectorIt {
	private:
		T* data;
	public:
		MyVectorIt(T* data = nullptr) : data(data) {}
		bool operator !=(const MyVectorIt<T>& other) const;
		bool operator ==(const MyVectorIt<T>& other) const;
		MyVectorIt<T> operator ++(int);
		MyVectorIt<T>& operator ++();
		T& operator * ();
	};

	template <class T>
	class MyVector {
	private:
		T* data;
		size_t len;
		size_t max_len;
	public:
		MyVector();
		MyVector(int n);
		MyVector(int n, const T& value);
		MyVector(const MyVector<T>& other);
		MyVector(MyVector<T>&& other);
		size_t size() const;
		T& operator[](size_t i);
		MyVector<T>& operator =(const MyVector<T>& other);
		MyVector<T>& operator =(MyVector<T>&& other);
		const T& operator[](size_t i) const;
		void push_back(const T& value);
		void resize(size_t n);
		void resize(size_t n, const T& value);
		bool empty() const;
		typedef MyVectorIt<T> Iterator;
		Iterator begin() const;
		Iterator end() const;
		Iterator erase(Iterator it);
		~MyVector();
	};
}

template<typename T>
bool std::MyVectorIt<T>::operator !=(const MyVectorIt<T> &other) const {
	return (data != other.data);
}

template<typename T>
bool std::MyVectorIt<T>::operator ==(const MyVectorIt<T> &other) const {
	return (data == other.data);
}

template<typename T>
std::MyVectorIt<T> std::MyVectorIt<T>::operator ++(int) {
	MyVectorIt<T> tmp(*this);
	data++;
	return (tmp);
}

template<typename T>
std::MyVectorIt<T>& std::MyVectorIt<T>::operator ++() {
	data++;
	return (*this);
}

template<typename T>
T& std::MyVectorIt<T>::operator *() {
	return (*data);
}

template<typename T>
std::MyVector<T>::MyVector() :  data(nullptr), len(0), max_len(0) {}

template<typename T>
std::MyVector<T>::MyVector(int n) {
	len = n;
	max_len = n;
	data = new T[n];
}

template<typename T>
std::MyVector<T>::MyVector(int n, const T &value) {
	len = n;
	max_len = n;
	data = new T[n];
	for (auto elem: *this)
		elem = value;
}

template<typename T>
size_t std::MyVector<T>::size() const {
	return (len);
}

template<typename T>
T& std::MyVector<T>::operator [](size_t i) {
//	if (i >= len || i < 0)
//		throw out_of_range("Bad index");
	return (data[i]);
}

template<typename T>
const T& std::MyVector<T>::operator [](size_t i) const {
//	if (i >= len || i < 0)
//		throw out_of_range("Bad index");
	return (data[i]);
}

template<typename T>
void std::MyVector<T>::push_back(const T &value) {
	if (len == max_len) {
		max_len = max_len * 2 + 1;
		T* tmp = data;
		data = new T[max_len];
		move(tmp, tmp + len, data);
		delete [] tmp;
	}
	data[len++] = value;
}

template<typename T>
void std::MyVector<T>::resize(size_t n) {
	max_len = n;
	if (len > n)
		len = n;
	T* tmp = data;
	data = new T[max_len];
	move(tmp, tmp + len, data);
	for (auto i = len; i < n; i++)
		data[i] = T();
	len = n;
	delete [] tmp;
}

template<typename T>
void std::MyVector<T>::resize(size_t n, const T &value) {
	size_t prev_len = len;
	resize(n);
	for (;prev_len < len; prev_len++)
		data[prev_len] = value;
}

template<typename T>
bool std::MyVector<T>::empty() const {
	return (len == 0);
}

template<typename T>
typename std::MyVector<T>::Iterator std::MyVector<T>::begin() const {
	return (Iterator(data));
}

template<typename T>
typename std::MyVector<T>::Iterator std::MyVector<T>::end() const {
	return (Iterator(data + len));
}

template<typename T>
typename std::MyVector<T>::Iterator std::MyVector<T>::erase(Iterator it) {
	len--;
	while (it != end()) {
		auto curr = it;
		it++;
		*curr = *it;
	}
	return (it);
}

template<class T>
std::MyVector<T>::MyVector(const MyVector<T> &other) {
	max_len = other.max_len;
	len = other.len;
	data = new T[max_len];
	copy(other.data, other.data + len, data);
}

template<class T>
std::MyVector<T>& std::MyVector<T>::operator =(const MyVector<T> &other) {
	max_len = other.max_len;
	len = other.len;
	delete [] data;
	data = new T[max_len];
	copy(other.data, other.data + len, data);
	return (*this);
}

template<class T>
std::MyVector<T>::MyVector(MyVector<T> &&other) {
	data = other.data;
	len = other.len;
	max_len = other.max_len;
}

template<class T>
std::MyVector<T>& std::MyVector<T>::operator =(MyVector<T> &&other) {
	delete [] data;
	data = other.data;
	len = other.len;
	max_len = other.max_len;
	return (*this);
}

template<typename T>
std::MyVector<T>::~MyVector() {
	delete[] data;
}


#endif
