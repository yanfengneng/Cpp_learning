#include <bits/stdc++.h>
using namespace std;

void test_cin_cout()
{
    int x;cin>>x;
    cout<<x<<endl;
}

void test_cout_size()
{
    ofstream of("test.txt");// 创建文件 test.txt 并打开
    for(int i=0;i<4096;i++){
        of<<'a';
    }
    system("pause");// 暂停
    of<<'b';
    system("pause");// 暂停
}

int main()
{
    //test_cin_cout();
    test_cout_size();
    return 0;
}