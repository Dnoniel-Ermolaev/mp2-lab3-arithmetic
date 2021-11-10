// тесты для вычисления арифметических выражений
#include "..\include\arithmetic.h"
#include <gtest.h>
#include <string>
#include "cstdlib"
#include <iostream>
#include <cmath>
#include <iomanip>


TEST(Lexem, can_create_Lexema)
{
	ASSERT_NO_THROW(Lexem L);
}
TEST(Lexem, can_create_Lexema_by_string_1)
{
	string a = ")((62+(62-3+1))";
	ASSERT_NO_THROW(Lexem L(a));
}
TEST(Lexem, can_create_Lexema_by_string_2)
{
	string a = " ((62 + (62 - 3 + 1)))";
	ASSERT_NO_THROW(Lexem L(a));
}
TEST(Lexem, can_get_Lexema_1)
{
	Lexem L1;
	string a = ")((62+(62-3+1))";
	ASSERT_NO_THROW(L1.GetString(a));

}
TEST(Lexem, can_get_Lexema_2)
{
	Lexem L1;
	string a = " ((62 + (62 - 3 + 1)))";
	ASSERT_NO_THROW(L1.GetString(a));
}
TEST(Lexem, correct_form_without_space) {
	Lexem L("5+ 12  + 6 12  *5");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("5+12+612*5", L.a);
}
TEST(Lexem, correct_divide_operation_1) {
	Lexem L("5+3-6+sqrt(234)+-1.00000005+0.5^2+sin(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("-1.00000005", L.MyLexema[11]);
}
TEST(Lexem, correct_divide_operation_2) {
	Lexem L("5+3-6+sqrt(234)+-1.00000005+0.5^2+sin(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("234", L.MyLexema[8]);
}
TEST(Lexem, correct_divide_operation_3) {
	Lexem L("5+3-6+sqrt(234)+-1.00000005+0,5^2+sin(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("0.5", L.MyLexema[13]);
}
TEST(Lexem, correct_divide_operation_4) {
	Lexem L("5+3-6+sqrt(234)+-1.00000005+0,5^2+sin(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("0.5", L.MyLexema[13]);
}
TEST(Lexem, correct_divide_operation_5) {
	Lexem L("5+3-6+sqrt(234)+-1.00000005+0,5^2+sin(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("^", L.MyLexema[14]);
}
TEST(Lexem, correct_divide_operation_6) {
	Lexem L("5+3-6+sqrt(234)+-1.00000005+0,5^2+sin(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("sin", L.MyLexema[17]);
}
TEST(Lexem, correct_divide_operation_7) {
	Lexem L("sqrt(sin((cos(0))^2)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("sqrt", L.MyLexema[0]);
}
TEST(Lexem, correct_divide_operation_8) {
	Lexem L("sqrt(sin((cos(0))^2)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("sin", L.MyLexema[2]);
}
TEST(Lexem, correct_divide_operation_9) {
	Lexem L("sqrt(sin((cos(0))^2)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("cos", L.MyLexema[5]);
}
TEST(Lexem, correct_divide_operation_10) {
	Lexem L("sqrt(sin((cos(0))^2)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("0", L.MyLexema[7]);
}
TEST(Lexem, correct_divide_operation_11) {
	Lexem L("sqrt(sin((cos(0))^2)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ("^", L.MyLexema[10]);
}
TEST(Lexem, correct_check_Skob_1)
{
	Lexem L("((5+2)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(false,L.CheckSkobka());
}
TEST(Lexem, correct_check_Skob_2)
{
	Lexem L("(())5+2)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(false,L.CheckSkobka());
}
TEST(Lexem, correct_check_func_1)
{
	Lexem L("3sin(4)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(false,L.CheckFunc());
}
TEST(Lexem, correct_check_func_2)
{
	Lexem L("sqrt(sin(5))");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(true,L.CheckFunc());
}
TEST(Lexem, correct_check_func_3)
{
	Lexem L("(3+5)sin(4)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(true, L.CheckFunc());
}
TEST(Lexem, correct_check_znak_1)
{
	Lexem L("-5+-6");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(true,L.CheckZnakiSkobki());
}
TEST(Lexem, correct_check_znak_2)
{
	Lexem L("--5+5");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(false, L.CheckZnakiSkobki());
}
TEST(Lexem, correct_check_znak_3)
{
	Lexem L("-5+5-");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(false, L.CheckZnakiSkobki());
}
TEST(Lexem, correct_check_znak_4)
{
	Lexem L("(5+13^3)/+3");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(false,L.CheckZnakiSkobki());
}
TEST(Lexem, correct_check_znak_5)
{
	Lexem L("-4+(5+-10)/(-3)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(true, L.CheckZnakiSkobki());
}
TEST(Lexem, correct_check_tochka_1)
{
	Lexem L("-5..6");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(false, L.CheckTochkadrob());
}
TEST(Lexem, correct_check_tochka_2)
{
	Lexem L("-5,6");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(true, L.CheckTochkadrob());
}

TEST(Lexem, correct_check)
{
	Lexem L("3&+2");
	L.Preparestr();
	L.Divide();
	EXPECT_NO_THROW(L.CheckALL());
}
TEST(Lexem, correct_check_brackets_1)
{
	Lexem L("(3+2");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());

}
TEST(Lexem, correct_check_brackets_2)
{
	Lexem L("3+2)");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());

}
TEST(Lexem, correct_check_brackets_3)
{
	Lexem L("(3+2)7)");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());
}
TEST(Lexem, correct_check_brackets_4)
{
	Lexem L("(*(3+2)");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());
}
TEST(Lexem, correct_check_signs_ofoperations_1)
{
	Lexem L("+3+2");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());

}
TEST(Lexem, correct_check_signs_ofoperations_2)
{
	Lexem L("-3+2");
	L.Preparestr();
	L.Divide();
	EXPECT_NO_THROW(L.CheckALL());

}
TEST(Lexem, correct_check_signs_ofoperations_3)
{
	Lexem L("3*+2");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());
}
TEST(Lexem, correct_check_points_of_numbers)
{
	Lexem L("3.0.99+2");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());
}
TEST(Lexem, correct_check_variable)
{
	Lexem L("xy+2");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());
}
TEST(Lexem, correct_check_function_1)
{
	Lexem L("10sin3");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());

}
TEST(Lexem, correct_check_function_2)
{
	Lexem L("sin+9");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());
}
TEST(Lexem, correct_check_function_3)
{
	Lexem L("sin");
	L.Preparestr();
	L.Divide();
	EXPECT_ANY_THROW(L.CheckALL());
}

TEST(Lexem, can_convert_in_Polish_entry)
{
	Lexem L("(62+3)*936-22");
	L.Preparestr();
	L.Divide();
	ASSERT_NO_THROW(L.PolskaZapis());
}

TEST(Lexem, right_convert_in_Polish_entry)
{
	Lexem L("(62+3)*936-22");
	string a = "623+936*22-";
	L.Preparestr();
	L.Divide();
	L.PolskaZapis();
	string test;
	for (int i = 0; i < L.Size; i++)
	{
		test += L.MyLexema[i];
	}
	EXPECT_EQ(a,test);
}

TEST(Lexem, right_convert_in_Polish_entry_2)
{
	Lexem L("");
	string a;
	L.GetString("(1+2)*(3/4^5)+sin(x)");
	a = "12+345^/*xsin+";
	L.Preparestr();
	L.Divide();
	L.PolskaZapis();
	EXPECT_EQ(a,L.Polskastring);
}


TEST(Lexem, rigt_converte_int) {
	Lexem L("123512462346");
	L.Preparestr();
	L.Divide();
	L.Convert_str_to_double(L.MyLexema[0]);
	EXPECT_EQ(L.Convert_str_to_double(L.MyLexema[0]), 123512462346);
}

TEST(Lexem, rigt_converte_double) {
	Lexem L("123.51200000462346");
	L.Preparestr();
	L.Divide();
	L.Convert_str_to_double(L.MyLexema[0]);
	EXPECT_EQ(L.Convert_str_to_double(L.MyLexema[0]), 123.51200000462346);
}

TEST(Lexem, right_calculation_Lexema_1)
{
	Lexem L("(62+3)*936-22");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ((62.0 + 3.0) * 936.0 - 22.0,L.CALC());
}
TEST(Lexem, right_calculation_Lexema_with_negative_numbers)
{
	Lexem L("(-2+3)*936-22");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ((-2.0 + 3.0) * 936.0 - 22.0,L.CALC());
}
TEST(Lexem, right_calculation_Lexema_with_function)
{
	Lexem L("(62+3)*sin(23)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ((62.0 + 3.0) * sin(23.0),L.CALC());
}
TEST(Lexem, right_accuracy_cos) {
	Lexem L("cos(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(cos(5), L.CALC());
}
TEST(Lexem, right_accuracy_sin) {
	Lexem L("sin(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(sin(5), L.CALC());
}
TEST(Lexem, right_accuracy_sqrt) {
	Lexem L("sqrt(5)");
	L.Preparestr();
	L.Divide();
	EXPECT_EQ(sqrt(5), L.CALC());
}

TEST(Lexem, right_calculation_Lexema_2)
{
	
	Lexem L("((1232+11.6277)*(62/-3)/((5-3)^7.4)*sin(x+5))*5");
	L.Preparestr();
	L.Divide();
	L.r = 7.0;
	EXPECT_EQ(408.26072932231386, L.CALC());//ввести 7
}