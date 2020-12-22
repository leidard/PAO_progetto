
#ifndef DEEPPTR_H
#define DEEPPTR_H
template <class T>
class DeepPtr {
   private:
    T* ptr;

   public:
    DeepPtr(T*);
    DeepPtr(const DeepPtr<T>& d);
    DeepPtr& operator=(const DeepPtr<T>& d);
    ~DeepPtr();
    T* get() const;

    T* release();
    void swap(const DeepPtr<T>&);

    operator bool() const;
    T& operator*() const;
    T* operator->() const;
};
#endif