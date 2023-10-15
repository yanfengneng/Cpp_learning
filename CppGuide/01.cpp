#include <iostream>
using namespace std;

class Rectangle
{
public:
    int length;
    int breadth;
    
    /* 成员函数声明 */
    void setLength(int l);
    void setBreadth(int b);
    int getArea();
};

/* 定义成员函数 */
void Rectangle::setLength(int l){
    length = l; 
}

void Rectangle::setBreadth(int b){
    breadth = b;
}

int Rectangle::getArea(){
    return length * breadth;
}

int main()
{
    Rectangle rt;
    rt.setLength(7);
    rt.setBreadth(4);
    int area = rt.getArea();
    cout << "Area : " << area << endl;
    return 0;
}