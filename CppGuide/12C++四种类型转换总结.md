- [1. `static_cast`](#1-static_cast)
- [2. `dynamic_cast`](#2-dynamic_cast)
- [3. `const_cast`](#3-const_cast)
- [4. `reinterpret_cast`](#4-reinterpret_cast)
- [5. C 风格类型转换](#5-c-风格类型转换)
- [总结](#总结)

参考：[static_cast和dynamic_cast详解](https://blog.csdn.net/u014624623/article/details/79837849)

> [C++四种强制转换](https://blog.csdn.net/daaikuaichuan/article/details/79476501)

C++ 提供了多种强制类型转换方式，分别用于不同的场景。主要有四种类型转换操作符：`static_cast`、`dynamic_cast`、`const_cast` 和 `reinterpret_cast`。这些转换方式比 C 风格的强制类型转换（如 `(int)x`）更加安全和明确。

### 1. `static_cast`
`static_cast` 用于执行显式类型转换，但它在编译时执行检查。常用于以下几种情况：

- **基本数据类型之间的转换**：如 `int` 到 `double`、`float` 到 `int` 等。
- **指针或引用类型之间的转换**：如将 `void*` 转换为具体类型的指针。
- **子类和基类之间的转换**：如将基类指针或引用转换为子类指针或引用。

```cpp
int main() {
    int a = 10;
    double b = static_cast<double>(a); // int 转 double
    std::cout << b << std::endl;

    void* p = &a;
    int* ip = static_cast<int*>(p); // void* 转 int*
    std::cout << *ip << std::endl;

    return 0;
}
```

### 2. `dynamic_cast`
`dynamic_cast` 主要用于多态类型（带有虚函数的类层次结构）之间的指针或引用转换。它可以在运行时检查转换是否安全，适合于从基类指针或引用向下转换为派生类指针或引用。如果转换失败，会返回 `nullptr`（对于指针）或抛出 `bad_cast` 异常（对于引用）。

```cpp
class Base {
    virtual void func() {} // 必须有虚函数
};

class Derived : public Base {
};

int main() {
    Base* base = new Derived();
    Derived* derived = dynamic_cast<Derived*>(base); // 安全转换，成功
    if (derived) {
        std::cout << "Cast successful" << std::endl;
    }

    Base* base2 = new Base();
    Derived* derived2 = dynamic_cast<Derived*>(base2); // 转换失败
    if (!derived2) {
        std::cout << "Cast failed" << std::endl;
    }

    delete base;
    delete base2;

    return 0;
}
```

### 3. `const_cast`
`const_cast` 主要用于在同类型的 `const` 和 `non-const` 对象之间进行转换。它只能移除或添加 `const` 和 `volatile` 修饰符，通常用于需要在某些函数内修改常量值的场景。

```cpp
void func(const int* p) {
    int* modifiable = const_cast<int*>(p); // 移除 const 属性
    *modifiable = 20; // 修改值
}

int main() {
    const int a = 10;
    func(&a); // 虽然不推荐，但这是 const_cast 的用途之一
    std::cout << a << std::endl; // a 的值在未定义行为的情况下可能会改变

    return 0;
}
```

### 4. `reinterpret_cast`
`reinterpret_cast` 是一种非常危险的类型转换，允许在几乎所有类型之间进行转换，包括不相关类型的指针、整数与指针之间的转换。它不会进行任何检查或处理，只是单纯地重解释位模式。它通常用于底层的硬件接口编程或需要强制转换类型的特殊场景。

```cpp
int main() {
    int a = 65;
    char* p = reinterpret_cast<char*>(&a); // int* 转 char*
    std::cout << *p << std::endl; // 打印字符 'A'

    int b = reinterpret_cast<int>(p); // char* 转 int
    std::cout << b << std::endl; // 打印指针值（通常为内存地址）

    return 0;
}
```

### 5. C 风格类型转换
C 风格的类型转换直接使用括号语法进行，如 `(Type)expression`。这种转换不区分 `static_cast`、`dynamic_cast`、`const_cast` 和 `reinterpret_cast`，因此更不安全，容易引发未定义行为。C++ 强烈建议使用上面的 C++ 风格转换。

```cpp
int main() {
    int a = 10;
    double b = (double)a; // C 风格的强制转换
    std::cout << b << std::endl;

    return 0;
}
```

### 总结
- `static_cast` 用于大部分类型安全的转换，适用于普通的基础类型转换和继承结构中向上和向下转换。
- `dynamic_cast` 用于在多态类型中进行安全的向下转换。
- `const_cast` 用于在 `const` 和 `non-const` 类型之间进行转换。
- `reinterpret_cast` 用于进行不安全的低级别转换。
- C 风格转换虽然方便但不建议使用，因为它不具备类型安全性。

了解这些转换的适用场景和限制，对于编写安全可靠的 C++ 程序非常重要。