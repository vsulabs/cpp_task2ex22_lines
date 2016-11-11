#pragma once

#include <map>
#include "Line.h"
#include <set>

typedef std::pair<double, double> simple_point;

class Plane {
	std::map<Line*, int> lines;
	
	std::string filename = "src/plane.txt";
public:
	Plane();
	~Plane();

	void AddLine(const Line& line);
	
	bool load_from_file();
	void clear();
	bool isEmpty()	const;
	void print()	const;

	static std::set<Point*> calc_must_cross(const Plane& plane);
	static bool		plane_with_parallel_lines(const Plane& plane);
	static bool		plane_with_equal_lines(const Plane& plane);
};


