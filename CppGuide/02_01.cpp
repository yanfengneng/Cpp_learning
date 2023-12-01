#include <iostream>
#include <string>

using namespace std;

// class Student
// {
// 	string name;
// public:
//     // 可以有任意数量的构造函数，但是参数的数量或类型必须是不同的
//     Student(string n) : name(n) { }
//     Student() : name("unknown") { }
//     void printName() { cout << name << endl; }
// };

class Rectangle
{
public:
    int length;
    int breadth;
    Rectangle(int l, int b):length(l),breadth(b){}

    int printArea();
};

int Rectangle::printArea()
{
	return length * breadth;
}

class Student
{
	string name;
	int marks;
public:
    void getName();
    void getMarks();
    void displayInfo();
};

void Student::getName()
{
	getline(cin, name);
}

void Student::getMarks()
{
	cin >> marks;
}

void Student::displayInfo()
{
	cout << "Name : " << name << endl;
	cout << "Marks : " << marks << endl;
}

// class Animals
// {
// public:
//     void sound();
// };
// void Animals::sound()
// {
// 	cout << "This is parent class" << endl;
// }

// class Dogs : public Animals
// {
// public:
//     void sound();
// };

// void Dogs::sound()
// {
// 	cout<< "Dogs bark" << endl;
// }

class Animals
{
public:
    void sound()
    {
        cout << "This is parent class" << endl;
    }
};

class Dogs : public Animals
{
public:
    void sound()
    {
        cout << "Dogs bark" << endl;
    }
};

class Cats : public Animals
{
public:
    void sound()
    {
        cout << "Cats meow" << endl;
    }
};

class Pigs : public Animals
{
public:
    void sound()
    {
        cout << "Pigs snort" << endl;
    }
};

int main()
{
    Dogs d;
	Cats c;
	Pigs p;
	d.sound();
	c.sound();
	p.sound();
    // Dogs d;
	// d.sound();
    // Student st[5];//创建了5个Student实例
	// for( int i = 0; i < 5; i++ )
	// {
	// 	cout << "Student " << i + 1 << endl;
	// 	cout << "Enter name" << endl;
	// 	st[i].getName();
	// 	cout << "Enter marks" << endl;
	// 	st[i].getMarks();
	// }

	// for( int i = 0; i < 5; i++ )
	// {
	// 	cout << "Student " << i + 1 << endl;
	// 	st[i].displayInfo();
	// }
    // Rectangle rt1(7, 4);
	// Rectangle rt2(4, 5);
	// cout << "Area of first rectangle " << rt1.printArea() << endl;
	// cout << "Area of second rectangle " << rt2.printArea() << endl;
	// Student a("xyz");
	// Student b;
	// a.printName();
	// b.printName();
	return 0;
}