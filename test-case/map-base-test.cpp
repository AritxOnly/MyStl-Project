#include <iostream>
#include <chrono>
#include <cassert>
#include "../map.h"  // 包含您自己的 map 类的头文件
#include <map>

using std::cout, std::string, std::endl;
using MyStl::map;

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
    void testMapFunctionality() {
        // 创建一个 map
        map<int, int> m1;
        
        // 测试基本操作：insert, at, operator[], erase
        cout << "Running functionality tests with assertions...\n";
        
        // 测试插入操作
        benchmark("Insert 10000 elements", [&]() {
            for (int i = 0; i < 10000; i++) {
                m1.insert(MyStl::pair<int, int>(i, i));
            }
        });
        
        // 断言检查 map 的大小和元素是否正确
        assert(m1.size() == 10000 && "Map size should be 10000 after inserting 10000 elements.");
        assert(m1.at(9999) == 9999 && "Element with key 9999 should have value 9999.");
        
        // 测试 operator[]
        m1[10000] = 10000;
        assert(m1.at(10000) == 10000 && "Element with key 10000 should have value 10000.");
        
        // 测试查找操作
        benchmark("Find elements", [&]() {
            for (int i = 0; i < 10000; i++) {
                int value = m1.at(i);
                assert(value == i && "Element value should match its key.");
            }
        });
        
        // 测试删除操作
        benchmark("Erase 5000 elements", [&]() {
            for (int i = 0; i < 5000; i++) {
                m1.erase(i);
            }
        });
        assert(m1.size() == 5001 && "Map size should be 5001 after erasing 5000 elements.");
        
        // 测试剩余元素
        benchmark("Check remaining elements", [&]() {
            for (int i = 5000; i <= 10000; i++) {
                int value = m1.at(i);
                assert(value == i && "Remaining element value should match its key.");
            }
        });
        
        // 测试 map 的深拷贝
        map<int, int> m2;
        benchmark("Copy map (deep copy)", [&]() {
            m2 = m1;
        });
        assert(m2.size() == m1.size() && "Copied map should have the same size.");
        assert(m2.at(10000) == 10000 && "Copied map should contain the same elements.");
        
        // 测试 swap 操作
        map<int, int> m3;
        benchmark("Swap two maps", [&]() {
            m1.swap(m3);
        });
        assert(m1.empty() && "After swap, m1 should be empty.");
        assert(m3.size() == 5001 && "After swap, m3 should have size 5001.");
        
        cout << "All functionality tests passed with assertions.\n";
    }
}

namespace Std {
    void testMapFunctionality() {
        // 创建一个 std::map
        std::map<int, int> m1;
        
        // 测试基本操作：insert, at, operator[], erase
        cout << "Running functionality tests with assertions...\n";
        
        // 测试插入操作
        benchmark("Insert 10000 elements", [&]() {
            for (int i = 0; i < 10000; i++) {
                m1.insert(std::pair<int, int>(i, i));
            }
        });
        
        // 断言检查 map 的大小和元素是否正确
        assert(m1.size() == 10000 && "Map size should be 10000 after inserting 10000 elements.");
        assert(m1.at(9999) == 9999 && "Element with key 9999 should have value 9999.");
        
        // 测试 operator[]
        m1[10000] = 10000;
        assert(m1.at(10000) == 10000 && "Element with key 10000 should have value 10000.");
        
        // 测试查找操作
        benchmark("Find elements", [&]() {
            for (int i = 0; i < 10000; i++) {
                int value = m1.at(i);
                assert(value == i && "Element value should match its key.");
            }
        });
        
        // 测试删除操作
        benchmark("Erase 5000 elements", [&]() {
            for (int i = 0; i < 5000; i++) {
                m1.erase(i);
            }
        });
        assert(m1.size() == 5001 && "Map size should be 5001 after erasing 5000 elements.");
        
        // 测试剩余元素
        benchmark("Check remaining elements", [&]() {
            for (int i = 5000; i <= 10000; i++) {
                int value = m1.at(i);
                assert(value == i && "Remaining element value should match its key.");
            }
        });
        
        // 测试 map 的深拷贝
        std::map<int, int> m2;
        benchmark("Copy map (deep copy)", [&]() {
            m2 = m1;
        });
        assert(m2.size() == m1.size() && "Copied map should have the same size.");
        assert(m2.at(10000) == 10000 && "Copied map should contain the same elements.");
        
        // 测试 swap 操作
        std::map<int, int> m3;
        benchmark("Swap two maps", [&]() {
            m1.swap(m3);
        });
        assert(m1.empty() && "After swap, m1 should be empty.");
        assert(m3.size() == 5001 && "After swap, m3 should have size 5001.");
        
        cout << "All functionality tests passed with assertions.\n";
    }
}

int main() {
    // 测试 std::map 的功能和性能
    cout << "std::map<int, int> benchmark:\n";
    Std::testMapFunctionality();

    // 测试 MyStl::map 的功能和性能
    cout << "MyStl::map<int, int> benchmark:\n";
    MyStl::testMapFunctionality();
    
    return 0;
}