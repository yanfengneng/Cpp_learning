#include <bits/stdc++.h>
using namespace std;

void test_cin_cout()
{
    int x;cin>>x;
    cout<<x<<endl;
}

void test_cout_size()
{
    ofstream of("test.txt");// �����ļ� test.txt ����
    for(int i=0;i<4096;i++){
        of<<'a';
    }
    system("pause");// ��ͣ
    of<<'b';
    system("pause");// ��ͣ
}

int main()
{
    //test_cin_cout();
    test_cout_size();
    return 0;
}