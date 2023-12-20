参考：

[C/C++const关键字详解](https://blog.csdn.net/weixin_44049823/article/details/128735316)

[C/C++面试：const使用总结](https://blog.csdn.net/zhizhengguan/article/details/81274713)

[C++const用法总结](https://blog.csdn.net/fuxingwe/article/details/8774855)

[C++ const的用法详解](https://blog.csdn.net/weixin_56935264/article/details/125760242)

[C/C++ const 总结 / const在函数前/后的作用](https://blog.csdn.net/weixin_42562387/article/details/114017352)

# 一、const 的作用

1. 保护被修饰的变量，防止意外修改，增强程序的健壮性。
2. `const` 定义常量从汇编的角度来看，只是给出了对应的内存地址，所以，`const` 定义的常量在程序运行过程中只有一份拷贝，节省内存空间, 避免不必要的内存分配。
3. 编译器通常不为普通 `const` 常量分配存储空间，而是将它们保存在符号表中，这使得它成为一个编译期间的常量，没有了存储与读内存的操作，使得它的效率也很高。



# 二、const 修饰基本数据类型

## 2.1 const 修饰常见数据类型

先上结论：**在常变量、常引用、常对象、常数组中，修饰符 `const` 既可以在类型说明前面，也可以在类型说明符后面，二者是等价的。**

```cpp
// 1. 常量
int const x = 2;
const int x = 2; // 与上面等价

// 2. 常数组
int const arr[3] = {1,2,3};
const int arr[3] = {1,2,3}; // 与上面等价

// 3. 常引用
int value = 5;
const int& ref1 = value;    // 常量引用，不能通过引用修改值
int const& ref2 = value;    // 同上

// 4. 常对象
class A{
...
}; 
const A a;
A const a; // 与上面等价
```

## 2.2 const 修饰指针

参考：[常量指针和指针常量区分技巧](https://blog.csdn.net/qq_61996032/article/details/123890819)、[指针常量和常量指针区别](https://blog.csdn.net/weixin_52244492/article/details/124081709)

**区分技巧：**

* 从左往右读，直接把 `const` 读作常量，把`*`读作指针，这样就可以区分常量指针和指针常量了。

```cpp
const int *p=&a; // “常量” const在int *前，叫常量指针
int* const p=&a; // int *在“常量”const前，叫指针常量
```

以上就可以根据 `const` 和 `*` 的位置来轻松区分了。



### 2.2.1 常量指针（const  int* p、int const *p）

**常量指针**：本质上是一个指针，常量表示指针指向的内容，说明该指针指向一个“常量”。**在常量指针中，指针指向的内容是不可改变的，指针看起来好像指向了一个常量。**

```cpp
int a = 10;
int b = 20;
int const *pa = &a; 
const int *pa = &a; // 同上
*pa = 30;  // 错误：不能改变指针指向对象的值
pa = &b；  // 正确：指针可以指向其他地址，但是内容不能改变	
```



### 2.2.2 指针常量（int* const p）

**指针常量**：本质上一个常量，指针用来说明常量的类型，表示该常量是一个指针类型的常量。**在指针常量中，指针自身的值是一个常量，不可改变，始终指向同一个地址。在定义的同时必须初始化。**

```cpp
int a = 0，b = 0;
int* const p = &a;
*p = 1; 	// 正确：p 指向的地址是一定的，但其指向的值的内容可以改变
*p = &b; 	// 错误：不可改变地址
```



### 2.2.3 指向常量的指针常量（const int* const p）

定义：**指针的地址不可变，也不能通过指针改变指向地址的值。并且在声明时必须初始化**。

```cpp
int a = 0，b = 0;
const int * const p = &a;
*p = 1; // 错误：不可以修改值
*p = &b; // 错误：不可改变地址
```



例题：

```cpp
int main() {
    int m = 10;
    const int n = 20; // 必须在定义的同时初始化
 
    const int *ptr1 = &m; // 指针指向的内容不可改变
    int * const ptr2 = &m; // 指针不可以指向其他的地方
 
    ptr1 = &n; // 正确
    ptr2 = &n; // 错误，ptr2不能指向其他地方
 
    *ptr1 = 3; // 错误，ptr1不能改变指针内容
    *ptr2 = 4; // 正确
 
    int *ptr3 = &n; // 错误，常量地址不能初始化普通指针吗，常量地址只能赋值给常量指针
    const int * ptr4 = &n; // 正确，常量地址初始化常量指针
 
    int * const ptr5; // 错误，指针常量定义时必须初始化
    ptr5 = &m; // 错误，指针常量不能在定义后赋值
 
    const int * const ptr6 = &m; // 指向“常量”的指针常量，具有常量指针和指针常量的特点，指针内容不能改变，也不能指向其他地方，定义同时要进行初始化
    *ptr6 = 5; // 错误，不能改变指针内容
    ptr6 = &n; // 错误，不能指向其他地方
 
    const int * ptr7; // 正确
    ptr7 = &m; // 正确
 
    int * const ptr8 = &n;
    *ptr8 = 8;
 
    return 0;
}
```



## 2.3 const 修饰函数

### 2.3.1 const 修饰函数参数

防止传入的参数代表的内容在函数体内被改变，**但仅对指针和引用有意义**。因为如果是按值传递，传给参数的仅仅是实参的副本，即使在函数体内改变了形参，实参也不会得到影响。

**const 修饰的函数参数是指针时**：代表**在函数体内不能修改该指针所指的内容**，起到保护作用，在字符串复制的函数中保证不修改源字符串的情况下，实现字符串的复制。

**const 修饰的函数参数是引用时**：·`func3(A a)` 传递进来的参数 a 是实参对象的副本，要调用构造函数来构造这个副本，而且函数结束后要调用析构函数来释放这个副本，在空间和时间上都造成了浪费，所以函数参数为类对象的情况，推荐用引用。但按引用传递，造成了安全隐患，通过函数参数的引用可以修改实参的内部数据成员，所以**用 const 引用来保护实参**。

```cpp
void func1(const int i); 	// i 不能被修改

void func2(const char *src, char *dest); // 保护源字符串不被修改，若修改src则编译出错

void func3(const A& a);        // a所引用的对象不能被修改
```

### 2.3.2 const 修饰函数返回值

**修饰普通类型的返回值**：`const int func1();` // 此处返回 int 类型的 const 值，意思指返回的原函数里的变量的初值不能被修改，但是函数按值返回的这个变量被制成副本，能不能被修改就没有了意义，**它可以被赋给任何的 const 或非 const 类型变量，完全不需要加上这个 const 关键字。**

<font color=alice>但这只对于内部类型而言（因为内部类型返回的肯定是一个值，而不会返回一个变量，不会作为左值使用，否则编译器会报错），对于用户自定义类型，返回值是常量是非常重要的。</font>

**返回引用**：`const int &func2();` // 注意千万不要返回局部对象的引用，否则会报运行时错误：**因为一旦函数结束，局部对象被释放，函数返回值指向了一个对程序来说不再有效的内存空间**。

**返回指针**：`const int *func3(); `// 注意千万不要返回指向局部对象的指针，**因为一旦函数结束，局部对象被释放，返回的指针变成了指向一个不再存在的对象的悬垂指针**。



## 2.4 const 在类中

```cpp
class A
{
public:
    void func();
    void func() const;
    const Aoperator+(const A &) const;
private:
    int num1;
    mutable int num2;
    const size_t size;
};
```

### 2.4.1 const 成员变量

**const 成员变量**：**只在某个对象⽣命周期内是常量，⽽对于整个类⽽⾔是可以改变的**。因为类可以创建多个对象，不同的对象其 const 数据成员值可以不同。所以不能在类的声明中初始化 const 数据成员（**在类中直接定义 `const int a = 5;` 是错误的，但是 `static const int a = 5;` 是可以的**）， 因为类的对象在没有创建时候，编译器不知道 const 数据成员的值是什么。

**const 数据成员的初始化只能在类的构造函数的初始化列表中进⾏，试图在构造函数体内对 const 成员变量初始化都会引发编译错误**。

```cpp
A::A(size_t sz):size(sz) // ok：使用初始化成员列表来初始化 const 成员变量
{...}
```

### 2.4.2 const 成员函数

* 1）const 成员函数的主要目的是防止成员函数修改对象的内容。this 指针的类型为`类类型* const this`，即成员函数中，不能修改this指针指向的地址，但是其所指向对象的成员变量可以被修改，const 修饰类成员函数，实际上就是将 this 指针限定为：`const 类类型 * const this`，表明**在该成员函数中不能对调用对象的任何成员进行修改，起到保护对象的作用**。
* 2）要注意，**const 关键字和 static 关键字对于成员函数是不可以同时使用的**，因为static关键字修饰静态成员函数不含有this指针，也就是不能实例化，const成员函数又必须具体到某一个函数。
* 3）**const 成员函数如果一定要修改某个变量，可以用 `mutable` 进行修饰**。成员变量中如果想建立在整个类中都恒定的常量，应该用类中枚举常量或者 `static const` 实现。

```cpp
class MyClass {
public:
    mutable int mutableMember; // mutable 成员变量可以在 const 成员函数中修改

    // 使用规则：在函数形参列表后面加上 const 构成 const 成员函数
    void constFunction() const {
        mutableMember = 42; // 合法，const 函数中修改了 mutable 成员
    }
};
```

**const 函数的规则**：

* 1）**const 对象只能访问 const 成员函数，非 const 的对象可以访问任何成员函数，包括const 成员函数**。
* 2）**函数名、参数、返回值都相同的 const 成员函数和非 cons t成员函数可以构成重载**，那么 const 对象调用 const 成员函数，非 const 对象默认调用非 cons t的成员函数。
* 3）const 成员函数可以访问所有成员变量，**但是只能访问 const 的成员函数，不能访问非 const 的成员函数**。
* 4） **非 const 成员函数，可以访问任何成员变量，包括 const 成员成员函数**。
* 5）const 成员函数不能修改任何的成员变量，除非变量用 mutable 修饰。



### 2.4.3 const 修饰类对象

```cpp
const A a; // 类对象a只能调用 const 成员函数，否则编译器报错。
```



### 2.4.4 const 修饰类成员返回值

```cpp
const A operator+(const A &) const;// 前一个 const 用来修饰重载函数operator+的返回值，可防止返回值作为左值进行赋值操作

A a, b, c;
a + b = c; // errro: 由于返回的是右值，不能被赋值
```



## 2.5 类中定义常量的用法

在类中定义常量的定义大致有几种方式实现：1）使用枚举类型；2）使用 const 或 static。

**1） 使用枚举类型**

```cpp
class test
{
     enum { a = 10, b = 20}; // 枚举常量
     int array1[a];  
     int array2[b];
};
```

**2）使用 const 或 static 关键字**

```cpp
// using c++11 standard
class CTest11
{
public:
    static const int a = 3; // Ok in C++11
    static int b = 4;       // Error：静态成员变量需要在类外进行初始化
    const int c = 5;        // Ok in C++11
    int d = 6;              // Ok in C++11
public:
    CTest11() :c(0) { }     // Ok in C++11
};
 
int main()
{
    CTest11 testObj;
    cout << testObj.a << testObj.b << testObj.c << testObj.d << endl;
    return 0;
}
```

