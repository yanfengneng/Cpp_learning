#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

class MyClass {
public:
    // 默认构造函数
    MyClass() {
        std::cout << "Default constructor called" << std::endl;
        data = new int(0);
    }

    // 拷贝构造函数
    MyClass(const MyClass& other) {
        std::cout << "Copy constructor called" << std::endl;
        data = new int(*(other.data));
    }

    // 拷贝赋值运算符函数
    MyClass& operator=(const MyClass& other) {
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &other) {
            delete data;  // 避免内存泄漏
            data = new int(*(other.data));
        }
        return *this;
    }

    // 移动构造函数：将右值的值清空
    MyClass(MyClass&& other) noexcept {
        std::cout << "Move constructor called" << std::endl;
        data = other.data;
        other.data = nullptr;
    }

    // 移动赋值运算符函数：将右值的值清空
    MyClass& operator=(MyClass&& other) noexcept {
        std::cout << "Move assignment operator called" << std::endl;
        if (this != &other) {
            delete data;  // 避免内存泄漏
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    // 析构函数
    ~MyClass() {
        std::cout << "Destructor called" << std::endl;
        delete data;
    }

private:
    int* data;
};

void B(int&& ref_r) {
    ref_r = 1;
}
 
// A、B的入参是右值引用
// 有名字的右值引用是左值，因此ref_r是左值
void A(int&& ref_r) {
    B(ref_r);  // 错误，B的入参是右值引用，需要接右值，ref_r是左值，编译失败
     
    B(std::move(ref_r)); // ok，std::move把左值转为右值，编译通过
    B(std::forward<int>(ref_r));  // ok，std::forward的T是int类型，属于条件b，因此会把ref_r转为右值
}

int main()
{
    int a = 5;
    A(std::move(a));
    // // 创建对象并测试构造函数和赋值运算符
    // MyClass obj1;              // 默认构造函数
    // MyClass obj2 = obj1;       // 对象初始化调用的是拷贝构造函数
    // MyClass obj3;
    // obj3 = obj1;               // 拷贝赋值运算符

    // // 移动构造函数和移动赋值运算符的测试
    // MyClass obj4 = std::move(obj1);  // 对象初始化调用的移动构造函数
    // MyClass obj5;
    // obj5 = std::move(obj2);         // 对象的赋值调用的是移动赋值运算符

    // // 析构函数的调用
    // // 注意：在程序结束时，局部对象将被销毁，析构函数将被调用

    // std::string str1 = "aacasxs";
    // std::vector<std::string> vec;
     
    // vec.push_back(str1); // 传统方法，copy
    // vec.push_back(std::move(str1)); // 调用移动语义的 push_back 方法，避免拷贝，str1会失去原有值，变成空字符串
    // cout << str1 << endl;
    // vec.emplace_back(std::move(str1)); // emplace_back效果相同，str1会失去原有值
    // cout << str1 << endl;
    // vec.emplace_back("axcsddcas"); // 当然可以直接接右值
    return 0;
}