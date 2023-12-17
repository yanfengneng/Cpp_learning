#include <iostream>
using namespace std;

// class Base 
// {
// public:
// 	virtual void func() {
// 		cout << "Base func\n";
// 	}
// };

// class Son : public Base
// {
// public:
// 	void func() {
// 		Base::func();
// 		cout << "Son func\n";
// 	}
// };

class BV
{
public:
    virtual void Fun1()
    {
        cout << "BV->Fun1()" << endl;
    }
    virtual void Fun2()
    {
        cout << "BV->Fun2()" << endl;
    }
};

class DV : public BV
{
public:
    virtual void Fun1()
    {
        cout << "DV->Fun1()" << endl;
    }
    virtual void Fun3()
    {
        cout << "DV->Fun3()" << endl;
    }
    virtual void Fun4()
    {
        cout << "DV->Fun4()" << endl;
    }
};

typedef void (BV::*V_PTR)(); // 使用成员函数指针类型

void PrintPFTable(BV* obj, V_PTR* table)
{
    for (size_t i = 0; table[i] != nullptr; ++i)
    {
        cout << "table[" << i << "] : ";
        (obj->*table[i])(); // 调用成员函数
        cout << endl;
    }
}

int main()
{
    BV b;
    DV d;

    PrintPFTable(&b, reinterpret_cast<V_PTR*>(*(int*)&b)); // 传入有效的对象指针
    PrintPFTable(&d, reinterpret_cast<V_PTR*>(*(int*)&d));

    return 0;
}