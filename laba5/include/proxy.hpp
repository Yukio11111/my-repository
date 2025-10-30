#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>
#include <utility> // Для std::lock_guard, хотя в <mutex> он тоже есть

template<class T, class MutexInjection = std::mutex>
class ptr_holder
{
public:
    ptr_holder(T* ptr): ptr_(ptr) {}

    class proxy
    {
    public:
        proxy(T* ptr, MutexInjection& mtx) : ptr_(ptr), lock_(mtx) {}

        T* operator->() const
        {
            return ptr_;
        }

    private:
        T* ptr_;
        std::lock_guard<MutexInjection> lock_;
    };

    proxy operator->() const
    {
        return proxy(ptr_, mutex_);
    }

private:
    T* ptr_;
    mutable MutexInjection mutex_;
};

#endif // __PROXY_HPP__