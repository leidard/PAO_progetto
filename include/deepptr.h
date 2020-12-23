
#ifndef DEEPPTR_H
#define DEEPPTR_H
template <class T>
class DeepPtr {
   private:
    T* ptr;

   public:
    DeepPtr(T* = nullptr);
    DeepPtr(const DeepPtr<T>& d);
    DeepPtr& operator=(const DeepPtr<T>& d);
    ~DeepPtr();
    T* get() const;

    T* release();
    void swap(DeepPtr<T>&);

    operator bool() const;
    T& operator*() const;
    T* operator->() const;
};

template <class T>
DeepPtr<T>::DeepPtr(T* p) : ptr(p->clone()) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr<T>& d) : ptr(d.ptr->clone()) {}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr<T>& d) {
    if (this != &d) {
        delete ptr;
        ptr = d.ptr->clone();
    }
    return *this;
}

template <class T>
DeepPtr<T>::~DeepPtr() { delete ptr; }

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
T& DeepPtr<T>::operator*() const { return *ptr; }

template <class T>
T* DeepPtr<T>::operator->() const { return ptr; }

#endif