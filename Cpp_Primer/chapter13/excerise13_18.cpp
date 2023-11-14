#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
    static int sn;
public:
    Employee() { mysn = sn++; }
    // 默认构造函数
    Employee(const string& s){ name = s, mysn = sn++; }

    // 定义拷贝构造函数和拷贝赋值运算符
    Employee(Employee& e){ name = e.name, mysn = sn++; }
    Employee& operator=(Employee& rhs){ name = rhs.name; *this; }

    const string& get_name(){ return name; }
    int get_mysn() { return mysn; }
private:
    string name;
    int mysn;
};

// 静态数据成员的初始化
int Employee::sn = 0;

void f(Employee& s)
{
    cout << s.get_name() << ":" << s.get_mysn() << endl;
}

int main()
{
    // a 初始化 b 调用拷贝构造函数
    Employee a("yan"), b = a, c;
    // b 为 c 赋值，调用拷贝赋值运算符
    c = b;
    f(a); f(b); f(c);

    return 0;
}