#include <bits/stdc++.h>
using namespace std;

class Vec2D {
private:
	double x_;
	double y_;

public:
	Vec2D(double x, double y) :x_(x), y_(y) {}
	Vec2D() { x_ = 0.0; y_ = 0.0; }
	
	std::string toString();
	
	friend Vec2D operator+(const Vec2D& v1, const Vec2D& v2);
	friend Vec2D operator-(const Vec2D& v1, const Vec2D& v2);
	friend double operator*(const Vec2D& v1, const Vec2D& v2);
	friend Vec2D operator+(const Vec2D& v1, double num);
	friend Vec2D operator*(const double num, const Vec2D& v2);
	friend Vec2D operator*(const Vec2D& v2, const double num);
	friend istream& operator>>(istream& stream, Vec2D& v1);
	friend std::ostream& operator<<(std::ostream& stream, const Vec2D& v1);

	Vec2D negative();

	Vec2D operator-();

	Vec2D operator++();
	Vec2D operator++(int dummy);

	Vec2D operator--();

	Vec2D operator+=(const Vec2D& v);
	Vec2D operator-=(const Vec2D& v);

	double& operator[](const int& index);

	double magnitude();
	double direction();
	int compareTo(Vec2D& v2);

	operator double();

	double getX()const { return x_; }
	double getY() const { return y_; }
	void setX(double x) { x_ = x; }
	void setY(double y) { y_ = y; }
};

std::string Vec2D::toString()
{
	std::string res = "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
	return res;
}

Vec2D Vec2D::negative()
{
	return Vec2D(-1 * x_, -1 * y_);
}

Vec2D Vec2D::operator-()
{
	return Vec2D(-1 * x_, -1 * y_);
}

Vec2D Vec2D::operator++()
{
	x_++;
	y_++;
	return *this;
}

Vec2D Vec2D::operator++(int dummy)
{
	Vec2D ret(x_, y_);
	x_++;
	y_++;
	return ret;
}

Vec2D Vec2D::operator--()
{
	x_ -= 1;
	y_ -= 1;
	return *this;
}

Vec2D Vec2D::operator+=(const Vec2D& v)
{
	x_ += v.x_;
	y_ += v.y_;
	return *this;
}

Vec2D Vec2D::operator-=(const Vec2D& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	return *this;
}

double& Vec2D::operator[](const int& index)
{
	if (index == 0) {
		return x_;
	}
	else if (index == 1) {
		return y_;
	}
	else {
		printf("subscript error\n");
		exit(0);
	}
}

Vec2D operator+(const Vec2D& v1, const Vec2D& v2) {
	Vec2D ret;

	ret.setX(v1.getX() + v2.getX());
	ret.setY(v1.getY() + v2.getY());

	return ret;
}

Vec2D operator+(const Vec2D& v1, double num) {
	Vec2D ret;

	ret.setX(v1.getX() + num);
	ret.setY(v1.getY() + num);

	return ret;
}

Vec2D operator*(const double num, const Vec2D& v2) {
	Vec2D ret;

	ret.setX(num * v2.getX());
	ret.setY(num * v2.getY());

	return ret;
}

istream& operator>>(istream& stream, Vec2D& v1)
{
	double x, y;
	stream >> x >> y;
	v1.setX(x);
	v1.setY(y);
	// 也可以直接
	// stream >> x_ >> y_;
	return stream;
}

ostream& operator<<(ostream& stream, const Vec2D& v1)
{
	std::string res = "(" + std::to_string(v1.getX()) + ", " + std::to_string(v1.getY()) + ")";
	stream << res;

	return stream;
}


int main()
{

}