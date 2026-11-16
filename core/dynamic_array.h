#pragma once
#include <string>
#include <utility>      
#include "exceptions.h"

template <class T>
class DynamicArray 
{

private:
    T*  data_;
    int size_;

    void CheckIndex(int index) const 
    {
        if (index < 0 || index >= size_)
            throw IndexOutOfRange(index, size_);
    }

    static void CheckSize(int size) 
    {
        if (size < 0)
            throw InvalidArgument("DynamicArray: size must be >= 0, got " + std::to_string(size));
    }

    static T* AllocateCopy(const T* src, int copyCount, int newSize) 
    {
        if (newSize == 0) return nullptr;

        T* block = new T[newSize]();
        try 
        {
            for (int i = 0; i < copyCount; ++i)
                block[i] = src[i];
        } 
        catch (...) 
        {
            delete[] block;  
            throw;            
        }
        return block;
    }

public:

    DynamicArray() : data_(nullptr), size_(0) {}

    explicit DynamicArray(int size) : data_(nullptr), size_(0)
    {
        CheckSize(size);
        data_ = AllocateCopy(nullptr, 0, size);   
        size_ = size;
    }

    DynamicArray(const T* items, int count) : data_(nullptr), size_(0) 
    {
        CheckSize(count);
        if (count > 0 && items == nullptr)
            throw InvalidArgument("DynamicArray: items is null, but count = " + std::to_string(count));
        data_ = AllocateCopy(items, count, count);
        size_ = count;
    }

    DynamicArray(const DynamicArray& other): 
        data_(AllocateCopy(other.data_, other.size_, other.size_)), size_(other.size_) {}


    DynamicArray& operator=(const DynamicArray& other) 
    {
        if (this != &other) 
        {
            DynamicArray copy(other);   
            Swap(copy);                 
        }                               
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept: data_(other.data_), size_(other.size_) 
    {
        other.data_ = nullptr;   
        other.size_ = 0;         
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept 
    {
        if (this != &other) 
        {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] data_;
    }



    const T& Get(int index) const 
    {
        CheckIndex(index);
        return data_[index];
    }

    void Set(int index, const T& value) 
    {
        CheckIndex(index);
        data_[index] = value;
    }

    T& operator[](int index) 
    {
        CheckIndex(index);
        return data_[index];
    }

    const T& operator[](int index) const 
    {
        CheckIndex(index);
        return data_[index];
    }

    int GetSize() const {return size_;}



    void Resize(int newSize) 
    {
        CheckSize(newSize);
        int keep = (size_ < newSize) ? size_ : newSize;   
        T* newData = AllocateCopy(data_, keep, newSize);  
        delete[] data_;                                   
        data_ = newData;
        size_ = newSize;
    }

    void Swap(DynamicArray& other) noexcept 
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }
};