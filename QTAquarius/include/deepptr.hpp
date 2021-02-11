#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>
class DeepPtr {
private:
    T* ptr;

public:
    DeepPtr(T* = nullptr);
    DeepPtr(const DeepPtr& d);
    ~DeepPtr();
    DeepPtr& operator=(const DeepPtr& d);

    DeepPtr(DeepPtr&& d);
    DeepPtr& operator=(DeepPtr&& d);

    T* get() const;

    operator bool() const;

    bool operator!() const;

    T& operator*() const;

    T* operator->() const;
};

template <class T>
DeepPtr<T>::DeepPtr(T* p) : ptr(p) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr<T>& d) : ptr(d ? d.ptr->clone() : nullptr) {}

template <class T>
DeepPtr<T>::~DeepPtr() { delete ptr; }

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr<T>& d) {
    if (this != &d) {
        delete ptr;
        ptr = d ? d.ptr->clone() : nullptr;
    }
    return *this;
}

template <class T>
DeepPtr<T>::DeepPtr(DeepPtr<T>&& d) : ptr(d.ptr) { d.ptr = nullptr; }

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
DeepPtr<T>::operator bool() const { return ptr != nullptr; }

template <class T>
bool DeepPtr<T>::operator!() const { return ptr == nullptr; }

template <class T>
T& DeepPtr<T>::operator*() const { return *ptr; }

template <class T>
T* DeepPtr<T>::operator->() const { return ptr; }

#endif
