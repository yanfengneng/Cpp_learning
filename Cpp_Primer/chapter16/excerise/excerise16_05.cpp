#include <iostream>
#include <string>
using namespace std;

// C���԰汾��T ��ʾ���Ͳ�����N ��ʾ�����С
template <typename T, size_t N>
void print(const T (&a)[N])
{
    for(auto iter = begin(a); iter != end(a); iter++){
        cout<<*iter<<" ";
    }
    cout<<endl;
}

// C++�汾
template<typename Array>
void print(const Array& a)
{
    for(const auto& i:a)cout<<i<<" ";
    cout<<endl;
}

int main()
{
    int a[6]{0,2,4,6,8,10};
    string vs[3]{"hello","world","!"};

    print(a);
    print(vs);

    return 0;
}