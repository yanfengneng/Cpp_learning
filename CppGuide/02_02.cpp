#include <iostream>

using namespace std;

// class Animals
// {
// public:
//     virtual void sound();
// };

// void Animals::sound()
// {
// 	cout<<"This is parent class" <<endl;
// }

// class Dogs : public Animals
// {
// private:
//     void sound();
// };

// void Dogs::sound()
// {
// 	cout<< "Dogs bark" <<endl;
// }

// 在抽象类中，除了纯虚函数外，可以有其他函数和变量
class Employee // 抽象类
{
	virtual int getSalary() = 0;
};

class Developer : public Employee // 派生类
{
private:
	int salary;
public:
	Developer(int s):salary(s){}
	int getSalary();
};

int Developer::getSalary()
{
	return salary;
}

// 抽象基类的子类必须定义抽象方法，否则子类也将变成抽象类
class Driver : public Employee // 派生类
{
private:
	int salary;
public:
	Driver(int t):salary(t){}
	int getSalary();
};

int Driver::getSalary()
{
	return salary;
}

class Animals // 抽象类
{
public:
    virtual void sound() = 0;
};

class Dogs  // 派生类
{
public:
    void sound()
    {
        cout << "Dogs bark" << endl;
    }
};

class Cats // 派生类
{
public:
    void sound()
    {
        cout << "Cats meow" << endl;
    }
};

class Pigs // 派生类
{
public:
    void sound()
    {
        cout << "Pigs snort" << endl;
    }
};

// 接口类是与抽象类相同的类，不同之处在于接口类的所有函数都是纯虚的，没有成员变量。
// 接口类的派生类必须实现该接口类的每一个虚函数，为基类的每个纯虚函数提供定义。
// 接口类也不能系创建实例（对象）
class IShape
{
public:
    virtual int getArea() = 0;
    virtual int getPerimeter() = 0;
};

class Rectangle : public IShape
{
	int length;
	int breadth;
public:
    Rectangle(int l, int b):length(l),breadth(b){}

    int getArea();

    int getPerimeter();

};

int Rectangle::getArea()
{
	return length * breadth;
}

int Rectangle::getPerimeter()
{
	return 2*(length + breadth);
}

class Square : public IShape
{
	int side;
public:
    Square(int a):side(a){}

    int getArea();

    int getPerimeter();

};

int Square::getArea()
{
	return side * side;
}

int Square::getPerimeter()
{
	return 4 * side;
}

int main()
{
    Rectangle rt(7, 4);
	Square s(4);
	cout << "Rectangle :" << endl;
	cout << "Area : " << rt.getArea() << " Perimeter : " << rt.getPerimeter() << endl;
	cout << "Square :" << endl;
	cout << "Area : " << s.getArea() << " Perimeter : " << s.getPerimeter() << endl;
    
    // Dogs d;
	// Cats c;
	// Pigs p;
	// d.sound();
	// c.sound();
	// p.sound();
    // // 两个派生类
    // Developer d1(5000);
	// Driver d2(3000);
	// int a, b;
	// a = d1.getSalary();
	// b = d2.getSalary();
	// cout << "Salary of Developer :" << a << endl;
	// cout << "Salary of Driver :" << b << endl;
	// Animals *a;
	// Dogs d;
    // // 声明为指向基类对象的指针，当它指向共有派生类对象时，只能利用它来直接访问派生类从基类继承来的成员，不能直接访问共有派生类中的其他成员
	// a= &d;
	// a -> sound();   //  早绑定

    // Animals a1;
    // Dogs *d1;
    // // d1 = &a1;// 报错：声明指向派生类对象的指针不能直接指向基类对象，因为类型不匹配，需要做强制类型转换
    // d1 = (Dogs*)&a1;
    // d1->sound();
	return 0;
}
