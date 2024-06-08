#include <bits/stdc++.h>
using namespace std;

class Foo {
public:
    Foo() { std::cout << "Foo()" << std::endl; }
    virtual ~Foo() { std::cout << "~Foo()" << std::endl; }

    void* operator new(std::size_t size)
    {
        std::cout << "operator new" << std::endl;
        return std::malloc(size);
    }

    void* operator new(std::size_t size, int num)
    {
        std::cout << "operator new" << std::endl;
        std::cout << "num is " << num << std::endl;
        return std::malloc(size);
    }

    void* operator new (std::size_t size, void* p)
    {
        std::cout << "placement new" << std::endl;
        return p;
    }

    void operator delete(void* ptr)
    {
        std::cout << "operator delete" << std::endl;
        std::free(ptr);
    }
};

int main()
{
    Foo* m = new(100) Foo;
    Foo* m2 = new(m) Foo;
    std::cout << sizeof(m) << std::endl;
    // delete m2;
    delete m;
    return 0;
}