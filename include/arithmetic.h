// Объявление функций и классов для вычисления арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__
#include "stack.h"
#include <string>
#include "cstdlib"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
class Lexem {
public:
	string a;
	string* MyLexema;
	string Polskastring;
	int* Prior;
	int Size;
	double r=0.0;
	bool POINT = false;
	TStack <char> Str1;//операнд
	TStack <char> Str2;//оператор
	Lexem(string s="0");
	~Lexem();
	void GetString(string s);//Получение следующей строки
	void Preparestr();//избавление от лишних пробелов в строке
	void Divide();//разбиение на массив лексем
	bool CheckSkobka();//проверка на открытые/закрытые скобки
	bool CheckTochkadrob();//проверка на точки в числах double;
	bool CheckPeremenpodr();//проверка переменных подряд
	bool CheckFunc();//проверка функций
	bool CheckZnakiSkobki();//проверка двух знаков перед скобкой (, знак перед )
	bool CheckALL();
	int PRIOR(string s)
	{
		if (s == "(") { return (0); }
		if (s == "+") { return (1); }
		if (s == "-") { return (1); }
		if (s == "*") { return (2); }
		if (s == "/") { return (2); }
		if (s == "^") { return (3); }
		if (s == "sin") { return (4); }
		if (s == "cos") { return(4); }
		if (s == "sqrt") { return(4); }
	}
	void PolskaZapis();
	double Convert_str_to_double(string s);
	double CALC();

};
#endif