#include <iostream>
#include <string>
 
using namespace std;
 
class AccessTest
{
public:
	int pub_mem;
	int pub_fun(){};
protected:
	int prot_mem;
	int prot_fun(){};
private:
	int priv_memb;
	int priv_fun(){};
};

// 派生类定义的语法：class <派生类名> : [继承方式] <基类名>

class PubAccessTest : public AccessTest	// 共有继承
{
public:
	void test()
	{
		int x = pub_mem;    //OK
		pub_fun();         	//OK
		
		int y = prot_mem;    //OK
		prot_fun();        	 //OK
		
		// int z = priv_memb;   //ERROR
		// priv_fun();        	 //ERROR
	}
};


class ProtAccessTest : protected AccessTest // 保护继承
{
public:
	void test()
	{
		int x = pub_mem;   //OK
		pub_fun();         //OK
		
		int y = prot_mem;  //OK
		prot_fun();        //OK
		
		// int z = priv_memb; //ERROR
		// priv_fun();        //ERROR
	}
};

class PriAccessTest : private AccessTest // 私有继承
{
public:
	void test()
	{
		int x = pub_mem;     //OK
		pub_fun();           //OK
		
		int y = prot_mem;    //OK
		prot_fun();          //OK
		
		// int z = priv_memb;   //ERROR
		// priv_fun();          //ERROR
	}
};

class Animal {
protected:
   std::string m_name;
};

class Cat : public Animal {
public:
   using Animal::m_name; // 将 m_name 变成公共成员

   void printName() {
       std::cout << "My name is " << m_name << std::endl;
   }
};

class Person {
public:
   void sayHello() {
       std::cout << "Hello!" << std::endl;
   }
};

class Student : public Person {
protected:
   using Person::sayHello; // 将 sayHello 函数变成保护成员

public:
   void sayHello(int grade) {
       std::cout << "Hello! My grade is " << grade << std::endl;
   }
};

// // 1. 使用指针来访问私有变量
// class A 
// {
// // protected:
// private:
//    int num;
// public:
//    void setNum(int n) {
//        num = n;
//    }

//    int getNum() {
//        return num;
//    }
// };

class A
{
protected:
   int num;
public:
   void setNum(int n) {
       num = n;
   }
   int getNum() {
       return num;
   }
};

class B : public A 
{
public:
   void test() {
       int *p = (int *)&num; // 将protected成员变量地址强制转换为int指针
       *p = 20; // 通过指针访问protected成员变量
   }
};

int main()
{
	B b;
	b.setNum(10);
	b.test();
	cout << b.getNum() << endl; // 输出结果为20
	// A a;
	// int *p = (int *)&a; // 将对象地址强制转换为int指针
	// *p = 10; // 通过指针访问private成员变量
	// cout << a.getNum() << endl; // 输出结果为10
	
	// Student student;
	// student.sayHello(); // 编译错误，无法直接访问 sayHello() 函数（注意没有参数）
	// student.sayHello(90);
	// Cat cat;
	// cat.m_name = "Tom"; // 直接访问 m_name 变量
	// cat.printName();
	// PriAccessTest dt;
	// int x = dt.pub_mem;    //ERROR，基类的成员现在是派生类的私有成员
	// int y = dt.prot_mem;   //ERROR，基类的成员现在是派生类的私有成员
	// int z = dt.priv_memb;  //ERROR, private成员无法访问
	
	// int x = dt.pub_mem;    //ERROR，基类的成员现在是派生类的保护成员
    // int y = dt.prot_mem;   //ERROR，基类的成员现在是派生类的保护成员
    // int  z= dt.priv_memb;  //ERROR

	// PubAccessTest dt;
	// int x = dt.pub_mem;    //OK
	// int y = dt.prot_mem;   //ERROR
	// int z = dt.priv_memb;  //ERROR

	// AccessTest at;
	// at.pub_mem;     // OK, 类变量可以访问public成员
	// at.pub_fun();  // OK, 访问public成员函数是没有问题的
	return 0;
}