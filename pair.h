#ifndef __PAIR_H__
#define __PAIR_H__

namespace MyStl {
    template<class _TpX, class _TpY>
    class pair {
    public:
        using X = _TpX;
        using Y = _TpY;
        X first;
        Y second;

        // 构造函数
        pair() : first(X()), second(Y()) {}
        pair(const pair& other) : first(other.first), second(other.second) {}
        pair(pair&& other) : first(other.first), second(other.second) {}
        pair(X x, Y y) : first(x), second(y) {}
        ~pair() = default;

        pair& operator=(const pair& other);
        pair& operator=(pair&& other);

        bool operator==(const pair& other) const;
        bool operator!=(const pair& other) const;
        bool operator<(const pair& other) const;
        bool operator<=(const pair& other) const;
        bool operator>(const pair& other) const;
        bool operator>=(const pair& other) const;
    };

    template<class T1, class T2>
    pair<T1, T2>& pair<T1, T2>::operator=(const pair<T1, T2>& other) {
        return pair<T1, T2>(other.first, other.second);
    }

    template<class T1, class T2>
    pair<T1, T2>& pair<T1, T2>::operator=(pair<T1, T2>&& other) {
        // 疑问：是否可以这么写移动语义？
        return pair<T1, T2>(other.first, other.second);
    }

    template<class T1, class T2>
    bool pair<T1, T2>::operator==(const pair<T1, T2>& other) const {
        return first == other.first && second == other.second;
    }

    template<class T1, class T2>
    bool pair<T1, T2>::operator!=(const pair<T1, T2>& other) const {
        return first!= other.first || second != other.second;
    }

    template<class T1, class T2>
    bool pair<T1, T2>::operator<(const pair<T1, T2>& other) const {
        return first < other.first || (first == other.first && second < other.second);
    }

    template<class T1, class T2>
    bool pair<T1, T2>::operator<=(const pair<T1, T2>& other) const {
        return first < other.first || (first == other.first && second <= other.second);
    }

    template<class T1, class T2>
    bool pair<T1, T2>::operator>(const pair<T1, T2>& other) const {
        return first > other.first || (first == other.first && second > other.second);
    }

    template<class T1, class T2>
    bool pair<T1, T2>::operator>=(const pair<T1, T2>& other) const {
        return first > other.first || (first == other.first && second >= other.second);
    }
}

#endif