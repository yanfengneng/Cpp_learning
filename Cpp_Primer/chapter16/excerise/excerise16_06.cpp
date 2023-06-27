#include <iostream>
#include <string>
using namespace std;

// ǰ������
template <typename T, size_t N>
const T* my_begin(const T(&a)[N]);

template <typename T, size_t N>
const T* my_end(const T (&a)[N]);

// C���԰汾��T ��ʾ���Ͳ�����N ��ʾ�����С
template <typename T, size_t N>
void print(const T (&a)[N])
{
    for(auto iter = my_begin(a); iter != my_end(a); iter++){
        cout<<*iter<<" ";
    }
    cout<<endl;
}

template <typename T, size_t N>
const T* my_begin(const T(&a)[N])
{
    return &a[0];
}

template <typename T, size_t N>
const T* my_end(const T (&a)[N])
{
    return &a[0]+N;
}

int main()
{
    int a[6]{0,2,4,6,8,10};
    string vs[3]{"hello","world","!"};

    print(a);
    print(vs);

    return 0;
}