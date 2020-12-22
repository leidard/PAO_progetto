#include "vector.h"

template <class T>
Vector<T>::Vector() : _buffer(nullptr), _size(0), _capacity(0) {}

template <class T>
Vector<T>::Vector(unsigned int size) : _buffer(nullptr), _size(0), _capacity(0) {
    reserve(size);
}

template <class T>
Vector<T>::Vector(const Vector& v) : _buffer(new T[v._capacity]), _size(v._size), _capacity(v._capacity) {
    for (unsigned int i = 0; i < v._size; i++) _buffer[i] = v._buffer[i];
}

template <class T>
Vector<T>::~Vector() { delete[] _buffer; }

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
    if (this != &b) {
        delete _buffer;

        _buffer = new T[v._capacity];
        _size = v._size;
        _capacity = v._capacity;

        for (unsigned int i = 0; i < v._size; i++) _buffer[i] = v._buffer[i];
    }
    return *this;
}

template <class T>
T* Vector<T>::begin() { return _buffer; };

template <class T>
const T* Vector<T>::begin() const { return _buffer; };

template <class T>
T* Vector<T>::end() { return _buffer + _size; }

template <class T>
const T* Vector<T>::end() const { return _buffer + _size; };

template <class T>
unsigned int Vector<T>::size() { return _size; };

template <class T>
unsigned int Vector<T>::capacity() { return _capacity; };

template <class T>
bool Vector<T>::is_empty() { return _size == 0; };

template <class T>
T& Vector<T>::at(unsigned int index) { return _buffer[index]; }
template <class T>
const T& Vector<T>::at(unsigned int index) const { return _buffer[index]; }

template <class T>
T& Vector<T>::operator[](unsigned int index) { return _buffer[index]; }
template <class T>
const T& Vector<T>::operator[](unsigned int index) const { return _buffer[index]; }

template <class T>
T& Vector<T>::front() { return _buffer[0]; }  // access element at the front
template <class T>
const T& Vector<T>::front() const { return _buffer[0]; }

template <class T>
T& Vector<T>::back() { return _buffer[size - 1]; }  // access element at the back
template <class T>
const T& Vector<T>::back() const { return _buffer[size - 1]; }

template <class T>
void Vector<T>::push_back(const T& v) {
    if (_size >= _capacity)
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    _buffer[_size++] = v;
}

template <class T>
void Vector<T>::pop_back() { erase(--_size); }

template <class T>
void Vector<T>::erase(unsigned int index) {
    delete _buffer[index];
}

template <class T>
void Vector<T>::clear() {
    _size = 0;
    _capacity = 0;
    delete[] _buffer;
    _buffer = nullptr;
}

template <class T>
void Vector<T>::reserve(unsigned int n) {
    if (n > _capacity) {
        T* newbuff = new T[n];
        for (unsigned int i = 0; i < _size; i++)
            newbuff[i] = _buffer[i];

        _capacity = n;
        delete[] _buffer;
        _buffer = newbuff;
    }
}