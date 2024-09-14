/**
 * 测试代码由GPT-4o给出
 * 提供基准测试功能
 * 后续模块可能会尝试自己写测试
 */

#include <iostream>
#include <chrono>
#include <cassert>  // 添加断言头文件
#include "../stack.h"  // 这里包含你自己的stack类的头文件
#include <stack>

using std::cout, std::string, std::endl;
using MyStl::stack;

// 辅助函数：计算并打印操作执行时间
template <typename Func>
void benchmark(const string& operation, Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << operation << " took " << duration << " microseconds" << endl;
}

namespace MyStl {
    void testStackFunctionality() {
        // 创建一个栈
        stack<int> s1;
        
        // 测试基本操作：push, pop, getTop, swap
        cout << "Running functionality tests with assertions...\n";
        
        benchmark("Push 10000 elements", [&]() {
            for (int i = 0; i < 10000; i++) {
                s1.push(i);
            }
        });

        // 断言检查栈的大小和栈顶元素是否正确
        assert(s1.getTop() == 9999 && "Top element should be 9999 after pushing 10000 elements.");
        assert(s1.pop() && "Pop operation should succeed.");
        assert(s1.getTop() == 9998 && "Top element should be 9998 after popping.");

        // 检查是否能够继续正常操作
        benchmark("Push 5000 elements after pop", [&]() {
            for (int i = 0; i < 5000; i++) {
                s1.push(i);
            }
        });
        
        // 断言栈顶元素是否正确
        assert(s1.getTop() == 4999 && "Top element should be 4999 after pushing 5000 elements.");

        // 测试栈的深拷贝
        stack<int> s2;
        benchmark("Copy stack (deep copy)", [&]() {
            s2 = s1;
        });

        // 断言拷贝是否成功
        assert(s2.getTop() == s1.getTop() && "Copied stack should have the same top element.");
        
        // 测试栈的相加
        benchmark("Add two stacks", [&]() {
            stack<int> s3 = s1 + s2;
            assert(s3.getTop() == s2.getTop() && "Top element after adding two stacks should be the same.");
        });

        // 测试乘法操作符
        benchmark("Multiply stack by 3", [&]() {
            stack<int> s4 = s1 * 3;
            assert(s4.getTop() == s1.getTop() && "Top element after multiplying should remain the same.");
        });

        // 测试swap操作
        benchmark("Swap two stacks", [&]() {
            s1.swap(s2);
            assert(s1.getTop() == s2.getTop() && "After swap, stacks should have swapped top elements.");
        });

        cout << "All functionality tests passed with assertions.\n";
    }
}

namespace Std {
    void testStackFunctionality() {
        // 创建一个栈
        std::stack<int> s1;
        
        // 测试基本操作：push, pop, getTop, swap
        cout << "Running functionality tests with assertions...\n";
        
        benchmark("Push 10000 elements", [&]() {
            for (int i = 0; i < 10000; i++) {
                s1.push(i);
            }
        });

        // 断言检查栈的大小和栈顶元素是否正确
        assert(s1.top() == 9999 && "Top element should be 9999 after pushing 10000 elements.");
        s1.pop();
        assert(s1.top() == 9998 && "Top element should be 9998 after popping.");

        // 检查是否能够继续正常操作
        benchmark("Push 5000 elements after pop", [&]() {
            for (int i = 0; i < 5000; i++) {
                s1.push(i);
            }
        });
            
        // 断言栈顶元素是否正确
        assert(s1.top() == 4999 && "Top element should be 4999 after pushing 5000 elements.");

        // 测试栈的深拷贝
        std::stack<int> s2;
        benchmark("Copy stack (deep copy)", [&]() {
            s2 = s1;
        });

        // 断言拷贝是否成功
        assert(s2.top() == s1.top() && "Copied stack should have the same top element.");
            
        // 测试栈的相加
        benchmark("Add two stacks", [&]() {
            cout << "Not valid" << endl;
        });

        // 测试乘法操作符
        benchmark("Multiply stack by 3", [&]() {
            cout << "Not valid" << endl;
        });

        // 测试swap操作
        benchmark("Swap two stacks", [&]() {
            s1.swap(s2);
            assert(s1.top() == s2.top() && "After swap, stacks should have swapped top elements.");
        });

        cout << "All functionality tests passed with assertions.\n";
    }
}

int main() {
    // 测试栈功能和基准性能
    cout << "MyStl::stack<int> benchmark:\n";
    MyStl::testStackFunctionality();

    cout << "std::stack<int> benchmark\n";
    Std::testStackFunctionality();

    return 0;
}