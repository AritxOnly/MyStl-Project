#ifndef __STRING_H__
#define __STRING_H__

#include "abstract-data-structure/seqlist.h"
#include <cstring>
#include <stdexcept>

template<class T>
class SeqList;

namespace MyStl {
    class string : SeqList<char> {
    public:
        string();
        string(const int _size);
        string(const int _size, const char _value);
        string(const char* _str);
        string(const string& other);
        ~string() = default;

        const int length() const;
        const char* to_cstr() const;
        bool empty() const;

        string operator()(const int _pos, const int _len);
        bool operator==(const string& other) const;
        bool operator!=(const string& other) const;
        bool operator!() const;
        char operator[](const int index);
        string operator+(const string& other);
        string& operator=(const string& other);
        string& operator+=(const char _ch);
        string& operator+=(const char* _str);
        string& operator+=(const string& other);

        /** 
         * ABSTRACT SEQLIST ITERATOR
         * INCLUDE FUNCTION OF DEREFERENCE, ++, != AND ==
         */
        using typename SeqList<char>::iterator;

        iterator find(const char* pat);
        iterator find(const string& _str);
        iterator begin();
        iterator back();
        iterator end();

        // 引用seqlist抽象对象的成员变量
        using SeqList<char>::arr;
        using SeqList<char>::size;
        using SeqList<char>::capacity;
    };

    inline string::string() : SeqList<char>() {}

    inline string::string(const int _size) : SeqList<char>() {
        while (_size > capacity) {
            this->expand();
        }
        size = _size;
    }

    inline string::string(const int _size, const char _value) : SeqList<char>() {
        while (_size + 1 > capacity) {
            this->expand();
        }
        size = _size + 1;
        for (int i = 0; i < _size; i++) {
            arr[i] = _value;
        }
        arr[_size] = '\0';
    }
    
    inline string::string(const char* _str) : SeqList<char>() {
        int len = strlen(_str);
        while (len + 1 > capacity) {
            this->expand();
        }
        size = len + 1;
        strncpy(arr, _str, len);
        arr[len] = '\0';    // 尾部插0
    }

    inline string::string(const string& other) : SeqList<char>() {
        capacity = other.capacity;
        size = other.size;
        arr = new char[capacity];
        strncpy(arr, other.arr, size);
    }

    inline const int string::length() const{
        return size - 1;
    }

    inline const char* string::to_cstr() const {
        return arr;
    }

    inline bool string::empty() const {
        return length() == 0;
    }

    inline string string::operator()(const int _pos, const int _len) {
        if (_pos < 0 || _pos >= size - 1 || _len < 0) {
            throw std::out_of_range("Invalid position or length");
        }
        // 串选择
        int len = (_pos + _len >= size) ? (size - _pos - 1) : _len;
        string tmp(len + 1);
        for (int i = 0; i < len; i++) {
            tmp.arr[i] = arr[i + _pos];
        }
        tmp.arr[len] = '\0';
        tmp.size = len + 1;
        return tmp;
    }

    inline bool string::operator!() const {
        return empty();
    }

    inline char string::operator[](const int index) {
        if (index < 0 || index >= length()) {
            throw std::out_of_range("Invalid index");
        }
        return arr[index];
    }

    inline bool string::operator==(const string& other) const {
        return (size == other.size) && (strncmp(arr, other.arr, size) == 0);
    }

    inline bool string::operator!=(const string& other) const {
        return !(*this == other);
    }

    inline string string::operator+(const string& other) {
        string str = *this;
        str += other;
        return str;
    }

    inline string& string::operator=(const string& other) {
        if (arr != other.arr) {
            if (arr != nullptr) {
                delete[]arr;
            }
            size = other.size;
            capacity = other.capacity;
            arr = new char[capacity];
            strncpy(arr, other.arr, size);
        }
        return *this;
    }

    inline string& string::operator+=(const char _ch) {
        while (size + 2 > capacity) {
            this->expand();
        }
        arr[size++] = _ch;
        arr[size] = '\0';
        return *this;
    }

    inline string& string::operator+=(const char* _str) {
        int len = strlen(_str);
        while (size + len + 1 > capacity) {
            this->expand();
        }
        strcat(arr, _str);
        size += len;
        arr[size] = '\0';
        return *this;
    }

    inline string& string::operator+=(const string& other) {
        *this += other.arr;
        return *this;        
    }

    inline string::iterator string::find(const char* pat) {
        // 用KMP算法匹配字符串
        int len = strlen(pat);
        int* next = new int[len];
        auto get_next = [&]() {
            int j = 0, k = -1;
            next[0] = -1;
            j = 1;
            while (j < len) {
                k = next[j - 1];
                while (true) {
                    if (k == -1 || pat[j - 1] == pat[k] || pat[j - 1] == '*' || pat[k] == '*') {
                        k++;
                        next[j] = k;
                        j++;
                        break;
                    }
                    k = next[k];
                }
            }
        };
        get_next();
        int p = 0, t = 0;
        while (p < len && t < size) {
            if (p == -1 || pat[p] == arr[t] || pat[p] == '*') {
                p++;
                t++;
            } else {
                p = next[p];
            }
        }
        if (p < len)
            return string::iterator(-1, size, arr);
        return string::iterator(t - len, size, arr);
    }

    inline string::iterator string::find(const string& _str) {
        return find(_str.to_cstr());
    }

    inline string::iterator string::begin() {
        return string::iterator(0, size, arr);
    }

    inline string::iterator string::back() {
        return string::iterator(size - 1, size, arr);
    }

    inline string::iterator string::end() {
        return string::iterator(size, size, arr);
    }
}

#endif