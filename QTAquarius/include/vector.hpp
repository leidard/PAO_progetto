#include <utility>

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

    class iterator;
    class const_iterator;

    class iterator {
       protected:
        T* _current;

       public:
        iterator(T* i = nullptr) : _current(i) {}
        iterator(const iterator& i) : _current(i._current) {}
        iterator& operator=(const iterator& i) {
            if (this != &i) {
                _current = i._current;
            }
            return *this;
        }
        T& operator*() const { return *_current; }
        T* operator->() const { return _current; }
        T& operator[](int n) const { return _current[n]; }

        iterator operator++(int) { return iterator(_current++); }
        iterator operator--(int) { return iterator(_current--); }
        iterator operator+(int n) const { return iterator(_current + n); }
        iterator operator-(int n) const { return iterator(_current - n); }
        iterator& operator++() {
            ++_current;
            return *this;
        }
        iterator& operator--() {
            --_current;
            return *this;
        }
        iterator& operator+=(int n) {
            _current += n;
            return *this;
        }
        iterator& operator-=(int n) {
            _current -= n;
            return *this;
        }
        operator const_iterator() { return const_iterator(_current); }
        bool operator==(const iterator& i) const { return _current == i._current; }
        bool operator!=(const iterator& i) const { return _current != i._current; }
        bool operator<(const iterator& i) const { return _current < i._current; }
        bool operator>(const iterator& i) const { return _current > i._current; }
        bool operator<=(const iterator& i) const { return _current <= i._current; }
        bool operator>=(const iterator& i) const { return _current >= i._current; }
    };

    class const_iterator {
       protected:
        T* _current;

       public:
        const_iterator(T* i = nullptr) : _current(i) {}
        const_iterator(const const_iterator& i) : _current(i._current) {}
        const T& operator*() const { return *_current; }
        const T* operator->() const { return _current; }
        const T& operator[](int n) const { return _current[n]; }

        const_iterator operator++(int) { return const_iterator(_current++); }
        const_iterator operator--(int) { return const_iterator(_current--); }
        const_iterator operator+(int n) const { return const_iterator(_current + n); }
        const_iterator operator-(int n) const { return const_iterator(_current - n); }
        const_iterator& operator++() {
            ++_current;
            return *this;
        }
        const_iterator& operator--() {
            --_current;
            return *this;
        }
        const_iterator& operator+=(int n) {
            _current += n;
            return *this;
        }
        const_iterator& operator-=(int n) {
            _current -= n;
            return *this;
        }
        operator iterator() { return iterator(_current); }
        bool operator==(const const_iterator& i) const { return _current == i._current; }
        bool operator!=(const const_iterator& i) const { return _current != i._current; }
        bool operator<(const const_iterator& i) const { return _current < i._current; }
        bool operator>(const const_iterator& i) const { return _current > i._current; }
        bool operator<=(const const_iterator& i) const { return _current <= i._current; }
        bool operator>=(const const_iterator& i) const { return _current >= i._current; }
    };

    unsigned int size() const;
    unsigned int capacity() const;
    bool is_empty() const;

    iterator begin();
    iterator end();
    T& at(unsigned int);
    T& operator[](unsigned int);
    T& front();
    T& back();

    const_iterator begin() const;
    const_iterator end() const;
    const T& at(unsigned int) const;
    const T& operator[](unsigned int) const;
    const T& front() const;
    const T& back() const;

    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    iterator erase(iterator);
    void clear();
    void reserve(unsigned int);

    void insert(iterator pos, const T& val);
    void insert(iterator pos, unsigned int fill, const T& val);
    void swap(Vector&);

    void resize(unsigned int);
    void resize(unsigned int, const T&);
    void shrink_to_fit();

    // assign();  // assign vector content with many overloads if I remember correctly
};

template <class T>
Vector<T>::Vector(unsigned int capacity) : _buffer(new T[capacity == 0 ? 1 : capacity]), _size(0), _capacity(capacity == 0 ? 1 : capacity) {
}

template <class T>
Vector<T>::Vector(const Vector& v) : _buffer(new T[v._capacity]), _size(v._size), _capacity(v._capacity) {
    for (unsigned int i = 0; i < v._size; i++) _buffer[i] = std::move(v._buffer[i]);
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

        for (unsigned int i = 0; i < v._size; i++) _buffer[i] = std::move(v._buffer[i]);
    }
    return *this;
}

template <class T>
unsigned int Vector<T>::size() const { return _size; };

template <class T>
unsigned int Vector<T>::capacity() const { return _capacity; };

template <class T>
bool Vector<T>::is_empty() const { return _size == 0; };

template <class T>
typename Vector<T>::iterator Vector<T>::begin() { return Vector<T>::iterator(_buffer); };
template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const { return Vector<T>::const_iterator(_buffer); };

template <class T>
typename Vector<T>::iterator Vector<T>::end() { return Vector<T>::iterator(_buffer + _size); };
template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const { return Vector<T>::const_iterator(_buffer + _size); };

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
void Vector<T>::push_back(T&& v) {
    if (_size >= _capacity)
        reserve(_capacity * 2);
    _buffer[_size++] = std::move(v);
}

template <class T>
void Vector<T>::pop_back() { --_size; }

template <class T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator pos) {  // TODO CHECK THIS
    Vector<T>::iterator aux = pos;
    while (pos < (_buffer + _size - 1)) {
        pos[0] = std::move(pos[1]);
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
            newbuff[i] = std::move(_buffer[i]);  // if _capacity == 0 => _size == 0 never reached

        _capacity = n;
        delete[] _buffer;  // if _buffer == nullptr => no delete
        _buffer = newbuff;
    } else if (_capacity == 0) {  // n <= _capacity && _capacity == 0 =>  n == 0
        _buffer = new T[1];
        _capacity = 1;
    }
}

template <class T>
void Vector<T>::insert(Vector<T>::iterator pos, const T& v) {
    reserve(++_size);

    for (auto scorri = --end(); scorri > pos; pos--) scorri[0] = std::move(scorri[-1]);
    *pos = v;
}

template <class T>
void Vector<T>::insert(Vector<T>::iterator pos, unsigned int fill, const T& v) {
    if (fill == 0) return;
    _size += fill;
    reserve(_size);

    for (auto scorri = --end(); scorri > pos; pos--) scorri[0] = std::move(scorri[-1]);

    for (auto scorri = pos; scorri <= (pos + ((int)fill)); scorri++) *scorri = v;
}

template <class T>
void Vector<T>::resize(unsigned int newsize) {
    if (newsize > _capacity)
        reserve(newsize);
    _size = newsize;
}

template <class T>
void Vector<T>::resize(unsigned int newsize, const T& v) {
    if (newsize > _capacity) {
        reserve(newsize);
        for (unsigned int i = _size; i < newsize; i++) _buffer[i] = std::move(v);
    }
    _size = newsize;
}

template <class T>
void Vector<T>::shrink_to_fit() {
    if (_size == _capacity) return;
    if (_size == 0) {
        _buffer = new T[1];
        _capacity = 1;
        return;
    }
    T* newbuff = new T[_size];
    for (unsigned int i = 0; i < _size; i++) newbuff[i] = std::move(_buffer[i]);

    _buffer = newbuff;
    _capacity = _size;
}

#endif
