#pragma once
#include "Utils.h"

void	Run();

int		Select();
void	PrintMenu();

void	add_line			(Plane& plane);
void	search_point		(Plane& plane);
void	search_parallel		(Plane& plane);
void	search_equal		(Plane& plane);
void	load_plane			(Plane& plane);
void	clear_plane			(Plane& plane);
void	print_plane			(Plane& plane);

static std::string menu_exit("0 - �����");
static std::string please_input("--> ");
static std::string differ("_____________________________________________________");

static std::string main_menu("\t- Main menu - ");
static std::string sub_menu("\t- Sub menu - ");

static std::string main_menu1("1 - �������� ������");
static std::string main_menu2("2 - ����� ����� ����������� ����. ����� ������");
static std::string main_menu3("3 - ������, ���� �� ������������ ������");
static std::string main_menu4("4 - ������, ���� �� ����������� ������");
static std::string main_menu5("5 - ����������� ������ ���������");
static std::string main_menu6("6 - ��������� ������ � ������ �� �����");
static std::string main_menu7("7 - �������� ���������");
static const int max_menu_item = 7;

