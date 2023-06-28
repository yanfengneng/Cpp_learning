#include <iostream>
#include <tuple>
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    tuple<int,int,int> t1{10,20,30};
    tuple<string, vector<string>,pair<string,int>> t2("constants", {"a", "bb"}, {"ccc", 3});
    
    cout<<get<0>(t1)<<" "<<get<1>(t1)<<" "<<get<2>(t1)<<endl;
    //cout<<get<0>(t2)<<" "<<get<1>(t2)<<" "<<get<2>(t2)<<endl;
    return 0;
}