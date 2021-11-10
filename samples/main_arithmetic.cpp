// реализация пользовательского приложения
#include "stack.h"
#include "..\include\arithmetic.h"
#include <iostream>
#include <iomanip>


int main() {
	Lexem L("sqrt(sin((cos(0)^2)))");//(5 - 1) + cos(4) - sqrt(2) + sin(4) / cos(5) + -5 + 231.000543
	L.Preparestr();
	L.Divide();
	for (int i = 0; i < L.Size; i++)
	{
		cout<<L.MyLexema[i]<<"_["<<i<<"]_Prior = "<<L.Prior[i] << "\n";
		
	}
	if (L.CheckSkobka()) { cout << "OK SKOB" << endl; }
	else cout << "NOT OK SKOB" << endl;

	if (L.CheckTochkadrob()) { cout << "OK TOCHKA" << endl; }
	else cout << "NOT OK TOCHKA" << endl;

	if (L.CheckPeremenpodr()) { cout << "OK PEREM" << endl; }
	else cout << "NOT OK PEREM" << endl;

	if (L.CheckFunc()) { cout << "OK FUNC" << endl; }
	else cout << "NOT OK FUNC" << endl;

	if (L.CheckZnakiSkobki()) { cout << "OK ZNAKI" << endl; }
	else cout << "NOT OK ZNAKI" << endl;

	if (L.CheckALL()) { cout << "OK" << endl; }
	else cout << "NOT OK" << endl;
	
	L.PolskaZapis();
	
	for (int i = 0; i < L.Size-5; i++)
	{
		cout << L.MyLexema[i];

	}
	cout << endl;
	
	cout<<L.CALC()<<endl;
	
	return 0;
}