- [一、inline 函数](#一inline-函数)
- [二、constexpr 函数](#二constexpr-函数)
	- [2.1 使用方法](#21-使用方法)
	- [2.2 注意事项](#22-注意事项)

# 一、inline 函数

参考：

* 本科教材p27。

***

**inline 函数的定义：**

* 在函数声明的返回值类型前添加关键字 inline ，来显示声明 inline 函数**。也就是说 inline 必须放在函数声明的返回值类型前面才有机会成为内联函数，否则不起作用。**

```cpp
inline int max(int a, int b);

int max(){...}
```

<font color=blue>内联函数是 C++ 语言特有的一种附加函数类型，是通过在函数声明之前插入 inline 关键字实现的，在定义函数时可以不加 inline。</font><font color=alice>编译器会将编译后的全部内联函数的目标机器代码复制到程序内所有的引用位置，并把往返传送的数据也融合进引用位置的计算当中，用来避免函数调用机制所带来的开销，从而提高程序的执行效率。</font>

***

**内联声明只是向编译器发出的一个请求，编译器可以忽略这个请求**。使用 inline 函数是一种空间换时间的措施，若内联函数较长，且调用太频繁时，程序将会加长很多。**因此，通常只有较短的函数才能被定义为内联函数。**

* 1）**inline 函数的定义通常放在头文件中**。因为对于某个给定的内联函数来说，它的多个定义必须一致，所以内联函数通常被存放在头文件中，让每个调用该内联函数的文件都包含该头文件。
* 2）**默认在类中定义了成员函数（注意 `定义` 和 `声明` 的区别），那么该成员函数就是内联函数。**<font color=alice>如果在类中未给出成员函数定义，而又想内联该函数的话，那在类外定义上要加上 inline，否则就认为不是内联的。</font>

***

一般情况下，对内联函数有如下的限制：

* 1）不能有递归、静态数据、循环、switch 和 goto 语句、数组。
* 2）函数体也不能过长，比如函数代码超过 70 行就不太行。

**最后再说明一下：inline 只是对编译器的一个建议，具体怎么做还是取决于编译器怎么做。**

# 二、constexpr 函数

参考：

* [constexpr (C++)](https://learn.microsoft.com/zh-cn/cpp/cpp/constexpr-cpp?view=msvc-170)
* [C++中constexpr函数](https://blog.csdn.net/hou09tian/article/details/110470363)

***

**定义：**

* **constexpr 函数指的是在编译的时候就能得到其返回值的函数**。也就说编译器直接将 constexpr 函数转换为其返回值，因此 constexpr 函数都是被隐式地定义为内联函数，使用 `constexpr` 关键字来修饰 `constexpr` 函数。

## 2.1 使用方法

```cpp
constexpr int new_sz() { return 42; }
// 调用正确：foo 是一个常量表达式
constexpr int foo = new_sz();
```

## 2.2 注意事项

**1） `constexpr` 函数的返回值类型必须时字面值类型。**

```cpp
int g_i = 1;
constexpr int myFunc()
{
  	// 此时的返回值g_i不是字面值类型，因此报错信息为“error C3256: “g_i”: 变量使用不生成一个常量表达式”。
    return g_i;
}
```

**2）`constexpr` 函数的形参可以是非常量，但是实参必须是常量。**

```cpp
constexpr int myFunc(int i)
{
  return i;
}
// 此时 myFunc() 函数的实参是常量，在编译时可以直接被替换为1，程序不报错
constexpr int i = myFunc(1) * 4;

int j = 2;
// 此时，myFunc()函数的实参是非常量，程序报错信息为“error C2131: 表达式的计算结果不是常数”，将j定义为const int则不报错。
constexpr int k = myFunc(j) * 4;
```

**3）函数体中必须有且仅有一条 `return` 语句。**

```cpp
constexpr int myFunc(int i)
{
  	int j;
  	// 程序的报错信息为“error C3250: “j”: 不允许在“constexpr”函数体中进行声明”。
  	return i;
}
```

