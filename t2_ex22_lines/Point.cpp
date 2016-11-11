#include "Point.h"
#include <iostream>

using namespace std;

Point::Point(): _x(HUGE_VAL), _y(HUGE_VAL) { }

Point::Point(double x, double y): _x(x), _y(y) { }

Point::Point(const Point & point): _x(point._x), _y(point._y) { }

Point::~Point() { }

std::string Point::point_to_string() const
{
	return '(' + to_string(_x) + " , " + to_string(_y) + ')';
}

void Point::print() const
{
	cout << '(' << _x << " ; " << _y << ')' << endl;
}

bool Point::is_infty() const
{
	return _x == HUGE_VAL && _y == HUGE_VAL;
}

bool Point::operator==(const Point & other) const
{
	return _x == other._x && _y == other._y;
}
