#include <iostream>
#include <vector>
#include <cassert>
#include "../vector.h" // 包含你自定义的 MyStl::vector

template <typename Func>
void benchmark(const std::string& operation, Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << operation << " took " << duration << " microseconds" << std::endl;
}

// 测试 MyStl::vector 的性能和功能
void testMyStlVector() {
    MyStl::vector<int> myVector;

    // 测试 push_back
    benchmark("MyStl::vector push_back 1M elements", [&]() {
        for (int i = 0; i < 1000000; ++i) {
            myVector.push_back(i);
        }
    });

    // 测试访问元素并确保数据正确性
    benchmark("MyStl::vector random access", [&]() {
        for (int i = 0; i < 1000000; ++i) {
            assert(myVector[i] == i); // 验证每个元素是否正确
        }
    });

    // 测试 size 和 capacity
    benchmark("MyStl::vector size and capacity check", [&]() {
        assert(myVector.get_size() == 1000000);
        assert(myVector.get_capacity() >= 1000000);
    });

    // 测试 reserve
    benchmark("MyStl::vector reserve to 2M capacity", [&]() {
        myVector.reserve(2000000);
        assert(myVector.get_capacity() >= 2000000);
    });

    // 测试 insert
    benchmark("MyStl::vector insert 100 elements at the beginning", [&]() {
        for (int i = 0; i < 100; ++i) {
            myVector.insert(myVector.begin(), i);
        }
    });
    assert(myVector[0] == 99);

    // 测试 erase
    benchmark("MyStl::vector erase first 100 elements", [&]() {
        myVector.erase(myVector.begin(), myVector.begin() + 100);
    });
    assert(myVector[0] == 0);

    // 测试 pop_back
    benchmark("MyStl::vector pop_back 1M elements", [&]() {
        for (int i = 0; i < 1000000; ++i) {
            myVector.pop_back();
        }
    });
    assert(myVector.get_size() == 0);

    // 测试 swap
    MyStl::vector<int> otherVector(10, 5); // 初始化容量为 10、每个元素为 5
    benchmark("MyStl::vector swap with another vector", [&]() {
        myVector.swap(otherVector);
    });
    assert(myVector.get_size() == 10 && myVector[0] == 5);


    // 测试 shrink_to_fit
    myVector.reserve(1000);
    benchmark("MyStl::vector shrink_to_fit", [&]() {
        myVector.shrink_to_fit();
    });
    assert(myVector.get_capacity() >= myVector.get_size());

    std::cout << "All MyStl::vector tests passed.\n";
}

// 测试 std::vector 的性能和功能
void testStdVector() {
    std::vector<int> stdVector;

    // 测试 push_back
    benchmark("std::vector push_back 1M elements", [&]() {
        for (int i = 0; i < 1000000; ++i) {
            stdVector.push_back(i);
        }
    });

    // 测试访问元素并确保数据正确性
    benchmark("std::vector random access", [&]() {
        for (int i = 0; i < 1000000; ++i) {
            assert(stdVector[i] == i); // 验证每个元素是否正确
        }
    });

    // 测试 size 和 capacity
    benchmark("std::vector size and capacity check", [&]() {
        assert(stdVector.size() == 1000000);
        assert(stdVector.capacity() >= 1000000);
    });

    // 测试 reserve
    benchmark("std::vector reserve to 2M capacity", [&]() {
        stdVector.reserve(2000000);
        assert(stdVector.capacity() >= 2000000);
    });

    // 测试 insert
    benchmark("std::vector insert 100 elements at the beginning", [&]() {
        for (int i = 0; i < 100; ++i) {
            stdVector.insert(stdVector.begin(), i);
        }
    });
    assert(stdVector[0] == 99);

    // 测试 erase
    benchmark("std::vector erase first 100 elements", [&]() {
        stdVector.erase(stdVector.begin(), stdVector.begin() + 100);
    });
    assert(stdVector[0] == 0);

    // 测试 pop_back
    benchmark("std::vector pop_back 1M elements", [&]() {
        for (int i = 0; i < 1000000; ++i) {
            stdVector.pop_back();
        }
    });
    assert(stdVector.size() == 0);

    // 测试 swap
    std::vector<int> otherVector(10, 5);
    benchmark("std::vector swap with another vector", [&]() {
        stdVector.swap(otherVector);
    });
    assert(stdVector.size() == 10 && stdVector[0] == 5);

    // 测试 shrink_to_fit
    stdVector.reserve(1000);
    benchmark("std::vector shrink_to_fit", [&]() {
        stdVector.shrink_to_fit();
    });
    assert(stdVector.capacity() >= stdVector.size());

    std::cout << "All std::vector tests passed.\n";
}

int main() {

    std::cout << "Benchmarking std::vector..." << std::endl;
    testStdVector();

    std::cout << "Benchmarking MyStl::vector..." << std::endl;
    testMyStlVector();

    return 0;
}