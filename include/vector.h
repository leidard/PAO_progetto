#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector {
   private:
    T* _buffer;
    unsigned int _size;
    unsigned int _capacity;

   public:
    Vector(unsigned int = 0);
    Vector(const Vector&);
    ~Vector();
    Vector& operator=(const Vector&);

    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;

    unsigned int size();
    unsigned int capacity();
    bool is_empty();

    T& at(unsigned int);
    const T& at(unsigned int) const;

    T& operator[](unsigned int);
    const T& operator[](unsigned int) const;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void push_back(const T&);
    void pop_back();
    T* erase(T*);
    void clear();
    void reserve(unsigned int);

    void insert(const T&, unsigned int);

    // assign();  // assign vector content with many overloads if I remember correctly
    // insert(const T& value);
};

template <class T>
Vector<T>::Vector(unsigned int capacity = 1) : _buffer(new T[capacity == 0 ? 1 : capacity]), _size(0), _capacity(capacity) {
}

template <class T>
Vector<T>::Vector(const Vector& v) : _buffer(new T[v._capacity]), _size(v._size), _capacity(v._capacity) {
    for (unsigned int i = 0; i < v._size; i++) _buffer[i] = v._buffer[i];
}

template <class T>
Vector<T>::~Vector() { delete[] _buffer; }

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
    if (this != &v) {
        delete[] _buffer;

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
T& Vector<T>::back() { return _buffer[_size - 1]; }  // access element at the back
template <class T>
const T& Vector<T>::back() const { return _buffer[_size - 1]; }

template <class T>
void Vector<T>::push_back(const T& v) {
    if (_size >= _capacity)
        reserve(_capacity * 2);
    _buffer[_size++] = v;
}

template <class T>
void Vector<T>::pop_back() { --_size; }

template <class T>
T* Vector<T>::erase(T* pos) {  // TODO CHECK THIS
    T* aux = pos;
    while (pos < (_buffer + _size - 1)) {
        pos[0] = pos[1];
        pos++;
    }
    --_size;
    return aux;
}

template <class T>
void Vector<T>::clear() {
    delete[] _buffer;
    _size = 0;
    _capacity = 1;
    _buffer = new T[1];
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

template <class T>
void Vector<T>::insert(const T& v, unsigned int index) {
    reserve(++_size);

    for (unsigned int j = _size - 1; j > index; j++)
        _buffer[j] = _buffer[j - 1];

    _buffer[index] = v;
}

#endif