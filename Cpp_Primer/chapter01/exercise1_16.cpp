#include <iostream>
using namespace std;

int main()
{
    int sum=0,val=0;
    cout<<"������һЩ������ Ctrl+Z ��ʾ������";
    for(;cin>>val;){
        sum+=val;
    }
    cout<<"������֮��Ϊ��"<<sum<<endl;
    return 0;
}