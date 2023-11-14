#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class HasPtr
{
    // 使用友元函数，以便访问 HasPtr 的私有数据成员
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const string& s = string()): ps(new string(s)), i(0){}
    HasPtr(const HasPtr& p): ps(new string(*(p.ps))), i(p.i){} // 拷贝构造函数
    HasPtr& operator=(const HasPtr&);   // 拷贝赋值运算符
    HasPtr& operator=(const string&);   // 赋予新 string
    string& operator*();                // 解引用
    bool operator<(const HasPtr&) const;    // 比较运算
    ~HasPtr();
private:
    string* ps;
    int i;
};

bool HasPtr::operator<(const HasPtr& rhs) const
{
    return *ps < *rhs.ps;
}

inline
void swap(HasPtr& lhs, HasPtr& rhs)
{
    cout << "交换 " << *lhs.ps << "和" << *rhs.ps << endl;
    using std::swap;
    // 由于指针类型和整数类型，都是内置类型，因此下面这两个 swap 使用的是 std::swap，而不是 HasPtr 版本的 swap，所以不会导致递归循环
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

HasPtr::~HasPtr()
{
    delete ps;  // 释放 ps 指向的 string 对象的内存
}

// 大多数赋值运算符组合了析构函数和拷贝构造函数的工作
// 类似析构函数，赋值操作会销毁左侧运算对象的资源；类似拷贝构造函数，赋值操作会从右侧运算对象拷贝数据
inline
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    // a = rhs
    // 先拷贝再销毁：rhs 表示右侧运算对象，先拷贝右侧对象指向的string字符串值，然后再释放左侧对象中的 ps 指向的 string 内存空间
    auto nps = new string(*rhs.ps); // 重新申请一块内存空间，用于存储 ps 指向的字符串
    delete ps;  // 释放左侧对象指向的 string 内存空间
    ps = nps;   // 将右侧对象中 string 字符串空间拷贝到本对象，也就是左侧对象
    i = rhs.i;  // 使用内置的 int 赋值
    return *this; // 返回一个此对象的引用，返回左侧对象的引用
}

HasPtr& HasPtr::operator=(const string& rhs)
{
    *ps = rhs;
    return *this;
}

string& HasPtr::operator*()
{
    return *ps;
}

int main(int argc, char **argv)
{
    vector<HasPtr> vh;
    int n = atoi(argv[1]);
    for(int i = 0; i < n; ++i)
        vh.push_back(to_string(i));
    for(auto p : vh)
        cout << *p << " ";
    cout << endl;
    sort(vh.begin(), vh.end());
    for(auto p : vh)
        cout << *p << " ";
    cout << endl;
    return 0;
}