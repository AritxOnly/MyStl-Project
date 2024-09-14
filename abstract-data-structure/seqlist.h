#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdexcept>

const long long MAX_SIZE = 2147483647;
const int DEFAULT_CAPACITY = 100;

template<class T>
class SeqList {
public:
    SeqList();
    virtual ~SeqList();

protected:
    T* arr;
    int size;
    int capacity;

    void expand();  // 扩容
};


#define _TPL template<class T>
#define _SL SeqList<T>

_TPL
_SL::SeqList() : capacity(0), size(0), arr(nullptr) {}

_TPL
_SL::~SeqList() { 
    if (arr != nullptr)
        delete[]arr; 
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
    T* newArr = new T[capacity];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[]arr;
    arr = newArr;
}
#endif