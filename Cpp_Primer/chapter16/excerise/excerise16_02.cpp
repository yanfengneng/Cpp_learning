#include <iostream>
using namespace std;

template <typename T>
int compare(const T& a,const T& b)
{
    return a<b?-1:a>b?1:0;
}

int main()
{
    cout<<compare(1,2)<<endl;
    cout<<compare(2,1)<<endl;
    cout<<compare(6.6,7.7)<<endl;
    cout<<compare(7.7,6.6)<<endl;
    return 0;
}