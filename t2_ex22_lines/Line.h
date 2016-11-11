#pragma once
#include "Point.h"

class Line
{
	double _a, _b, _c;
public:
	Line(double a, double b, double c);
	Line(Point begin, Point end);
	Line(const Line& line);
	~Line();
	
	void print() const;
	bool operator ==(const Line& other) const;

	static Point cross_in(const Line& one, const Line& two);
	static bool parallel_lines(const Line& one, const Line& two);
	static bool equal_lines(const Line& one, const Line& two);
	static inline double det(double a, double b, double c, double d);
};
