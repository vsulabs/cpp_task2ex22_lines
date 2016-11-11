#include "Plane.h"
#include <set>
#include <fstream>
#include <iostream>

using namespace std;

Plane::Plane() { }

Plane::~Plane() { clear(); }

void Plane::AddLine(const Line & line)
{	
	for (map<Line*, int>::iterator it = lines.begin(); it != lines.end(); ++it)
		if (Line::equal_lines(*(it->first), line)) {
			++it->second;
			return;
		}
	lines.insert(pair<Line*, int>(new Line(line), 1));
}

template <typename T1, typename T2>
struct left_more_by_second_param {
	typedef pair<T1, T2> type;
	bool operator() (type const& a, type const& b) const {
		return a.second > b.second;
	}
};

set<Point*> Plane::calc_must_cross(const Plane & plane)
{
	set<Point*> result;

	map<simple_point, int> crossed_points;
	set<simple_point> set_points;
	
	if (plane.lines.size() < 2)
		return result;
		
	for (map<Line*, int>::const_iterator i = plane.lines.begin(); i != --plane.lines.end(); ++i) {
		// с помощью множества запоминаем, какие точки уже проверялась для данной прямой на пересечение
		set_points = set<simple_point>(); 
		
		map<Line*, int>::const_iterator j = i;
		++j;
		for (; j != plane.lines.end(); ++j) {			
			Point p = Point(Line::cross_in(*(i->first), *(j->first)));
			simple_point tmp = simple_point(p.x(), p.y());
			if (p.x() != HUGE_VAL && p.y() != HUGE_VAL && set_points.find(tmp) == set_points.end()) {				
				crossed_points[simple_point(tmp)] += j->second;
				set_points.insert(simple_point(tmp));
			}
		}
	}

	set<simple_point> current_set;
	set_points = set<simple_point>();
	for (map<Line*, int>::const_iterator i = plane.lines.begin(); i != --plane.lines.end(); ++i) {
		map<Line*, int>::const_iterator j = i;
		++j;
		current_set = set<simple_point>();
		for (; j != plane.lines.end(); ++j) {
			Point p = Point(Line::cross_in(*(i->first), *(j->first)));
			simple_point tmp = simple_point(p.x(), p.y());
			if (p.x() != HUGE_VAL && p.y() != HUGE_VAL && set_points.find(tmp) == set_points.end()) {
				set_points.insert(simple_point(tmp));
				current_set.insert(simple_point(tmp));
			}
		}
		for (auto p : current_set) {
			crossed_points[p] += i->second;
		}
	}	

	map<simple_point, int>::iterator max_it = crossed_points.begin();
	if (max_it == crossed_points.end())
		return result;
		
	int max = max_it->second;
	for (map<simple_point, int>::iterator it = crossed_points.begin(); it != crossed_points.end(); ++it)
		if (it->second > max) {
			while (result.size() > 0) {
				delete *result.begin();
				result.erase(result.begin());
			}
			result.insert(new Point(it->first.first, it->first.second));
			max = it->second;
		}
		else if (it->second == max) {
			result.insert(new Point(it->first.first, it->first.second));
		}
	return result;	
}


bool Plane::plane_with_parallel_lines(const Plane & plane)
{	
	if (plane.lines.size() < 2)
		return false;
	if (plane_with_equal_lines(plane))
		return true;
	for (map<Line*, int>::const_iterator i = plane.lines.begin(); i != --plane.lines.end(); ++i) {
		map<Line*, int>::const_iterator j = i;
		++j;
		for (; j != plane.lines.end(); ++j)
			if (Line::parallel_lines(*i->first, *j->first))
				return true;
	}
	return false;
}

bool Plane::plane_with_equal_lines(const Plane & plane)
{
	for (auto it : plane.lines)
		if (it.second > 1)
			return true;
	return false;
	/*
	if (plane.lines.size() < 2)
		return false;
	for (map<Line*, int>::const_iterator i = plane.lines.begin(); i != --plane.lines.end(); ++i) {
		map<Line*, int>::const_iterator j = i;
		++j;
		for (; j != plane.lines.end(); ++j)
			if (Line::equal_lines(*i->first, *j->first))
				return true;		
	}
	return false;
	*/
}

bool Plane::load_from_file()
{
	ifstream infile;

	string s;
	string::size_type sz;
	
	clear();
	bool OkReading = true;
	infile.open(filename);

	while (!infile.eof() && OkReading) // To get you all the lines.
	{
		getline(infile, s); // Saves the line in tmp_string			
		double a = stod(s, &sz);
		s = s.substr(sz + 2);
		double b = stod(s, &sz);
		s = s.substr(sz + 2);
		double c = stod(s, &sz);
		try{
			AddLine(Line(a, b, c));
		}
		catch (const exception& e) {
			e.what();
		}
	}

	return true;
}

void Plane::clear()
{
	while (lines.size() > 0) {
		delete(lines.begin()->first);
		lines.erase(lines.begin());
	}	
}

bool Plane::isEmpty() const { return lines.size() == 0; }

void Plane::print() const
{
	for (auto i : lines) {
		cout << "x" << i.second << "\t" << "|" << "\t";
		(*(i.first)).print();		
	}
}
