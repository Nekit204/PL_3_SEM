#include<string>
#include<stack>
#include<fstream>
#include<iostream>
#include"/Users/User/Desktop/учеба/2 курс/ЯП/Лабораторные/Лабораторная работа 14/LP_Lab14/LP_Lab14/Lt.h"
using namespace std;
int prioritet(char l) 
{
	if (l == ')' || l == '(')
		return 0;
	if (l == ',')
		return 1;
	if (l == '+' || l == '-')
		return 2;
	if (l == '*' || l == '/')
		return 3;
	if (l == '[' || l == ']')
		return 4;
}
bool PolishNotation(string str)
{
	stack<char>stck;
		char outstr[255] = "";
		int length = str.length();
		char now, operand, next;
		int i;
		int lenout = 0;
		int func;
		int pr, operation;
		char opforstr;
		int count = 0;
		int count2 = 0;
		int ignor = 0;
		int ignor2 = 0;
		for (i = 0; i < str.length(); i++)
		{
			now = str[i];
			next = str[i + 1];
			if (now == LEX_RIGHTHESIS)
			{
				ignor--;
				while (stck.top() != '(')
				{
					outstr[lenout] = stck.top();
					lenout++;
					stck.pop();
				}
				stck.pop();
			}
			if (now == LEX_LEFTHESIS)
			{
				ignor++;
				stck.push(now);
			}
			if (now == '+' || now == '-' || now == '/' || now == '*')
			{
				if (!stck.size())
					stck.push(now);
				else
				{
				   operation = stck.top();
				   pr = prioritet(operation);
				if (prioritet(now) > pr||pr==4)
						stck.push(now);
					else
				{
						
							while (stck.size() && prioritet(now) <= prioritet(operation))
							{
								opforstr = operation;
								outstr[lenout] = opforstr;
								stck.pop();
								lenout++;
								if (stck.size())
								{
									operation = stck.top();
								}
							}
							stck.push(now);
				}
			}
		}
			if (now == '[')
			{
				ignor++;
				stck.push(now);
			}
			if (now == ',')
			{
				
				count2++;
				if (count2 == 1)
				{
					count += 2;
				
				}
				else if (count2 > 1)
				{
					count++;
					
				}
				operation = stck.top();
				if(operation=='+'||operation=='-'||operation=='*'||operation=='/')
				while (stck.size() && prioritet(now) < prioritet(operation)&&prioritet(operation)!=4)
				{
					opforstr = operation;
					outstr[lenout] = opforstr;
					stck.pop();
					lenout++;
					if (stck.size())
					{
						operation = stck.top();
					}
				}
			}
			if (now == ']')
			{
				ignor--;
				stck.pop();
				outstr[lenout] = '@';
				lenout++;
				operand = count+48;
				outstr[lenout] = operand;
				lenout++;
				count = 0;
				count2 = 0;
			}
			if (now == 'i' || now == 'l')
			{
				outstr[lenout] = now;
				lenout++;
			}
			now = NULL;


		}
		while (stck.size())
		{
			outstr[lenout++] = stck.top();
			stck.pop();
		}
		cout << outstr;
		if (ignor==0)
		{
			return true;
		}
		else
		{
			return false;
		}
		
}