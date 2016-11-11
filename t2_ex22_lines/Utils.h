#pragma once

#include "Plane.h";

static const int max_size = 256;

double			InputReal(std::string message = "");
int				InputInt(std::string message = "");
Line			InputLine(std::string message = "");

void			Trim(std::string &str);
void			DelSpaces(std::string &str);

void			Write(std::string str, int count = 1);
bool			yes_or_no(std::string message);

