#ifndef __STACK_H__
#define __STACK_H__

#include "abstract-data-structure/seqlist.h"
#include <cassert>
#include <concepts>
#include <exception>
#include <stdexcept>
#include <utility>
#include <ostream>

template<class T>
class SeqList;

template<class T>
concept Printable = requires(T x, std::ostream& out) {
    { out << x } -> std::same_as<std::ostream&>;
};

namespace MyStl {
    // 顺序栈
    template<class T>
    class stack : public SeqList<T> {
    public:
        // 构造与析构
        stack();
        stack(const int _size);
        stack(const int _size, const T& _value);
        stack(const stack<T>& other);
        ~stack() = default;

        const T& getTop() const;
        bool pop();
        void push(const T& _value);
        void swap(stack& other);

        // 运算符重载
        stack& operator=(const stack& other);
        T& operator[](int index);
        std::ostream& operator<<(std::ostream& out);
        stack operator+(const stack& other) const;    // 用于合成两个stack
        stack operator*(const int times) const;   // 用于将stack loop拓展times份
        stack& operator+=(const stack& other);
        stack& operator*=(const int time);
        bool operator==(const stack& other);
        bool operator!=(const stack& other);

        // 迭代器类定义
        class iterator {
        public:
            iterator(int _index, int _size, T* _arr) : 
                index(_index), size(_size), arr(_arr) {
                if (index >= size)
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

        private:
            int index = 0;
            int size = 0;
            T* arr = nullptr;
        };

        iterator begin();
        iterator back();
        iterator end();

        // 引用seqlist抽象对象的成员变量
        using SeqList<T>::arr;
        using SeqList<T>::size;
        using SeqList<T>::capacity;
    
    private:
        int top;

        bool isUnequalExist(const stack& other);
    };
}

template<Printable T>
std::ostream& operator<<(std::ostream& out, MyStl::stack<T>& stack) {
    stack.operator<<(out);
    return out;
}

using namespace MyStl;

template<class T>
stack<T>::stack() : SeqList<T>(), top(-1) {
    assert(capacity == 0);  // 断言
}

template<class T>
stack<T>::stack(int _size) : SeqList<T>(), top(_size - 1) {
    if (_size <= 0)
        return;
    capacity = DEFAULT_CAPACITY;
    size = _size;
    while (capacity < _size) {
        capacity *= 2;  // 节省时间的做法，维护性可能略差
    }
    arr = new T[capacity];
}

template<class T>
stack<T>::stack(const int _size, const T& _value) : 
        SeqList<T>(), top(_size - 1) {
    if (_size <= 0)
        return;
    capacity = DEFAULT_CAPACITY;
    size = _size;
    while (capacity < _size) {
        capacity *= 2;  // 节省时间的做法，维护性可能略差
    }
    arr = new T[capacity];
    for (int i = 0; i < _size; i++) {
        arr[i] = _value;
    }
}

template<class T>
stack<T>::stack(const stack<T>& other) {
    // 深拷贝
    capacity = other.capacity;
    size = other.size;
    top = other.top;
    arr = new T[capacity];
    for (int i = 0; i <= top; i++) {
        arr[i] = other.arr[i];
    }
}

template<class T>
const T& stack<T>::getTop() const {
    return arr[top];
}

template<class T>
bool stack<T>::pop() {
    if (size == 0) {
        return false;
    }
    top--;
    size--;
    return true;
}

template<class T>
void stack<T>::push(const T& _value) {
    if (size == capacity)
        this->expand();
    arr[++top] = _value;
    size++;
}

template<class T>
void stack<T>::swap(stack<T>& other) {
    std::swap(arr, other.arr);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(top, other.top);
}

template<class T>
stack<T>& stack<T>::operator=(const stack<T>& other) {
    // 深拷贝
    if (arr != nullptr)
        delete[]arr;
    capacity = other.capacity;
    size = other.size;
    top = other.top;
    arr = new T[capacity];
    for (int i = 0; i <= top; i++) {
        arr[i] = other.arr[i];
    }
    return *this;
}

template<class T>
T& stack<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Stack index out of range");
    }
    return arr[index];
}

template<class T>
std::ostream& stack<T>::operator<<(std::ostream& out) {
    out << "stack bottom ->";
    for (int i = 0; i < size; i++) {
        out << " | " << arr[i];
    }
    out << " -> stack top\n";
    return out;
}

template<class T>
stack<T> stack<T>::operator+(const stack<T>& other) const {
    stack<T> ret(size + other.size);
    for (int i = 0; i < size; i++) {
        ret[i] = arr[i];
    }
    for (int i = 0; i < other.size; i++) {
        ret[i + size] = other.arr[i];
    }
    return ret;
}

template<class T>
stack<T> stack<T>::operator*(const int times) const {
    if (times < 1)
        return stack<T>();  // 返回空对象
    stack<T> ret(size * times);
    for (int iteration = 0; iteration < times; iteration++) {
        for (int i = 0; i < size; i++) {
            ret[size * iteration + i] = arr[i];
        }
    }
    return ret;
}

template<class T>
stack<T>& stack<T>::operator+=(const stack<T>& other) {
    int _size = size + other.size;
    while (_size > capacity) {
        this->expand();
    }
    for (int i = size; i < _size; i++) {
        arr[i] = other.arr[i - size];
    }
    size = _size;
    top = _size - 1;
    return *this;
} 

template<class T>
stack<T>& stack<T>::operator*=(const int times) {
    int _size = size * times;
    while (_size > capacity) {
        this->expand();
    }
    for (int iteration = 1; iteration < times; iteration++) {
        for (int i = 0; i < size; i++) {
            arr[iteration * size + i] = arr[i];
        }
    }
    size = _size;
    top = _size - 1;
    return *this;
}

template<class T>
bool stack<T>::isUnequalExist(const stack<T>& other) {
    if (size != other.size) {
        return true;
    }
    for (int i = 0; i < size; i++) {
        if (arr[i] != other.arr[i])
            return true;
    }
    return false;
}

template<class T>
bool stack<T>::operator==(const stack<T>& other) {
    return (size == other.size) && !isUnequalExist(other);
}

template<class T>
bool stack<T>::operator!=(const stack<T>& other) {
    return !(*this == other);
}

template<class T>
stack<T>::iterator stack<T>::begin() {
    if (size == 0) {
        return stack<T>::iterator(-1, size, arr);
    }
    return stack<T>::iterator(0, size, arr);
}

template<class T>
stack<T>::iterator stack<T>::back() {
    return stack<T>::iterator(top, size, arr);
} 

template<class T>
stack<T>::iterator stack<T>::end() {
    return stack<T>::iterator(-1, size, arr);
}

#endif