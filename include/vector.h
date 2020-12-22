#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector {
   private:
    T* _buffer;
    unsigned int _size;
    unsigned int _capacity;

   public:
    Vector();
    Vector(unsigned int);
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
    void erase(unsigned int);
    void clear();
    void reserve(unsigned int);

    // assign();  // assign vector content with many overloads if I remember correctly
    // insert();
};

#endif