#include <iostream>
using namespace std;

/*
*/

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

// 1. 静态全局变量
static int static_global_var = 520;

void TestStaticGlobalVar()
{
    static_global_var = 20;
    cout << static_global_var << endl;
}

int main()
{   
    TestStaticGlobalVar();
    // Point a(4, 5);
    // cout << "Point A : " << a.getX() << ", " << a.getY();
    // a.showCount();

    // Point b(a);
    // cout << "Point B : " << b.getX() << ", " << b.getY();
    // b.showCount();

    return 0;
}

