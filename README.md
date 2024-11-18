# MyStl-Project

用学过的数据结构的知识来还原40%+的C++ STL的功能

## `stack<T>`栈容器 

- 2024.9.14 `MyStl::stack<T>`容器完成实现
- 2024.9.15 `MyStl::stack<T>::iterator`迭代器完成实现

### 基准测试

**在Apple Silicon M2, Macbook Air 13, 16G RAM+512G SSD测试机上运行`make stackbench`**

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

## `vector<T>`动态数组容器

- 2024.9.18 进一步抽象`SeqList<T>`，嵌入通用迭代器定义
- 2024.9.21 `MyStl::vector<T>`容器完成实现与基准测试

### 基准测试

**在Apple Silicon M2, Macbook Air 13, 16G RAM+512G SSD测试机上运行`make vectorbench`**

得到基准测评结果：

^(1)^:M代表1000000数量级

| 测试项目                      | `MyStl::vector<int>` | `std::vector<int>` |
| ----------------------------- | -------------------- | ------------------ |
| 向动态数组中追加1M^(1)^个元素 | 4682us               | 51649us            |
| 1M个数据的随机读取            | 3087us               | 2913us             |
| 检查动态数组大小与容量        | 0us                  | 0us                |
| 为动态数组预留至少2M的容量    | 1370us               | 13997us            |
| 向动态数组的头部插入100个元素 | 94246us              | 8924us             |
| 删除动态数组头部的100个元素   | 1201us               | 79us               |
| 动态数组尾部弹出1M个元素      | 2053us               | 10683us            |
| 交换两个动态数组              | 0us                  | 0us                |
| 缩减动态数组容量              | 0us                  | 0us                |

> Benchmarking `MyStl::vector`...
> MyStl::vector push_back 1M elements took 4682 microseconds
> MyStl::vector random access took 3087 microseconds
> MyStl::vector size and capacity check took 0 microseconds
> MyStl::vector reserve to 2M capacity took 1370 microseconds
> MyStl::vector insert 100 elements at the beginning took 94246 microseconds
> MyStl::vector erase first 100 elements took 1201 microseconds
> MyStl::vector pop_back 1M elements took 2053 microseconds
> MyStl::vector swap with another vector took 0 microseconds
> MyStl::vector shrink_to_fit took 0 microseconds
> All MyStl::vector tests passed.

> Benchmarking `std::vector`...
> std::vector push_back 1M elements took 51649 microseconds
> std::vector random access took 2913 microseconds
> std::vector size and capacity check took 0 microseconds
> std::vector reserve to 2M capacity took 13997 microseconds
> std::vector insert 100 elements at the beginning took 8924 microseconds
> std::vector erase first 100 elements took 79 microseconds
> std::vector pop_back 1M elements took 10683 microseconds
> std::vector swap with another vector took 0 microseconds
> std::vector shrink_to_fit took 0 microseconds
> All std::vector tests passed.

## `string`字符串容器

- 2024.9.30 `string`容器完成实现与基准测试
- 2024.10.28 `MyStl::string::find`函数重构，修复错误

### 基准测试

**在Apple Silicon M2, Macbook Air 13, 16G RAM+512G SSD测试机上运行`make vectorbench`**

得到基准测评结果：

^(1)^:M代表1000000数量级

| 测试项目                  | `MyStl::string` | `std::string` |
| ------------------------- | --------------- | ------------- |
| 向字符串追加1M^(1)^个'b'  | 1833us          | 974us         |
| 从字符串中提取100万个字符 | 1575us          | 32us          |
| 在字符串中找'bbbbbb'子串  | 51816us             | 432us         |

> MyStl::string benchmark:
> Running large data set tests for MyStl::string...
> Append 1 million 'b's to MyStl::string took 1833 microseconds
> Substring operation on MyStl::string (extract 1 million characters) took 1575 microseconds
> Find substring 'bbbbbb' in MyStl::string took 0 microseconds
> All large data set tests passed for MyStl::string.

> std::string benchmark
> Running large data set tests for std::string...
> Append 1 million 'b's to std::string took 974 microseconds
> Substring operation on std::string (extract 1 million characters) took 32 microseconds
> Find substring 'bbbbbb' in std::string took 432 microseconds
> All large data set tests passed for std::string.

### 测试分析

在绝大多数项目中被标准库实现超越

## `pair<T1, T2>`元组容器

- 2024.11.4 `MyStl::pair<T1, T2>`容器完成实现

## `map<K, V>`映射容器

- 2024.11.14 `MyStl::map<K, V>`容器完成部分实现（不包含迭代器）
- 2024.11.18 `MyStl::map<K, V>`容器通过基准测试

### 基准测试

**在Apple Silicon M2, Macbook Air 13, 16G RAM+512G SSD测试机上运行`make mapbench`**

得到基准测评结果：

| 测试项目                    | `MyStl::map<int, int>` | `std::map<int, int>` |
| --------------------------- | ---------------------- | -------------------- |
| 向映射容器中插入10000个元素 | 6622us                 | 11836us              |
| 在映射容器中查找元素        | 3452us                 | 4100us               |
| 从容器中删除5000个元素      | 1165us                 | 2141us               |
| 检查剩余的元素              | 1532us                 | 1666us               |
| 深拷贝                      | 127us                  | 2723us               |
| 交换两个容器内容            | 0                      | 0                    |

> MyStl::map<int, int> benchmark:
> Running functionality tests with assertions...
> Insert 10000 elements took 6622 microseconds
> Find elements took 3452 microseconds
> Erase 5000 elements took 1165 microseconds
> Check remaining elements took 1532 microseconds
> Copy map (deep copy) took 127 microseconds
> Swap two maps took 0 microseconds
> All functionality tests passed with assertions.

> std::map<int, int> benchmark:
> Running functionality tests with assertions...
> Insert 10000 elements took 11836 microseconds
> Find elements took 4100 microseconds
> Erase 5000 elements took 2141 microseconds
> Check remaining elements took 1666 microseconds
> Copy map (deep copy) took 2723 microseconds
> Swap two maps took 0 microseconds
> All functionality tests passed with assertions.

