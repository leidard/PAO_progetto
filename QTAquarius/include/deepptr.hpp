
#ifndef DEEPPTR_H
#define DEEPPTR_H
#include <iostream>

template <class T>
class DeepPtr {
   private:
    T* ptr;

   public:
    DeepPtr(T* = nullptr);
    DeepPtr(const DeepPtr<T>& d);  // delete this
    DeepPtr(DeepPtr<T>&& d);
    DeepPtr& operator=(const DeepPtr<T>& d);  // delete this
    DeepPtr& operator=(DeepPtr<T>&& d);
    ~DeepPtr();

    T* get() const;

    T* release();

    void swap(DeepPtr<T>&);

    operator bool() const;
    bool operator!() const;

    T& operator*() const;

    T* operator->() const;
};

template <class T>
DeepPtr<T>::DeepPtr(T* p) : ptr(p) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr<T>& d) : ptr(d ? d.ptr->clone() : nullptr) { std::cout << "clonato!" << std::endl; }

template <class T>
DeepPtr<T>::DeepPtr(DeepPtr<T>&& d) : ptr(d.ptr) { d.ptr = nullptr; }

template <class T>
DeepPtr<T>::~DeepPtr() { delete ptr; }

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr<T>& d) {
    if (this != &d) {
        delete ptr;
        if (d)
            ptr = d.ptr->clone();
        else
            ptr = nullptr;
    }
    return *this;
}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(DeepPtr<T>&& d) {
    if (this != &d) {
        delete ptr;
        ptr = d.ptr;
        d.ptr = nullptr;
    }
    return *this;
}

template <class T>
T* DeepPtr<T>::get() const { return ptr; }

template <class T>
T* DeepPtr<T>::release() {
    T* tmp = ptr;
    ptr = nullptr;
    return tmp;
}

template <class T>
void DeepPtr<T>::swap(DeepPtr<T>& d) {
    T* tmp = ptr;
    ptr = d.ptr;
    d.ptr = tmp;
}

template <class T>
DeepPtr<T>::operator bool() const { return ptr != nullptr; }

template <class T>
bool DeepPtr<T>::operator!() const { return ptr == nullptr; }

template <class T>
T& DeepPtr<T>::operator*() const { return *ptr; }

template <class T>
T* DeepPtr<T>::operator->() const { return ptr; }

#endif
