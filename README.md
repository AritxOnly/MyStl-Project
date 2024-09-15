# MyStl-Project

用学过的数据结构的知识来还原40%+的C++ STL的功能

## `stack<T>`栈容器 

- 2024.9.14 `MyStl::stack<T>`容器完成实现
- 2024.9.15 `MyStl::stack<T>::iterator`迭代器完成实现

### 基准测试

**在Apple Silicon M2, Macbook Air 13, 16G RAM+512 SSD测试机上运行`make stackbench`**

得到基准测评结果：

| 测试项目                      | `MyStl::stack<int>` | `std::stack<int>` |
| ----------------------------- | ------------------- | ----------------- |
| 向栈中push 10000个元素        | 184us               | 1481us            |
| 迭代器遍历整个栈              | 308us               | /                 |
| 出栈后再往栈中push 5000个元素 | 119us               | 744us             |
| 深拷贝（从栈s1拷贝到s2）      | 81us                | 320us             |
| 两个栈相加                    | 380us               | /                 |
| 栈重复3次                     | 564us               | /                 |
| 交换两个栈                    | 0us                 | 0us               |

> `MyStl::stack<int> `benchmark:<br>
Running functionality tests with assertions...<br>
Push 10000 elements took 184 microseconds<br>
Push 5000 elements after pop took 119 microseconds<br>
Copy stack (deep copy) took 81 microseconds<br>
Add two stacks took 390 microseconds<br>
Multiply stack by 3 took 564 microseconds<br>
Swap two stacks took 0 microseconds<br>
All functionality tests passed with assertions.<br>

> `std::stack<int>` benchmark<br>
Running functionality tests with assertions...<br>
Push 10000 elements took 1481 microseconds<br>
Push 5000 elements after pop took 744 microseconds<br>
Copy stack (deep copy) took 320 microseconds<br>
Not valid<br>
Add two stacks took 2 microseconds<br>
Not valid<br>
Multiply stack by 3 took 0 microseconds<br>
Swap two stacks took 0 microseconds<br>
All functionality tests passed with assertions.<br>