#include <iostream>
using namespace std;

class Numbered
{
private:
    static int seq;
public:
    Numbered(){ mysn = seq++; }
    // 不定义拷贝构造函数，使用合成的拷贝构造函数时，只会简单的复制数据成员
    // Numbered(Numbered& n){ mysn = seq++;}
    int mysn;
};

// 静态数据成员的初始化
int Numbered::seq = 0;

void f(Numbered s)// 由于参数为非引用类型的，所以会调用拷贝构造函数
{
    cout << s.mysn << endl;
}

void f2(const Numbered& s)
{
    cout << s.mysn << endl;
}

int main()
{
    Numbered a, b = a, c = b;
    f2(a); f2(b); f2(c);
    return 0;
}