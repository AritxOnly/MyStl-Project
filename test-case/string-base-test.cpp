#include <iostream>
#include <chrono>
#include <cassert>  // 添加断言头文件
#include "../string.h"  // 这里包含您自己的 MyStl::string 头文件
#include <string>

using std::cout, std::string, std::endl;

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
    void testStringFunctionality() {
        cout << "Running large data set tests for MyStl::string...\n";
        
        // 创建一个大规模字符串
        MyStl::string s1(10000000, 'a');  // 1千万个字符 'a'
        
        // 测试 += 操作
        benchmark("Append 1 million 'b's to MyStl::string", [&]() {
            MyStl::string s2(1000000, 'b');
            s1 += s2.to_cstr();  // 添加1百万个字符 'b'
        });
        
        // 测试子串操作
        benchmark("Substring operation on MyStl::string (extract 1 million characters)", [&]() {
            MyStl::string s3 = s1(5000000, 1000000);  // 提取100万个字符
            assert(s3.length() == 1000000 && "Substring operation failed.");
        });

        // 测试查找操作
        benchmark("Find substring 'bbbbbb' in MyStl::string", [&]() {
            auto it = s1.find("bbbbbb");
            assert(it != s1.end() && "Substring 'bbbbbb' not found.");
        });

        cout << "All large data set tests passed for MyStl::string.\n";
    }
}

namespace Std {
    void testStringFunctionality() {
        cout << "Running large data set tests for std::string...\n";
        
        // 创建一个大规模字符串
        std::string s1(10000000, 'a');  // 1千万个字符 'a'
        
        // 测试 += 操作
        benchmark("Append 1 million 'b's to std::string", [&]() {
            std::string s2(1000000, 'b');
            s1 += s2;  // 添加1百万个字符 'b'
        });

        // 测试子串操作
        benchmark("Substring operation on std::string (extract 1 million characters)", [&]() {
            std::string s3 = s1.substr(5000000, 1000000);  // 提取100万个字符
            assert(s3.length() == 1000000 && "Substring operation failed.");
        });

        // 测试查找操作
        benchmark("Find substring 'bbbbbb' in std::string", [&]() {
            auto pos = s1.find("bbbbbb");
            assert(pos != std::string::npos && "Substring 'bbbbbb' not found.");
        });

        cout << "All large data set tests passed for std::string.\n";
    }
}

int main() {
    // 测试MyStl::string和std::string功能和基准性能
    cout << "MyStl::string benchmark:\n";
    MyStl::testStringFunctionality();

    cout << "std::string benchmark\n";
    Std::testStringFunctionality();

    return 0;
}