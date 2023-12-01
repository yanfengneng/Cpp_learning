#include <iostream>
#include <string>

using namespace std;

class Student // 基类
{
// private:
protected:
	string name;

public:
	Student():name("He"){}
	~Student(){}
	string getName();
	void setName(string n);
	void printAbout();
};

string Student::getName()
{
	return name;
}

void Student::setName(string n)
{
	name = n;
}

void Student::printAbout()
{
	cout << "I am a student"<<endl;
}

class UnderGraduate : public Student // 派生类
{
public:
	void printAbout();// 与父类的函数名相同，但是函数体功能不一样，称为多态函数
};

void UnderGraduate::printAbout()
{
	cout<<"I am a undergraduate"<<endl;
}

// class A
// {
// public:
// 	A(){ cout << "Constructor of A" << endl; }
// };

// class B : public A
// {
// public:
// 	B(){ cout << "Constructor of B" << endl; }
// };

// class C : public B
// {
// public:
// 	C(){ cout << "Constructor of C" << endl; }
// };

// class A
// {
// public:
// 	A( int l ){ cout << "Length : " << l << endl; }
// };

// class B : public A
// {
// public:
// 	// 关键先调基类，才能有派生类
// 	B() : A(10) { cout << "This is constructor of B" << endl; }
// };

class A
{
	int l1;
public:
	A(int z) : l1(z){ cout << "l1 : " << l1 << endl; }
};

class B : public A
{
	int l2;
public:
	B(int x, int y) : A(x), l2(y){ cout << "l2 : " << l2 << endl; }
};

int main()
{	
    // Student s;
	// UnderGraduate u;
	// string name = s.getName();
	// cout << name << endl;
	// s.printAbout();
	// u.printAbout();
    // UnderGraduate u;
	// // 子类可以调用基类的成员，但是基类的对象不能访问其派生类的成员
	// u.setName("xyz");
	// u.printAbout();
	// 派生类的构造函数的执行顺序是：先基类，后自己
    // cout << "Creating object of A :" << endl;
	// A a;
	// cout << "Creating object of B :" << endl;
	// B b;
	// cout << "Creating object of C :" << endl;
	// C c;
	B b(5, 10);
	return 0;
}