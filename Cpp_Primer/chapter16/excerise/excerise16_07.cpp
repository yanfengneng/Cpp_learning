#include <iostream>
#include <string>
using namespace std;

template <typename T, size_t N>
constexpr int arr_size(const T (&a)[N])
{
    return N;
}

template <typename T, size_t N>
void print(const T (&a)[N])
{
    for(int i=0;i<arr_size(a);++i){
        cout<<a[i]<<" ";
    }
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