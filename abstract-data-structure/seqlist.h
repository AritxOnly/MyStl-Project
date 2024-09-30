#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <iostream>
#include <stdexcept>

const long long MAX_SIZE = 2147483647;
const int DEFAULT_CAPACITY = 100;

template<class T>
class SeqList {
public:
    SeqList();
    virtual ~SeqList();

    void clear() {
        if (arr != nullptr)
            delete[]arr;
        size = 0;
        capacity = 0;
        arr = nullptr;
    }

    // 迭代器类定义
    class iterator {
    public:
        iterator(int _index, int _size = 0, T* _arr = nullptr) : 
            index(_index), size(_size), arr(_arr) {
            if (index >= size || index < 0)
                index = -1;
        }

        T& operator*() const {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            if (arr == nullptr) {
                throw std::overflow_error("arr not initialized");
            }
            return arr[index];
        }

        iterator operator+(const int n) {
            return iterator(index + n, size, arr);
        }

        iterator operator-(const int n) {
            return iterator(index - n, size, arr);
        }

        iterator& operator++() {
            index++;
            if (index >= size) {
                index = -1;
            }
            return *this;
        }

        bool operator!=(const iterator& other) {
            return (index != other.index) ? true : false;
        }

        bool operator==(const iterator& other) {
            return (index == other.index) ? true : false;
        }

        int getIndex() {
            return index;
        }

    private:
        int index = 0;
        int size = 0;
        T* arr = nullptr;
    };

protected:
    T* arr;
    int size;
    int capacity;

    void expand();  // 扩容
};


#define _TPL template<class T>
#define _SL SeqList<T>

_TPL
_SL::SeqList() : arr(nullptr), size(0), capacity(0) {}

_TPL
_SL::~SeqList() {
    if (arr != nullptr) 
        clear();
}

_TPL
void _SL::expand() {
    if (capacity == 0) {
        capacity = DEFAULT_CAPACITY;
    }

    if (capacity > MAX_SIZE) {
        throw std::overflow_error("Capacity out of range");
    }

    capacity *= 2;
    capacity = (capacity > MAX_SIZE) ? (MAX_SIZE - 1) : capacity;
    T* newArr = new T[capacity];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[]arr;
    arr = newArr;
}
#endif