#include <iostream>
#include<locale>
#include<string.h>
#include <string>
#include <tchar.h>
#include<fstream>
#include"/Users/User/Desktop/учеба/2 курс/ЯП/Лабораторные/Лабораторная работа 14/LP_Lab14/LP_Lab14/Lt.h"
using namespace std;
int _tmain(int argc,_TCHAR *argv[])
{
	setlocale(LC_ALL, "Russian");
	string str;
	ifstream file("in.txt");
	if (!file)
	{
		cout << "Файл не открыт\n\n";
		return -1;
	}
	bool PolishNotation(string str);
	int strin = 0;
	while (!file.eof())
	{
		bool flagok = false;
		bool skob = false;
		getline(file, str);
		strin++;
		if (str == "")
		{
			cout << "Пустая строка." << endl;
			return 0;
		}
		for (int l = 0; l < str.length(); l++)
		{
			if ((str[l] == '+' || str[l] == '-' || str[l] == '*' || str[l] == '/') && (str[l + 1] == '+' || str[l + 1] == '-' || str[l + 1] == '*' || str[l + 1] == '/'||str[l+1]==')'||str[l+1]==']'))
			{
				cout <<"Строка:"<<strin<<"-ошибка:два знака операции подряд или закрывающая скобка и знак операции" << endl;
				flagok = true;
				break;
			}	
			if ((str[0] == '+' || str[0] == '-' || str[0] == '/' || str[0] == '*'))
			{
				cout << "Строка:" << strin << "-ошибка:строка не должна начинаться со знака операции" << endl;
				flagok = true;
				break;
			}
			if (str[l] == '(')
			{
				skob = true;
			}
			if (str[l] == ')' && skob)
			{
				continue;
			}
			else if(str[l] == ')' && !skob)
			{
				cout << "Строка:" << strin << "-ошибка:неправильный порядок следования скобок" << endl;
				flagok = true;
				break;
				
			}
			if ((str[l] == 'i' || str[l] == 'l') && (str[l + 1] == 'i' || str[l + 1] == 'l'))
			{
				cout << "Строка:" << strin << "-ошибка:два операнда подряд " << endl;
				flagok = true;
				break;
			}
			if (str[l] != 'i' && str[l] != 'l' && str[l] != '+' && str[l] != '*' && str[l] != '-' && str[l] != '/' && str[l] != '[' && str[l] != ']' && str[l] != '(' && str[l] != ')' && str[l] != ',')
			{
				cout << "Строка:" << strin << "-ошибка:недопустимый символ" << endl;
				flagok = true;
				break;
			}
		}
		if (flagok)
		{
			continue;
		}
		
			if (PolishNotation(str))
			{
				cout << "   (выражение преобразовано.)" << endl;

			}
			else
			{
				cout << "  (выражение не было преобразовано.)" << endl;
			}
		
			
	}
}
