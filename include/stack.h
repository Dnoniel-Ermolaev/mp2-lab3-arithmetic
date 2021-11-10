// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, INCLUDE+
// - извлечение элемента, EXCLUDE+
// - просмотр верхнего элемента (без удаления) GET+
// - проверка на пустоту, CheckEmpty+
// - проверка на полноту, CheckFULL+
// - получение количества элементов в стеке Count+
// - очистка стека Clean+
// при вставке в полный стек должна перевыделяться память Overflow+

#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include <vector>
using namespace std;

const int MAX_STACK_SIZE = 100000000;


template <class ValType>
class TStack
{
public:
	ValType* MyStack;
	int Size;       // Размер
	int Top;        // Индекс вершины
	TStack(int s);	                          //конструктор
	TStack(const TStack& v);         //конструктор копирования
	TStack();
	~TStack();                               //деструктор

	void Include(const ValType i);          //Вставка элемента
	ValType Exclude();                      //извлечение элемента
	ValType Get();                          //Просмотр верхнего элемента без удаления
	bool CheckFull() const;                 //Проверка на полноту
	bool CheckEmpty() const;                //Проверка на пустоту
	void OverFlow();						//Переполнение/перевыделение памяти
	int Count();							//Количество элементов в стеке
	void Clean();							//очистка элементов
	friend ostream& operator<<(ostream& out, const TStack& v)
	{
		for (int i = 0; i < v.Top + 1; i++)
			out << v.MyStack[i] << ' ';
		return out;
	}
};

template<class ValType>
TStack<ValType>::TStack()
{
	Top = -1;
	Size = 10000;
	MyStack = new ValType[Size];
}

template <class ValType>
TStack<ValType>::TStack(int s)
{
	if (s < 0)
		throw "Negative size";
	else if (s > MAX_STACK_SIZE)
		throw "Size more than MAX_VECTOR_SIZE";
	else
	{
		Top = -1;
		Size = s;
		MyStack = new ValType[Size];
	}
}

template <class ValType> 
TStack<ValType>::TStack(const TStack<ValType>& v)
{
	Size = v.Size;
	Top = v.Top;
	MyStack = new ValType[Size];
	for (int i = 0; i < Top; i++)
		MyStack[i] = v.MyStack[i];
}

template <class ValType> 
TStack<ValType>::~TStack()
{
	if (MyStack != NULL)
		delete[]MyStack;
}

template <class ValType>
void TStack<ValType>::Include(const ValType i)
{
	OverFlow();
	Top++;
	MyStack[Top] = i;
	
}
template <class ValType>
ValType TStack<ValType>::Exclude()
{
	if (CheckEmpty()) {
		throw "Empty stack";
	}
	else
	{
		ValType res;
		res = MyStack[Top];
		Top--;
		return res;
	}
}
template <class ValType>
ValType TStack<ValType>::Get()
{
	if (CheckEmpty())
		throw "Empty stack";
	else
		return MyStack[Top];
}
template <class ValType>
bool TStack<ValType>::CheckFull() const 
{
	if (Top == Size - 1)
		return true;
	else
		return false;
}
template <class ValType>
bool TStack<ValType>::CheckEmpty() const 
{
	if (Top == (-1))
		return true;
	else
		return false;
}

template<class ValType>
inline void TStack<ValType>::OverFlow()
{
	if (CheckFull()==true)
	{
		ValType* MyStack2;
		MyStack2 = MyStack;
		Size = Size+1;
		MyStack = new ValType[Size];
		for (int i = 0; i < (Size-1); i++)
		{
			MyStack[i] = MyStack2[i];
		}
		delete MyStack2;
	}
}

template<class ValType>
inline int TStack<ValType>::Count()
{
	return Top+1;
}

template<class ValType>
inline void TStack<ValType>::Clean()
{
	Top = -1;
	//ВОТ ТУТ НЕ УВЕРЕН
	Size = s;
	MyStack = new ValType[Size];
}

#endif
