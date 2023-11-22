#include <iostream>
using namespace std;

// class A
// {
// public:
// 	A(int i=0):m_i(i){}
// 	int GetI() const
// 	{
// 		return m_i;
// 	}
// 	friend void Add(A& a, A& b);
// protected:
// 	// friend void Add(A& a, A& b); // 将Add函数作为类A的友元，在内部中可以定义函数体，但是定义了之后该友元函数为内联函数了
// private:
// 	// friend void Add(A& a, A& b); // 在保护和私有都能正确运行
// 	int m_i;
// };
 
// // 想在Add函数中访问私有数据成员，又不想通过接口（共有函数）
// void Add(A& a, A& b)
// {
// 	cout << a.m_i + b.m_i << endl;
// }

// class B;    // 前向引用声明
// class A
// {
// public:
// 	A(int i=0):m_i(i){}
// 	friend int Sum(A& a, B& b);// 在这之前未定义class B，需进行声明
// private:
// 	int m_i;
// };

// class B
// {
// public:
// 	B(int j = 0) :m_j(j) {}
// 	friend int Sum(A& a, B& b);// 一般情况下放在共有里面
// private:
// 	int m_j;
// };

// int Sum(A& a, B& b)// 定义友元函数
// {
// 	return a.m_i + b.m_j;
// }

// // 前向声明
// class C;
// class A;

// class B
// {
// public:
//     B(int j = 0):m_j(j) { }
//     void Sub(A& a, B& b, C& c);// 只声明，不定义
//     void Print(A& a);// 只声明，不定义
// private:
//     int m_j;
// };

// class A
// {
// public:
//     A(int i = 0): m_i(i) { }
//     // 另一个类的成员函数作为当前类的友元，用来访问当前类的成员数据
//     friend void B::Sub(A& a, B& b, C& c);// 类 B 的成员函数作为类 A 的友元函数
//     friend void B::Print(A& a); // 类 B 的成员函数作为类 A 的友元函数
// private:
//     int m_i;
// };

// class C
// {
// public:
//     C(int k = 0): m_k(k) { }
//     friend void B::Sub(A& a, B& b, C& c);// 类 B 的成员函数作为类 C 的友元函数
// private:
//     int m_k;
// };

// // 友元函数的定义一般放在类外
// void B::Sub(A& a, B& b, C& c)
// {
//     cout << a.m_i - m_j + c.m_k << endl;
// }

// // 友元函数的定义一般放在类外
// void B::Print(A& a)
// {
// 	cout << a.m_i << endl;
// }

class B;
class A
{
public:
    A(int a = 0) : m_a(a) { }
    void print(B& b);
    void test(B& b);
    void show(B& b);
private:
    int m_a;
};

class B
{
public:
    B(int b = 0) : m_b(b) { }
    friend class A;// 类 A 作为类 B 的友元类，则类 A 的所有成员函数都可以访问类 B 的所有数据成员
private:
    int m_b;
};

void A::print(B& b)
{
	cout << "a::print: " << b.m_b << endl;
}

void A::test(B& b)
{
	cout << "a::test: " << b.m_b << endl;
}

void A::show(B& b)
{
	cout << "a::show: " << b.m_b << endl;
}

int main()
{
	A a(2);
	B b(10);
	a.print(b);
	a.show(b);
	a.test(b);
    return 0;
}