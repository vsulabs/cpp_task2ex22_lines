#pragma once
#include <string>

static const double eps = 1e-7;

class Point
{
	double _x;
	double _y;
public:
	Point();
	Point(double x, double y);
	Point(const Point& point);
	~Point();

	double x() const	{ return _x; }
	double y() const	{ return _y; }
	
	std::string		point_to_string()	const;
	void			print()				const;
	bool			is_infty()			const;
	bool operator==(const Point& other) const;
};

