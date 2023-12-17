#include <iostream>
using namespace std;

class Rectangle
{
public:
    int length;
    int breadth;
    
    /* 成员函数的声明 */
    void setLength(int l);
    void setBreadth(int b);
    int getArea();

    // 构造函数一般声明在类的内部
    Rectangle()
    {
        length = 10;
        breadth = 10;
    }

    // // 带参数的构造函数
    // Rectangle(int l, int b){
    //     length = l, breadth = b;
    // }

    // 构造函数的列表初始化
    Rectangle(int l, int b):length(l), breadth(b){}
};

/* 定义成员函数 */
void Rectangle::setLength(int l){
    length = l; 
}

void Rectangle::setBreadth(int b){
    breadth = b;
}

int Rectangle::getArea(){
    return length * breadth;
}

int main()
{
    
    // 
    Rectangle rt(7, 4);
    cout << "Area : " << rt.getArea() << endl;
    // Rectangle rt;
    // cout << "length = " << rt.length << endl;
    // cout<< "breadth = " << rt.breadth << endl;
    // rt.setLength(7);
    // rt.setBreadth(4);
    // int area = rt.getArea();
    // cout << "Area : " << area << endl;
    return 0;
}

/*
protected 和 private 的区别：
    1）protected：可以被该类中函数、子类的函数、其友元函数进行访问。但是不能被该类的对象访问。
    2）private：只能由该类中的函数、其友元函数访问。不能被任何其他的函数访问，也不能被该类的对象访问。
    3）private属性不能被继承，使用private继承时，父类的protected和public属性在子类中变为private，那么只能该父类只能被子类中的函数访问了。
    使用protected继承，父类的protected和public属性在子类中变为protected；使用public继续，父类中的protected和public属性不发生变化。


如果将某个变量声明为 const 类型，那么该变量可以初始化，但是不能被赋值：
    在数据类型之前使用 const 关键字声明的任何变量都是 const 变量。要初始化一个 const 变量，需要使用 C++ 的初始化方式。
    因为不能给 const 变量赋值，因此不能在构造函数内部给其赋值。只能使用构造函数初始化表来对 const 数据成员变量进行初始化。


在类中使用 static 关键字：已总结
*/
