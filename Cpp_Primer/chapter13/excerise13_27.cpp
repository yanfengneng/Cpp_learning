#include <string>
#include <iostream>
using namespace std;

class HasPtrCount
{
public:
    // 构造函数分配新的 string 和新的计数器，将计数器置为 1
    HasPtrCount(const string& s = string()): ps(new string(s)), i(0), use(new size_t(1)){}
    // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
    // 拷贝构造函数
    HasPtrCount(const HasPtrCount& p):ps(p.ps), i(p.i), use(p.use){ ++*use; }
    // 拷贝赋值运算符，a = rhs
    // 之所以采用先递增 rhs 中的计数，然后再递减左侧运算对象中的计数，是为了处理自赋值，也就是两个对象相同时，避免释放再赋值前，造成访问无效内存空间
    HasPtrCount& operator=(const HasPtrCount& rhs)
    {
        // a = rhs
        ++*rhs.use; // 递增右侧运算对象的引用计数，表示又有一个对象指向相同 string 内存空间了
        if(--*use == 0){// 减少左侧对象中的引用计数，因为 a 又指向新的 string 内存空间了，因此需要递减它之前的引用计数
            delete ps;// 若引用计数减少到 0，则释放 ps 指向的 string 内存空间，以及 use 指向的 int 类型空间
            delete use;
        }
        // 然后将数据从 rhs 拷贝到本对象
        ps = rhs.ps, i = rhs.i, use = rhs.use;
        // 返回本对象
        return *this;
    }

    // 赋予新的 string
    HasPtrCount& operator=(const string& rhs)
    {
        *ps = rhs;
        return *this;
    }

    // 解引用
    string& operator*()
    {
        return *ps;
    }

    // 析构函数
    ~HasPtrCount()
    {
        if(--*use == 0) // 若引用计数变为 0，则释放 ps 指向的 string 内存，释放 use 指向的 int 类型数据的内存
        {
            delete ps;
            delete use;
        }
    }
private:
    string *ps;
    int i;
    size_t *use;    // 用来记录有多少个对象共享 *ps 的成员
};

int main()
{
    HasPtrCount h("hi mom!");
    HasPtrCount h2 = h; // 未分配新 string，h2 和 h 指向相同的 string
    h = "hi dad!";
    cout << "h: " << *h << endl;
    cout << "h2: " << *h2 << endl;
    return 0;
}