#include <iostream>
using namespace std;
 
class A
{
private:
	int x, y;
public:
	A(int x1 = 0, int y1 = 0)
	{
		x = x1;
		y = y1;
	}
	A operator+(const A& a)const
	{
		A t;
		t.x = this->x + a.x;
		t.y = this->y + a.y;
		return t;
	}
	void show()
	{
		cout << "x=" << x << "," << "y=" << y << endl;
	}
};
int main()
{
	A a1(1, 2);
	A a2(3, 4);
	A a;
	a = a1 + a2;
	a.show();
}