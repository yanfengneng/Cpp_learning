#include <iostream>
using namespace std;

class Box {
public:
    // 默认构造函数
    Box() {}

    // 初始化 Box 类使用相同的值
    explicit Box(int i) : m_width(i), m_length(i), m_height(i) // 列表初始化
    {}

    // 初始化 Box 类使用自定义的参数
    Box(int width, int length, int height)
        : m_width(width), m_length(length), m_height(height)
    {}

    int Volume() { return m_width * m_length * m_height; }

private:
    // 调用默认构造函数时将会使用 0 值
    // 若这里没有0初始化值时，默认构造函数将使用垃圾值进行初始化
    int m_width{ 0 };
    int m_length{ 0 };
    int m_height{ 0 };
};

// class B
// {
//     B(int i){}
// };

// class A
// {
//     A(){}
//     B b;
// };

// class A
// {
//     A(const A&){}
// };

// class B : public A{};

// class ConstRef
// {
// public:
//     ConstRef(int ii);
// private:
//     int i;
//     const int ci;
//     int &ri;
// };

// ConstRef::ConstRef(int ii)
// {
//     i = ii;     // 正确
//     ci = ii;    // 错误：不能给 const 赋值
//     ri = i;     // 错误：ri没被初始化
// }
// class X
// {
//     int i;
//     int j;
// public:
//     // 未定义行为：i 在 j 之前被初始化
//     X(int val):j(val), i(j){}
// };

// class Foo
// {
// public:
// 	Foo(int i) : Foo('c') { type = i; }
// 	Foo(char c) : Foo(1) { name = c; }
// private:
// 	int type;
// 	char name;
// };

class Foo
{
public:
	Foo(int i) try: Foo(i,'c') 
	{
		cout<<"start assignment"<<endl;
		type = i; 
	}
	catch(...)
	{
		cout<<"caugth exception"<<endl;
	}

private:
	Foo(int i,char c) 
	{
		cout<<"throw exception"<<endl;
		throw 0;
	}
	int type;
	char name;

};

class PrivateCopy
{
    PrivateCopy(const PrivateCopy&);
    PrivateCopy & operator=(const PrivateCopy&);
public:
    PrivateCopy() = default;
    ~PrivateCopy();
};

class HasPtr
{
public:
    HasPtr(const std::string & s = std::string()): // 带默认参数的构造函数
        ps(new std::string(s)), i(0) {}
    
    ~HasPtr(){ delete ps; }

    // 删掉自定义的深拷贝构造函数和拷贝赋值运算符，使用合成的这俩函数
    // // 深拷贝构造函数
    // HasPtr(const HasPtr& hp)
    // {
    //     ps = new string(*(hp.ps)); // 重新申请一块内存空间，用于存储 ps 指向的字符串
    //     i = hp.i;
    // }
    
    // // 重载赋值运算符，用于拷贝初始化
    // HasPtr& operator=(const HasPtr& rhs)
    // {
    //     auto ps_ = new string(*(rhs.ps)); // 重新申请一块内存空间，用于存储 ps 指向的字符串
    //     delete ps;  // 销毁原 string 的内存空间
    //     ps = ps_;   // 指H向新 string 的内存空间
    //     i = rhs.i;  // 使用内置的 int 赋值
    //     return *this;   // 返回一个此对象的引用
    // }
private:
    std::string *ps;
    int i;
};

HasPtr f(HasPtr hp) // hp 是值传递，被拷贝一次
{
    HasPtr res = hp; // 拷贝给定的 HasPtr
    // 当函数 f 返回时，hp 和 res 都被销毁，析构函数会 delete res 和 hp 中的指针成员，由于这两个指针成员指向同一个地址对象，这个地址对象被释放两次，显然是错误的
    return res; // res 和 hp 被销毁
}

class HasPtrCount
{
public:
    // 构造函数分配新的 string 和新的计数器，将计数器置为 1
    HasPtrCount(const string& s = string()): ps(new string(s)), i(0), use(new size_t(1)){}
    // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
    // 拷贝构造函数
    HasPtrCount(const HasPtrCount& p):ps(p.ps), i(p.i), use(p.use){ ++*use; }
    // 拷贝赋值运算符
    HasPtrCount& operator=(const HasPtrCount& rhs)
    {
        ++*rhs.use;
        if(--*use == 0){
            delete ps;
            delete use;
        }
        ps = rhs.ps, i = rhs.i, use = rhs.use;
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

    ~HasPtrCount()
    {
        if(--*use == 0)
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

class NoDtor
{
public:
    NoDtor() = default;     // 使用合成默认构造函数
    ~NoDtor() = delete;     // 不能销毁 NoDtor 类型的对象
};

int main()
{
    HasPtrCount h("hi mom!");
    HasPtrCount h2 = h;
    h = "hi dad!";
    cout << "h: " << *h << endl;
    cout << "h2: " << *h2 << endl;
    // NoDtor nd;  // 错误：NoDtor 的析构函数是删除的
    // NoDtor *p = new NoDtor();   // 正确：但是不能 delete p
    // delete p;   // 错误：NoDtor 的析构函数是删除的
    // HasPtr p("hello world!");
    // f(p);
    // HasPtr q(p); 
    
    // A a(); // error C2512: 'B' : no appropriate default constructor available
    // B b; //error C2512:'B': no appropriate default constructor available
    // X x(1);
    // Foo f(1);
    return 0 ; 

    // Box b; // Calls Box()
    // cout << b.Volume() << endl;

    // // 使用统一初始化：
    // Box b2 {5}; // Calls Box(int)
    // cout << b2.Volume() << endl;
    // Box b3 {5, 8, 12}; // Calls Box(int, int, int)
    // cout << b3.Volume() << endl;

    // // 使用函数式表示法：
    // Box b4(2, 4, 6); // Calls Box(int, int, int)
    // cout << b4.Volume() << endl;
    
    // return 0;
}