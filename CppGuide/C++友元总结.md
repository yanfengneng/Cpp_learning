- [一、友元函数/友元类的定义](#一友元函数友元类的定义)
- [二、友元的分类](#二友元的分类)
	- [2.1 外部友元函数](#21-外部友元函数)
		- [一个外部函数作为多个类的友元函数](#一个外部函数作为多个类的友元函数)
	- [2.2 友元函数是其他类的成员函数](#22-友元函数是其他类的成员函数)
	- [2.3 友元类](#23-友元类)
		- [友元函数与友元类的比较](#友元函数与友元类的比较)
		- [友元函数/友元类的优缺点](#友元函数友元类的优缺点)
- [三、友元函数在运算符重载中的应用](#三友元函数在运算符重载中的应用)

***
参考：[友元函数详解（定义、实现、优缺点）](https://blog.csdn.net/weixin_42031299/article/details/127699941)、[C++友元函数](https://blog.csdn.net/weixin_59179454/article/details/127574320)、[C++之友元函数](https://blog.csdn.net/m0_59052131/article/details/127591261)

****
# 一、友元函数/友元类的定义


**定义：**

* 1）在类中用 `friend` 关键字去声明函数/类，则这个函数/类就会变成友元函数/友元类；
* 2）**友元函数/友元类的声明位置没有要**求，可以在 `private、protected、public` 权限区，效果都是一样的；
* 3）**友元函数/友元类是单向的**，A 在 B 类中被声明为友元函数/友元类，表示 A 是 B 的友元函数/友元类，但 B 不是 A 的友元类函数/友元类；
* 4）**友元函数/友元类具有和类成员函数一样的权限，可以访问 protected 和 private 权限的成员，但不是类的成员函数**；
* 5）友元函数在**类中声明时用 `friend` 修饰**，但是在**定义时不需要用 `friend` 修饰**；
* 6）**友元函数不能被继承**：父类的友元函数，继承后并不会成为子类的友元函数；
* 7）**友元函数不具有传递性**：A 类和 B 类都是 C 类的友元类，但是 A 类和 B 类并不是友元类；

****

**友元函数与类成员函数、非友元函数的区别：**

* 1）**友元函数和非友元函数都是类外函数，不是类的成员函数，所以函数内不能使用this指针来表示类的对象**；
* 2）友元函数相比于非友元函数，**友元函数具有类成员函数一样的权限，可以访问类的`protected` 和 `private` 权限下的成员，而非友元函数不可以**；
* 3）**友元函数不是类的成员，所以不能用类的对象去访问友元函数**；



# 二、友元的分类

## 2.1 外部友元函数

**定义**：使用一个普通函数作为类的友元，那么在当前函数中就可以通过对象访问类的 `private` 或 `protected` 数据成员。

* 1）外部友元函数是类中说明的类，**它不是该类的成员函数，但是允许访问该类的所有成员，它是独立于任何类的外部函数**。
* 2）外部友元函数的参数为该类的对象，因为外部友元函数不是类的成员，所以没有 this 指针，只能通过 `对象名.成员变量名` 来访问成员变量。
* 3）在类中声明友元函数使用 `friend` 关键字，在类外定义友元函数去掉 `friend` 关键字。
* 4）若在类声明中定义了友元函数（给定了函数体代码），则该友元函数是内联的。

```cpp
class A
{
public:
	A(int i=0):m_i(i){}
	int GetI() const
	{
		return m_i;
	}
	friend void Add(A& a, A& b);
protected:
	// friend void Add(A& a, A& b); // 将Add函数作为类A的友元，在内部中可以定义函数体，但是定义了之后该友元函数为内联函数了
private:
	// friend void Add(A& a, A& b); // 在保护和私有都能正确运行
	int m_i;
};
 
// 想在Add函数中访问私有数据成员，又不想通过接口（共有函数）
void Add(A& a, A& b)
{
	cout << a.m_i + b.m_i << endl;
}

int main()
{
	A a(5);
	A b(8);
	Add(a, b);
    return 0;
}
```

### 一个外部函数作为多个类的友元函数

**说明：**

* 1）在本例中，将 sum() 声明为 A 和 B 类的 friend 函数。因此，该函数现在可以访问这两个类的私有成员和受保护成员。**这两个类的对象都作为函数的参数传递**。
* 2）**注意，我们在定义类 A 之前声明了类 B，因为在类 A 的主体中，friend 函数接受参数 'A' 和 'B' **。也就是需要前向声明。

声明语法：`friend <返回值类型> <函数名> (<参数列表>);`

```cpp
class B;    // 前向引用声明
class A
{
public:
	A(int i=0):m_i(i){}
	friend int Sum(A& a, B& b);// 在这之前未定义class B，需进行声明
private:
	int m_i;
};

class B
{
public:
	B(int j = 0) :m_j(j) {}
	friend int Sum(A& a, B& b);// 一般情况下放在共有里面
private:
	int m_j;
};

int Sum(A& a, B& b)// 定义友元函数
{
	return a.m_i + b.m_j;
}


void main()
{
	A a(20);
	B b(20);
	cout << Sum(a, b) << endl;
}
```



## 2.2 友元函数是其他类的成员函数

**定义**：一个类 B 的成员函数作为另一个类 A 的友元函数。**注意 friend 函数仅仅来类中声明，friend 函数需要在类外定义**。与前一种外部定义的友元函数相比，该友元函数的存取范围小得多，只能访问其作为友元类中的所有成员。

声明语法：`friend <函数返回值类型> <类名>::<成员函数名>(<形参列表>);`

```cpp
// 前向声明
class C;
class A;

class B
{
public:
    B(int j = 0):m_j(j) { }
    void Sub(A& a, B& b, C& c);// 只声明，不定义
    void Print(A& a);// 只声明，不定义
private:
    int m_j;
};

class A
{
public:
    A(int i = 0): m_i(i) { }
    // 另一个类的成员函数作为当前类的友元，用来访问当前类的成员数据
    friend void B::Sub(A& a, B& b, C& c);// 类 B 的成员函数作为类 A 的友元函数
    friend void B::Print(A& a); // 类 B 的成员函数作为类 A 的友元函数
private:
    int m_i;
};

class C
{
public:
    C(int k = 0): m_k(k) { }
    friend void B::Sub(A& a, B& b, C& c);// 类 B 的成员函数作为类 C 的友元函数
private:
    int m_k;
};

// 友元函数的定义一般放在类外
void B::Sub(A& a, B& b, C& c)
{
    cout << a.m_i - m_j + c.m_k << endl;
}

// 友元函数的定义一般放在类外
void B::Print(A& a)
{
	cout << a.m_i << endl;
}

int main()
{
	// A a(20);
	// B b(20);
	// cout << Sum(a, b) << endl;
    A a(10);
	B b(20);
	C c(30);
	b.Sub(a, b, c);
	b.Print(a);
    return 0;
}
```



## 2.3 友元类

**定义**：整个类作为另一个类的友元类。友元类的每个成员函数都是另一个类的友元函数，都可以访问另一个类中的所有成员，公有、保护或私有数据成员。

```cpp
class B;
class A
{
public:
    A(int a = 0) : m_a(a) { }
    void print(B& b);
    void test(B& b);
    void show(B& b);
private:
    int m_a;
};

class B
{
public:
    B(int b = 0) : m_b(b) { }
    friend class A;// 类 A 作为类 B 的友元类，则类 A 的所有成员函数都可以访问类 B 的所有数据成员
private:
    int m_b;
};

void A::print(B& b)
{
	cout << "a::print: " << b.m_b << endl;
}

void A::test(B& b)
{
	cout << "a::test: " << b.m_b << endl;
}

void A::show(B& b)
{
	cout << "a::show: " << b.m_b << endl;
}

int main()
{
	A a(2);
	B b(10);
	a.print(b);
	a.show(b);
	a.test(b);
    return 0;
}
```

A、B 类可以互为友元类：

```cpp
class B;
class A
{
public:
	A(int a = 0) :m_a(a) {}
	void print(B& b);
	void test(B& b);
	void show(B& b);
	friend class B;// 类 B 是类 A 的友元类，则类 B 可以访问类 A 的所有数据成员
private:
	int m_a;
};
class B
{
public:
	B(int b=0):m_b(b){}
	friend class A;// 类 A 是类 B 的友元类，则类 A 可以访问类 B 的所有数据成员
	void Print(A& a);
private:
	int m_b;
};

// 类 A 与类 B 互为友元类，可以相互对方的私有、保护、共有数据成员
void B::Print(A& a)
{
	cout << a.m_a << endl;
}

void A::print(B& b)
{
	cout << "a::print:" << b.m_b << endl;
}

void A::test(B& b)
{
	cout << "a::test:" << b.m_b << endl;
}

void A::show(B& b)
{
	cout << "a::show:" << b.m_b << endl;
}

void main()
{
	A a(2);
	B b(10);
	a.print(b);
	a.show(b);
	a.test(b);
	b.Print(a);
}
```

### 友元函数与友元类的比较

1）当A类被声明为B类的友元类时，则A类中的所有成员函数都可以访问B类private和protected权限成员；
2）A类和B类可以都声明对方为友元类，则A类和B类互为友元类，都可以访问对方类受保护的成员；
3）类中包含一个或者多个成员函数，将类声明为友元类，则相当于一次声明了多个友元函数；

**总结：友元类可以批量的声明友元函数；**



### 友元函数/友元类的优缺点

缺点：友元函数不是类的成员但是却具有成员的权限，**可以访问类中受保护的成员，这破坏了类的封装特性和权限管控**；

优点：可以实现类之间的数据共享；比如**上面互为友元类，则可以互相访问对方受保护的成员**；

**总结：友元函数是一种破坏封装特性的机制，可以让程序员写代码更灵活，但是不能滥用；**

# 三、友元函数在运算符重载中的应用

参考：[【C++入门】运算符重载详解](https://blog.csdn.net/weixin_42031299/article/details/127593164)

<font color=alice>友元函数重载运算符与类中定义重载运算符的区别在于：友元函数实现运算符重载，不能使用 this 指针，因为友元函数不属于类本身，需要将操作数作为参数传入运算符的参数列表中。</font>

***

**友元函数与成员函数实现运算符重载的选择：**

* 1）两种方式C++都是支持的，功能上都可以实现，运算符选择任意一种来实现运算符重载都是可以的；
* 2）**一般建议将双目运算符重载用友元函数实现，单目运算符重载用成员函数实现**；
* 3）**双目运算符用成员函数实现重载**：两种操作数的地位其实是不相等的，运算符左侧的操作是用this指针表示，右侧的操作数是传进去的参数，地位不相等，容易造成 `a+b` 不等于 `b+a` ；
* 4）**单目运算符用成员函数实现重载**：因为单目运算符只涉及一个操作对象，直接使用成员函数的this指针就可以实现功能，很方便；

```cpp
#include <iostream>

using namespace std;

class coordinate
{
public:
	coordinate():x(0), y(0) { }
	coordinate(int x0, int y0);
	
	void print(void);

	// 友元函数
	friend coordinate operator+(const coordinate& a, const coordinate& b);
private:
    int x;					// x轴坐标
	int y;					// y轴坐标
};

coordinate::coordinate(int x0, int y0)
{
	x = x0;
	y = y0;
};

void coordinate::print()
{
	cout << "(" << this->x << ", " << this->y << ")" << endl;
}

// 用独立函数来实现+的运算符重载
coordinate operator+(const coordinate& a, const coordinate& b)
{
	coordinate tmp;
	
	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	
	return tmp;
}


int main()
{
	coordinate a(1, 3);
	coordinate b(2, 4);
	coordinate c;
	
	c = a + b;	// 相当于是 c = operator+(a, b);
	
	a.print();
	b.print();
	c.print();

	return 0;
}
```

