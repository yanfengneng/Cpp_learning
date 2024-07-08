- [一、this 指针的定义及用法](#一this-指针的定义及用法)
- [二、this 指针的本质：指针常量](#二this-指针的本质指针常量)
  - [2.1 this 指针的类型](#21-this-指针的类型)
- [三、this 指针的特点](#三this-指针的特点)


参考：

* [C++ this指针](https://blog.csdn.net/qq_21989927/article/details/111474451)
* [C++中this指针的理解与作用详解](https://zhuanlan.zhihu.com/p/95735331)

# 一、this 指针的定义及用法

C++中成员变量和成员函数是分开存储的，**每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码。**

那么问题是：这一块代码是如何区分哪个对象调用自己的呢？

C++通过提供特殊的对象指针，this指针，解决上述问题。**this指针指向被调用的成员函数所属的对象，this指针是隐含每一个非静态成员函数内的一种指针，它不需要定义，直接使用即可。**

**this指针的用途：**

* 1）当**形参与类中的变量同名**时，可用 this 指针来进行区分。
* 2）在类中的非静态成员函数中返回对象本身时，可以使用 return *this。
* 3）每个对象拥有一个 this 指针，通过 this 指针来访问自己的成员变量。
* 4）this 指针并不是对象的一部分，this 指针所占的内存大小是不会反应在 `sizeof` 操作符上的。
* 5）this 指针只能在成员函数中实用，全局函数、静态函数都不能使用 this 指针。
* 6）在普通的成员函数中，**this 指针是一个指针常量（Type * const pointer）**。在 const 成员函数中，**this 指针是一个指向常量的指针常量（const Type * const pointer），不能修改 this 指针指向的值。**
* 7）**this 指针在成员函数开始前构造，在成员函数结束后销毁。**



# 二、this 指针的本质：指针常量

**this 指针的本质是一个指针常量：`Type* const pointer;`**

this 指针存储了调用它的对象的地址，并且该地址不能被重新赋值（也就是不能被修改）。也就是 **this 指针就是指向当前对象的指针。**

## 2.1 this 指针的类型

```cpp
class B
{
public:
  /* 编译器将其转换为一个外部的、非成员的、普通的函数 */
  /* this做为隐式参数传递给函数fun() */
  /* void fun1(const B* const this)*/
  void fun1() const {};
  /* void fun2(volatile B* const this) */
  void fun2() volatile {};
  /* void fun2(const volatile B* const this) */
  void fun3() const volatile {};
};

/*********************************/
int Person::getId()const
{
    return this->id;
}
string Person::getName()
{
    return this->name;
}
const Person p(1,"yyy");
p.getId();    //正确，getId为const成员函数
p.getName();  //错误，p为const对象，不能调用非const成员函数
Person p1(2,"ddd");
p1.getId();    //正确，普通对象可以调用const成员函数
p1.getName();  //正确，普通对象可以调用非const成员函数
```
这里顺便补充一点：

* [07const 关键字总结](07const关键字总结.md) 里面具体总结了 **const 对象只能访问 const 成员函数，不能访问非 const 成员函数，否则会报错**。因为 const 成员函数不能修改对象，因此 const 对象只能调用 const 成员函数，不能调用非 const 成员函数。

[02static用法总结&C++程序内存布局](02static用法总结&C++程序内存布局.md) 里面总结了**为什么 static 成员函数不能为 const 成员函数**。

参考：[this指针的类型](https://blog.csdn.net/shltsh/article/details/45949729)、[C++ this指针与const成员函数](https://blog.csdn.net/u011197534/article/details/78385550)



# 三、this 指针的特点

**由于 this 指针为指向当前对象的指针，因此其只能在成员函数中使用，在全局函数函数、静态成员函数中不能使用 this 指针。**<font color=blue>因为静态成员函数，不单独属于某个对象，它属于该类所共有的，因此在静态成员函数内部不能使用成员变量（成员变量是属于 this 指针的，也就是属于当前对象的）。要想在静态成员函数中使用成员变量，只能将对象作为形参来进行传入，使用`对象.成员变量`的方式来访问。</font>

