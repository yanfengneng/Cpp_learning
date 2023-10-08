#include <iostream>
using namespace std;

int main()
{
    int sum=0,i=50;
    while(i<=100){
        sum+=i++;
    }
    cout<<sum<<endl;
    return 0;
}