#include "..\include\arithmetic.h"
#include "..\include\stack.h"
using namespace std;


Lexem::Lexem(string s)
{
    a = s;
    Preparestr();
    Size = a.length();
    MyLexema = new string[Size];
    Prior = new int[Size];
    TStack <char> RES;
    for (int i = 0; i < Size; i++)
    {
        MyLexema[i] = ' ';
        Prior[i] = -1;
    }
    MyLexema[0] = a;
}

Lexem::~Lexem()
{
    delete[] MyLexema;
    delete[] Prior;
}

void Lexem::GetString(string s)
{
    a = s;
    Preparestr();
    Size = a.length();
    MyLexema = new string[Size];
    Prior = new int[Size];
    TStack <char> RES;
    for (int i = 0; i < Size; i++)
    {
        MyLexema[i] = ' ';
        Prior[i] = -1;
    }
    MyLexema[0] = a;
    Polskastring = "";
}

void Lexem::Preparestr()
{
	string result;
	for (int i = 0; i < a.size(); i++) {
        if (a[i] == ',') result += '.';
		else if (a[i] != ' ') result += a[i];
       
	}
	a = result;
}

void Lexem::Divide()
{
    string a = MyLexema[0];
    int j = 0;
    string RES = "";
    string* MyLexema1 = new string[Size];
    int* Prior1 = new int[Size];
    for (int i = 0; i < Size; i++)
    { //знаки операций (кроме минуса)
        if ((a[i] == '+') || (a[i] == '*') || (a[i] == '/') || (a[i] == '^'))
        {
            if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; j++; RES = ""; }
            MyLexema1[j] = a[i];
            Prior1[j] = 1;
            j++;
        }
        else //минус
        {
            if (a[i] == '-')
            {
                if ((i == 0)||(((Prior1[j - 1] == 4) || (Prior1[j - 1] == 1))) && (RES == "")) { RES = RES + '-'; }//|| (((Prior1[j - 1] == 4) || (Prior1[j - 1] == 1)))&&
                else {
                    if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; j++; RES = ""; }
                    MyLexema1[j] = a[i];
                    Prior1[j] = 1; j++;
                }
            }
            else //скобки
            {
                if ((a[i] == '(') || (a[i] == ')'))
                {
                    if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; j++; RES = ""; }
                    MyLexema1[j] = a[i];
                    Prior1[j] = 4; j++;
                }
                else // функция sin
                {
                    if ((a[i] == 's') && (a[i + 1] == 'i') && (a[i + 2] == 'n'))
                    {
                        if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; j++; RES = ""; }
                        MyLexema1[j] = "sin"; i = i + 2;
                        Prior1[j] = 5; j++;
                    }
                    else
                    {
                        if ((a[i] == 'c') && (a[i + 1] == 'o') && (a[i + 2] == 's'))
                        {
                            if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; j++; RES = ""; }
                            MyLexema1[j] = "cos"; i = i + 2;
                            Prior1[j] = 5; j++;
                        }
                        else
                        {
                            if ((a[i] == 's') && (a[i + 1] == 'q') && (a[i + 2] == 'r')&& (a[i + 3] == 't'))
                            {
                                if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; j++; RES = ""; }
                                MyLexema1[j] = "sqrt"; i = i + 3;
                                Prior1[j] = 5; j++;
                            }
                            else //операнды-переменные
                            {
                                if (((a[i] >= 'A') && (a[i] <= 'Z')) || ((a[i] >= 'a') && (a[i] <= 'z')))
                                {
                                    if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; j++; RES = ""; }
                                    MyLexema1[j] = a[i];
                                    Prior1[j] = 3; j++;
                                }
                                else //операнды числа
                                {
                                    if (((a[i] >= '0') && (a[i] <= '9')) || (a[i] == '.'))
                                    {
                                        RES = RES + a[i];
                                    }
                                    //else {  } //ошибка не распознаный символ
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (RES != "") { MyLexema1[j] = RES; Prior1[j] = 2; RES = ""; j++; }
    Size = j;
    MyLexema = new string[Size];
    Prior = new int[Size];
    for (int i = 0; i < Size; i++)
    {
        MyLexema[i] = MyLexema1[i];
        Prior[i] = Prior1[i];
    }
    /*if (Errorpointer == -1) { Errorpointer = 1; }*/
}

bool Lexem::CheckSkobka()
{
    int b=0;
    int c = 0;
    TStack <char> S3; int i = 0;
    while ((i < Size))
    {
        if (Prior[i] == 4)
        {
            if (MyLexema[i] == "(") { S3.Include('('); c++; }
            else
            {
                if (S3.CheckEmpty()) { b++; }
                else { S3.Exclude(); c--; }
            }
            
        } 
        i++;
    }

    if ((b==0)&&(c==0)) return true;
    else return false;
}

bool Lexem::CheckTochkadrob()
{
    
    int i = 0;
    while ((i < Size))
    {
        if (Prior[i] == 2) // две и более точек в одном числе
        {
            string f = MyLexema[i];
            int  k = count(f.begin(), f.end(), '.');
            if (k > 1) { return false; }
        } i++;
    }
   return true;
}

bool Lexem::CheckPeremenpodr()
{
    int i = 0;
   
    while ((i < Size))
    {
        if ((Prior[i] == 3) && (Prior[i + 1] == 3)) { return false; } 
        i++;
    }
   
    return true;
}

bool Lexem::CheckFunc()
{ 
  int i = 0;
        while (i < Size)
        {
            if ((Prior[i] == 5) && (Prior[i + 1] == 1)) {return false; }
            if ((Prior[i] == 5) && (Prior[i + 1] != 4)) {return false; }
            if ((Prior[i] == 5) && (Prior[i - 1] == 2)&&(MyLexema[i - 1]!="-")) {return false; }
            if ((Prior[i] == 5) && (Prior[i - 1] == 3)) {return false; }
            if ((Prior[i] == 5) && (i == Size - 1)) { return false; }
            i++;
        }
        return true;
}

bool Lexem::CheckZnakiSkobki()
{
    int i = 0;
    while (i < Size)
    {
        if (MyLexema[i] == "+")
        {
            if ((MyLexema[i + 1] == "+") || (MyLexema[i - 1] == "+")) { return false; }
            // два знака подряд, знак после открывающейся скобки, знак перед закрывающейся скобкой
        }
        if (MyLexema[i] == "-")
        {
            if ((MyLexema[i + 1] == "+")|| (MyLexema[i + 1] == "-")) { return false; }
            // два знака подряд, знак после открывающейся скобки, знак перед закрывающейся скобкой
        }
        if (Prior[i] == 1)
        {
            if ((Prior[i + 1] == 1) || (MyLexema[i - 1] == "(") || (MyLexema[i + 1] == ")")) { return false; }
            // два знака подряд, знак после открывающейся скобки, знак перед закрывающейся скобкой
        } i++;
    }
    if (MyLexema[0] == "+") return false;
    if (Prior[Size-1] == 1) return false;
   
    return true;
}

bool Lexem::CheckALL()
{
    if ((CheckFunc()) && (CheckPeremenpodr()) && (CheckSkobka()) && (CheckTochkadrob()) && (CheckZnakiSkobki())) return true;
    else  throw "NOT_OK_ALL";

    if (!CheckSkobka()) throw "NOT_OK_SKOB";

    if (!CheckTochkadrob()) throw "NOT_OK_TOCHKA";

    if (!CheckPeremenpodr()) throw "NOT_OK_PEREM";

    if (!CheckFunc()) throw "NOT_OK_FUNC";

    if (!CheckZnakiSkobki()) throw "NOT_OK_ZNAKI";   
    
}

void Lexem::PolskaZapis()
{
    

    if (!CheckALL()) { std::cout<< "1"; }
    else {
            int colSkob = 0;
            for (int i = 0; i < Size; i++)
            {
                if (Prior[i] == 4) { colSkob++; };
                if (Prior[i] == 5) { Prior[i] = 1; };
            }
            string* MyLexema1; MyLexema1 = MyLexema; MyLexema = new string[Size - colSkob];
            int* Prior1; Prior1 = Prior; Prior = new int[Size - colSkob];
            TStack <int> RES;
            int j = 0;
            for (int i = 0; i < Size; i++)
            {
                if ((Prior1[i] == 2) || (Prior1[i] == 3))
                {
                    MyLexema[j] = MyLexema1[i];
                    Prior[j] = Prior1[i];
                    j++;
                }
                else
                {
                    if (Prior1[i] == 1)
                    {
                        if (RES.CheckEmpty()) { RES.Include(i); }
                        else
                        {
                            int pr1 = PRIOR(MyLexema1[i]), pr2 = PRIOR(MyLexema1[RES.Get()]);
                            if (pr1 > pr2) { RES.Include(i); }
                            else
                            {
                                while ((pr1 <= pr2) && (!RES.CheckEmpty()))
                                {
                                    int q = RES.Exclude();
                                    MyLexema[j] = MyLexema1[q];
                                    Prior[j] = Prior1[q];
                                    j++;
                                    if (!RES.CheckEmpty()) { pr2 = PRIOR(MyLexema1[RES.Get()]); }
                                } RES.Include(i);
                            }
                        }
                    }
                    else
                    {
                        if (MyLexema1[i] == "(") { RES.Include(i); }
                        else
                        {
                            if (MyLexema1[i] == ")")
                            {
                                int w = 0;
                                while ((!RES.CheckEmpty()) && (w == 0))
                                {
                                    int q = RES.Get();
                                    if (MyLexema1[q] == "(") { w = 1; }
                                    else
                                    {
                                        q = RES.Exclude();
                                        MyLexema[j] = MyLexema1[q];
                                        Prior[j] = Prior1[q];
                                        j++;
                                    }
                                } RES.Exclude();
                            }
                        }
                    }
                }
            }
            while (!RES.CheckEmpty())
            {
                int q = RES.Exclude(); MyLexema[j] = MyLexema1[q]; Prior[j] = Prior1[q]; j++;
            }
            Size = Size - colSkob;
            POINT = true;

            delete[] MyLexema1;
            delete[] Prior1;
    }
    for (int i = 0; i < Size; i++)
    {
        Polskastring = Polskastring + MyLexema[i];
    }

   
}

double Lexem::Convert_str_to_double(string s)
{
        
        double res = stod(s);
        return res;
    
}

double Lexem::CALC()
{
    if (POINT == false) PolskaZapis();
    TStack <double> RES;
   
    //ПЕРЕМЕННАЯ ЗА МЕСТО ПУСТОЙ ПЕРЕМЕННОЙ
    std::cout << std::setprecision(17);
    int s = Size, j = 0;

    double* M1 = new double[Size];;
    string* M2 = new string[Size];
    for (int i = 0; i < Size; i++)
    {
        if (Prior[i] == 2) { RES.Include(Convert_str_to_double(MyLexema[i])); }
        if (Prior[i] == 3)
        {
            int w = 0, f = -1;
            while ((w < j) && (f == -1))
            {
                if (M2[j] == MyLexema[i]) { f = i; RES.Include(f); } w++;
            }
            if (f == -1)
            {
                double q;
                std::cout << "\tEnter the value of the variable " << MyLexema[i] << ":\n\t";
                if (r == 0.0) { cin >> q; r = q; }
                else { q = r; } RES.Include(q); M1[j] = q; M2[j] = MyLexema[i];
            }
        }
        if (Prior[i] == 1)
        {
            double x, y;
            x = RES.Exclude();
            if (MyLexema[i] == "sin") { RES.Include(sin(x)); }
            else if (MyLexema[i] == "cos") { RES.Include(cos(x)); }
            else if (MyLexema[i] == "sqrt") { RES.Include(sqrt(x)); }
            else
            {
                y = RES.Exclude();
                if (MyLexema[i] == "+") { RES.Include(x + y); }
                if (MyLexema[i] == "-") { RES.Include(y - x); }
                if (MyLexema[i] == "*") { RES.Include(x * y); }
                if (MyLexema[i] == "/") { RES.Include(y / x); }
                if (MyLexema[i] == "^") { RES.Include(pow(y, x)); }
            }
        }
       
    }
    delete[] M1;
    delete[] M2;
    return RES.Exclude();
}

