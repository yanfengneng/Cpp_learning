#include <string>
#include <iostream>
using namespace std;

// int globalval = 20;
// int& foo()
// { 
//     return globalval; 
// }

class A
{
public:
    void foo() const { cout << "A::foo() const\n"; }
    void foo() { cout << "A::foo()\n"; }
};

A bar(){ return A(); }
const A cbar() { return A(); }

class Intvec
{
public:
    explicit Intvec(size_t num = 0)
        : m_size(num), m_data(new int[m_size])
    {
        log("constructor");
    }

    ~Intvec()
    {
        log("destructor");
        if (m_data) {
            delete[] m_data;
            m_data = 0;
        }
    }

    Intvec(const Intvec& other)
        : m_size(other.m_size), m_data(new int[m_size])
    {
        log("copy constructor");
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = other.m_data[i];
    }

    Intvec& operator=(const Intvec& other)
    {
        log("copy assignment operator");
        Intvec tmp(other);
        std::swap(m_size, tmp.m_size);
        std::swap(m_data, tmp.m_data);
        return *this;
    }

    Intvec& operator=(Intvec&& other)
    {
        log("move assignment operator");
        std::swap(m_size, other.m_size);
        std::swap(m_data, other.m_data);
        return *this;
    }
private:
    void log(const char* msg)
    {
        cout << "[" << this << "] " << msg << "\n";
    }

    size_t m_size;
    int* m_data;
};

// 形参是个右值引用
void change(int&& right_value) {
    right_value = 8;
}

void f(const int& n) {
    n += 1; // 编译失败，const左值引用不能修改指向变量
}

void f2(int && n) {
    n += 1; // ok
}

int main()
{
    // f(5);
    // f2(5);
    // foo() = 10;
    // std::string & sref = std::string();
    // bar().foo();
    // cbar().foo();

    // Intvec v1(20);
    // Intvec v2;
    // cout << "assigning lvalue...\n";
    // v2 = v1;
    // cout << "ended assigned lvalue...\n";

    // cout << "assigning rvalue...\n";
    // v2 = Intvec(33);
    // cout << "ended assigning rvalue...\n";

    // int &&ref_a_right = 5;	// ok

    // int a = 5;

    // // int &&ref_a_left = a; // 编译不过，右值引用不可以指向左值

    // ref_a_right = 6;// 右值引用的用途：可以修改右值
    // int a = 5; // a是个左值
    // int &ref_a_left = a; // 左值引用指向左值
    // int &&ref_a_right = std::move(a); // 通过std::move将左值转化为右值，可以被右值引用指向
    
    // int &&b = static_cast<int&&> (a);
    // cout << b << endl;
    // cout << a << endl; // 打印结果：5
    // int a = 5; // a是个左值
    // int &ref_a_left = a; // ref_a_left是个左值引用
    // int &&ref_a_right = std::move(a); // ref_a_right是个右值引用
 
    // // change(a); // 编译不过，a是左值，change参数要求右值
    // // change(ref_a_left); // 编译不过，左值引用ref_a_left本身也是个左值
    // // change(ref_a_right); // 编译不过，右值引用ref_a_right本身也是个左值
     
    // change(std::move(a)); // 编译通过
    // change(std::move(ref_a_right)); // 编译通过
    // change(std::move(ref_a_left)); // 编译通过
 
    // change(5); // 当然可以直接接右值，编译通过
     
    // cout << &a << ' ';
    // cout << &ref_a_left << ' ';
    // cout << &ref_a_right;
    // 打印这三个左值的地址，都是一样的
    return 0;
}