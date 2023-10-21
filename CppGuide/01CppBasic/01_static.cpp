#include <iostream>
using namespace std;


class Point
{
public:
    // 构造函数
    Point(int x = 0, int y = 0): x_(x), y_(y){
        // 在构造函数中对 count 进行累加，所有对象共同维护同一个 count
        count++;
    }

    Point(Point &p){
        x_ = p.x_, y_ = p.y_;
        count++;
    }

    ~Point(){ count--; } // 构造函数

    int getX(){ return x_; }

    int getY(){ return y_; }

    void showCount(){
        cout << "Object count : " << count << endl;
    }

    static void StaticShowCount(){
        cout << "Static Object count : " << count << endl;
    }
private:
    // 私有数据成员
    int x_, y_;
    // 静态数据成员声明，用于记录点的个数
    static int count;
};

/* 静态数据成员的定义和初始化，必须使用类名来限定 */
int Point::count = 0;

// 1. 静态全局变量：位于内存中的全局区
static int static_global_var = 520;

// 1. 测试静态全局变量
void TestStaticGlobalVar()
{
    static_global_var = 20;
    cout << static_global_var << endl;
}

// 2. 测试静态局部变量
void TestStaticLocalVar()
{
    // 静态局部变量同样位于全局数据区中，只被初始化一次，之后调用函数该变量不会被初始化。
    // 由于静态局部变量位于全局数据区，因此直到程序运行接收，该变量的内存才会被回收。
    // 同时由于静态局部变量的作用域为局部作用域，因此当定义它的函数或语句块结束时，其作用域随之结束。
    static int static_local_var = 10;
    cout << static_local_var++ << endl;
}

// 3. 静态函数：静态函数只能在声明它的文件中可见，不能被其他文件所使用
static void TestStaticFunc()
{
    int a = 20;
    cout << a << endl;
}

int main()
{   
    TestStaticFunc();
    TestStaticFunc();
    // TestStaticLocalVar(); // 10
    // TestStaticLocalVar(); // 11
    // TestStaticLocalVar(); // 12
    // TestStaticGlobalVar();
    // Point a(4, 5);
    // cout << "Point A : " << a.getX() << ", " << a.getY();
    // a.showCount();

    // Point b(a);
    // cout << "Point B : " << b.getX() << ", " << b.getY();
    // b.showCount();

    return 0;
}

