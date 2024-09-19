#include <bits/stdc++.h>
using namespace std;

int main()
{
    unique_ptr<int[]> array(new int[5]);
    for(auto a : array){
        cout << a << endl;
    }
    return 0;
}