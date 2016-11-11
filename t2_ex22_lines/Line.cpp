#include "Line.h"
#include <iostream>

using namespace std;

Line::Line(double a, double b, double c) : _a(a), _b(b), _c(c) {
	if (_a == 0 && _b == 0)
		throw exception("заданы координаты плоскости");
}

Line::Line(Point begin, Point end)
{
	if (begin == end)
		throw exception("Заданы совпадающие точки, нельзя провести прямую");
	_a = end.y() - begin.y();
	_b = -(end.x() - begin.x());
	_c = begin.y() * (end.x() - begin.x()) - begin.x() * (end.y() - begin.y());
}

Line::Line(const Line & line): _a(line._a), _b(line._b), _c(line._c) { }

Line::~Line() { }

Point Line::cross_in(const Line & one, const Line & two)
{
	double denum = det(one._a, one._b, two._a, two._b);
	if (abs(denum) < eps)
		return Point(HUGE_VAL, HUGE_VAL);
	double x = - det(one._c, one._b, two._c, two._b) / denum;
	double y = - det(one._a, one._c, two._a, two._c) / denum;
	return Point(x, y);
}

void Line::print() const
{
	cout << '(' << _a << ")*x + (" << _b << ")*y + (" << _c << ") = 0" << endl;
}

bool Line::operator==(const Line& other) const
{
	return _a == other._a && _b == other._b && _c == other._c;
}

bool Line::parallel_lines(const Line& one, const Line& two)
{
	return abs(det(one._a, one._b, two._a, two._b)) < eps;
}

bool Line::equal_lines(const Line& one, const Line& two)
{
	/*
	return
		abs(det(one._a, one._b, two._a, two._b)) < eps &&
		abs((two._a / one._a) * one._c - two._c) < eps;
		*/
	return
		abs(det(one._a, one._b, two._a, two._b)) < eps && (
		abs((two._a / one._a) * one._c - two._c) < eps ||
		abs((two._b / one._b) * one._c - two._c) < eps);
}

double Line::det(double a, double b, double c, double d)
{
	return a * d - b * c;
}
