#include "Utils.h"
#include <iostream>

using namespace std;

double InputReal(string message)
{
	string s;
	bool isOkNumber = true;
	int cnt;
	if (message != "")
		Write(message);
	Write("в качестве разделите вещественной и дробной части используйте ,");
	do {
		if (!isOkNumber)
			Write("Некорректная строка, повторите ввод. Используйте , для разделения");
		cout << "--> ";
		getline(cin, s);
		Trim(s);
		cnt = 0;
		isOkNumber = s.begin() != s.end() && (*s.begin() == '+' || *s.begin() == '-' || *s.begin() >= '0' && *s.begin() <= '9');
		if (*s.begin() == ',') {
			isOkNumber = true;
			++cnt;
		}
		for (string::iterator i = ++s.begin(); i != s.end() && isOkNumber; ++i)
		{
			isOkNumber = (*i >= '0' && *i <= '9') || *i == ',';
			if (*i == ',')
				++cnt;
			isOkNumber &= cnt <= 1;
		}		
	} while (!isOkNumber);
	
	return stod(s);
} // inputReal

int InputInt(string message)
{
	char s[max_size];
	char *str;
	bool isOkNumber = true;
	int res;
	if (message != "")
		Write(message);
	do {
		if (!isOkNumber)
			cout << "bad input, try again!" << endl;
		cout << "--> ";

		cin.getline(s, max_size);
		isOkNumber = true;
		s[max_size - 1] = '\0';

		str = s;
		if (s[0] == '-' || s[0] == '+')
			str++;
		if (*str == '\0')
			isOkNumber = false;
		for (; *str != '\0' && isOkNumber; str++)
			isOkNumber = isOkNumber && (*str >= '0' && *str <= '9');
	} while (!isOkNumber);
	res = atoi(s);
	return res;
}

Line InputLine(std::string message)
{
	Write("Введите коэффициенты прямой ax + by + c = 0");
	double a = InputReal("Введите коэффициент A");
	double b = InputReal("Введите коэффициент B");
	double c = InputReal("Введите коэффициент C");	
	if (a == 0 && b == 0 && c == 0)
		throw exception("Введены координаты плоскости, невозможно инициализировать прямую\r\n");
	return Line(a, b, c);
}


void Write(string str, int count) 
{
	cout << str;
	for (int i = 0; i < count; ++i)
		cout << std::endl;
}


void Trim(std::string &str)
{
	const auto strBegin = str.find_first_not_of(" \t");
	if (strBegin != std::string::npos) {
		const auto strEnd = str.find_last_not_of(" \t");
		const auto strRange = strEnd - strBegin + 1;
		str = str.substr(strBegin, strRange);
	}
	else
		return;

	std::string result = "";	
	for (unsigned int i = 0; i < str.length(); i++)
		result += static_cast<unsigned char>(str.at(i));

	str = result;
}

void DelSpaces(std::string &str)
{
	std::string result = "";
	Trim(str);
	unsigned i = 0;
	while (i < str.length()) {
		while (str[i] != ' ' && i < str.length()) {
			result.push_back(str[i]);
			i++;
		}
		if (str[i] == ' ' && i < str.length())
			result.push_back(' ');
		while (str[i] == ' ' && i < str.length())
			i++;
	} // while
	str = result;
}

bool yes_or_no(string message)
{
	cout << message << endl;
	cout << "1 - yes, 0 - no" << endl << endl;
	int k;
	bool errorInput = false;
	do {
		if (errorInput)
			cout << "Некорректный ввод, повторите!" << endl;
		k = InputInt();
		errorInput = k < 0 || k > 1;
	} while (errorInput);
	return k == 1;
}
