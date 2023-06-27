#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// 如下两个函数几乎是相同的，唯一的差异是参数的类型，函数体则是完全一样的
// int compare(const string& v1,const string& v2)
// {
//     if(v1<v2)return -1;
//     else if(v1>v2)return 1;
//     else return 0;
// }

// int compare(const double& v1, const double& v2)
// {
//     if(v1<v2)return -1;
//     else if(v1>v2)return 1;
//     else return 0;
// }

// 使用通用函数模板
// template <typename T>
// int compare(const T& v1, const T& v2)
// {
//     if(v1<v2)return -1;
//     else if(v1>v2)return 1;
//     else return 0;
// }

template<unsigned N, unsigned M>
int compare(const char (&p1)[N],const char (&p2)[M])
{
    return strcmp(p1,p2);
}

template<typename T>
int compare(const T& v1, const T& v2)
{
    if(less<T>()(v1,v2))return -1;
    if(less<T>()(v2,v1))return 1;
    return 0;
}

int main()
{
    cout<<compare(1,2)<<endl;
    cout<<compare(2,1)<<endl;
    cout<<compare(6.6,7.7)<<endl;
    cout<<compare(7.7,6.6)<<endl;
    cout<<compare("hi","mom")<<endl;
    return 0;
 }