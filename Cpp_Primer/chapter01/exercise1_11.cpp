#include <iostream>
using namespace std;

int main()
{
    int a,b;
    cout<<"please input two num:"<<endl;
    cin>>a>>b;
    // ��С�����ӡ
    if(a<b){
        while(a<=b){
            cout<<a++<<" ";
        }
        cout<<endl;
    }
    // �ɴ�С��ӡ
    else{
        while(a>=b){
            cout<<a--<<" ";
        }
        cout<<endl;
    }
    return 0;
}