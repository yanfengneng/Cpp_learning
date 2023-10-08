#include <iostream>
using namespace std;

int main()
{
    int sum=0,val=0;
    cout<<"请输入一些数，按 Ctrl+Z 表示结束：";
    for(;cin>>val;){
        sum+=val;
    }
    cout<<"读入数之和为："<<sum<<endl;
    return 0;
}