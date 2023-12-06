#include <iostream>

using namespace std;

class coordinate
{
public:
	coordinate():x(0), y(0) { }
	coordinate(int x0, int y0);
	
	void print(void);

	// 友元函数
	friend coordinate operator+(const coordinate& a, const coordinate& b);
private:
    int x;					// x轴坐标
	int y;					// y轴坐标
};

coordinate::coordinate(int x0, int y0)
{
	x = x0;
	y = y0;
};

void coordinate::print()
{
	cout << "(" << this->x << ", " << this->y << ")" << endl;
}

// 用独立函数来实现+的运算符重载
coordinate operator+(const coordinate& a, const coordinate& b)
{
	coordinate tmp;
	
	tmp.x = a.x + b.x;
	tmp.y = a.y + b.y;
	
	return tmp;
}


int main()
{
	coordinate a(1, 3);
	coordinate b(2, 4);
	coordinate c;
	
	c = a + b;	// 相当于是 c = operator+(a, b);
	
	a.print();
	b.print();
	c.print();

	return 0;
}