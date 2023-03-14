#include <iostream>
using namespace std;

int main()
{
    int a,b;
    cout<<"please input two num:"<<endl;
    cin>>a>>b;
    // 由小到大打印
    if(a<b){
        while(a<=b){
            cout<<a++<<" ";
        }
        cout<<endl;
    }
    // 由大到小打印
    else{
        while(a>=b){
            cout<<a--<<" ";
        }
        cout<<endl;
    }
    return 0;
}