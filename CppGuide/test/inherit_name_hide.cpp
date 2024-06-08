#include <iostream>
using namespace std;

// class A
// {
// protected:
//     int ax;
// public:
//     A() : ax(0) {}
// };

// class B : public A
// {
// private:
//     int ax;
// public:
//     B() : ax(10) {}

//     /* 成员函数 fun 访问时采用就近原则，访问 B 对象中的 ax，隐藏 A 对象中的 ax */
//     void fun(){
//         cout << "before : " << ax << endl;
//         ax = 100;
//         cout << "after : " << ax << endl;
//     }
// };

// class A
// {
// private:
//     int value;
// public:
//     A() : value(10) {}
//     void fun() { cout << "A::fun" << value << endl; }
// };

// class B : public A // 共有继承
// {
// public:
//     void fun() { cout << "B::fun" << endl; }
// };

// class D
// {
// public:
// 	void funcA();				//1
// 	void funcA() const;			//2
// 	void funcB(int a);			//3
// 	void funcB(const int a);	//4
// };
void hidefunc(const char* pstr)
{
	cout << "global function: " << pstr << endl;
}

class HideA
{
public:
	void hidefunc()
	{
		cout << "HideA function" << endl;
	}

	void usehidefunc()
	{
		// 隐藏外部函数hidefunc，使用外部函数时要加作用域
		hidefunc();
		::hidefunc("lvlv");
	}
};

class HideB : public HideA
{
public:
	void hidefunc()
	{
		cout << "HideB function" << endl;
	}

	void usehidefunc()
	{
		// 隐藏基类函数hidefunc，使用外部函数时要加作用域
		hidefunc();
		HideA::hidefunc();
	}
};

int main()
{
    HideB B;
    B.usehidefunc();
    B.HideA::usehidefunc();
    // B b;
    // b.fun();
    // b.fun(10); // 编译不通过，因为这里不是函数重载，只是函数覆盖，函数重载
    return 0;
}