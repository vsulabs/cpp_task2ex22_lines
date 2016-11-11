#include "Task.h"
#include <iostream>

using namespace std;

void Run()
{
	Plane plane;

	int menu_mark;
	do {
		PrintMenu();
		menu_mark = Select();

		switch (menu_mark)
		{
		case 1: // add
			add_line(plane);
			break;
		case 2: // search
			search_point(plane);
			break;
		case 3: // check parallel
			search_parallel(plane);
			break;
		case 4: // check equal
			search_equal(plane);
			break;
		case 5: // print
			print_plane(plane);
			break;
		case 6: // load
			load_plane(plane);
			break;
		case 7: // clear
			clear_plane(plane);
			break;
		} // switch

	} while (menu_mark != 0);
	Write("Программа завершила работу");
}

int Select()
{
	int k;
	bool errorInput = false;
	do {
		if (errorInput)
			Write("Некорректный ввод, повторите!");
		k = InputInt();
		errorInput = k < 0 || k > max_menu_item;
	} while (errorInput);
	cout << endl;
	return k;
}

void PrintMenu()
{
	Write(differ, 2);
	
	Write(main_menu);
	
	Write(main_menu1);
	Write(main_menu2);
	Write(main_menu3);
	Write(main_menu4);
	Write(main_menu5);
	Write(main_menu6);
	Write(main_menu7);
	Write(menu_exit);
}

void add_line(Plane & plane)
{
	try	{
		Line line = InputLine();
		plane.AddLine(line);		
	}
	catch(const exception& e) {
		cerr << e.what();
	}
}

void search_point(Plane & plane)
{
	set<Point*> points = Plane::calc_must_cross(plane);
	if (points.size() == 0) {
		Write("Точки пересечения нет");
		return;
	}
	for (auto point: points)
		point->print();
	while (points.size() > 0) {
		delete *points.begin();
		points.erase(points.begin());
	}
}

void search_parallel(Plane & plane)
{
	if (Plane::plane_with_parallel_lines(plane))
		Write("Плоскость имеет параллельные прямые");
	else
		Write("Плоскость не имеет параллельных прямых");
}

void search_equal(Plane & plane)
{
	if (Plane::plane_with_equal_lines(plane))
		Write("Плоскость имеет совпадающие прямые");
	else
		Write("Плоскость не имеет совпадающих прямых");
}

void load_plane(Plane & plane)
{
	if (plane.isEmpty() && plane.load_from_file()) {
		Write("Данные были успешно загружены");
		return;
	}	
	if (yes_or_no("Вы уверены, что хотите заменить старые данные новыми из файла?") && plane.load_from_file())
		Write("Данные были успешно загружены");
	else
		Write("Загрузка данных не произведена");
	if (yes_or_no("Распечатать загруженные прямые?"))
		plane.print();
}

void clear_plane(Plane & plane)
{
	if (plane.isEmpty()) {
		Write("Список пуст");
		return;
	}
	if (yes_or_no("Вы уверены, что хотите удалить данные?")) {
		plane.clear();
		Write("Список очищен");
		return;
	}
	Write("Очистка данных отменена, плоскость хранит прежние прямые");
}

void print_plane(Plane & plane)
{
	if (plane.isEmpty()) {
		Write("Список пуст");
		return;
	}
	plane.print();
}
