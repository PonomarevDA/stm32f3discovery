/**
* @file seven_segments_indicators.cpp
* @brief seven segments indicators implementation
*/

/****************************************************
*	1(1)	2(A)	3(F)	4(2)	5(3)	6(B)	*
*													*
*	FAAAB			FAAAB			FAAAB			*
*	F   B			F   B			F   B			*
*	F   B			F   B			F   B			*
*	GGGGG			GGGGG			GGGGG			*
*	E   C			E   C			E   C			*
*	E   C			E   C			E   C			*
*	EDDDC dot		EDDDC dot		EDDDC dot		*
*													*
*	7(E)	8(D)	9(dot)	10(C)	11(G)	12		*
****************************************************/

#include "stm32f3xx.h"
#include <seven_segments_indicators.hpp>


/**
* @brief ����� �� �������������� ���������� �����
* @param number - �����, ������� ����� ��������
*/
void Indicators::SetNumber(uint16_t number)
{
	enum
	{
		a = (1 << 2), 
		b = (1 << 6), 
		c = (1 << 10), 
		d = (1 << 8), 
		e = (1 << 7), 
		f = (1 << 3), 
		g = (1 << 11), 
		dot=(1 << 9),
		digit3 = (1 << 4) | (1 << 5),
		digit2 = (1 << 1) | (1 << 5),
		digit1 = (1 << 1) | (1 << 4)
	};
	
	short code_of_digit[] = 
	{
		a + b + c + d + e + f,
		b + c,
		a + b + g + e + d,
		a + b + g + c + d,
		f + g + b + c,
		a + f + g + c + d,
		a + c + d + e + f + g,
		a + b + c,
		a + b + c + d + e + f + g,
		a + b + c + d + f + g
	};
	if (digit == 0)
	{
		GPIOB->ODR = code_of_digit[number/100] | digit3 | dot;
		digit++;
	}
	else if (digit == 1)
	{
		GPIOB->ODR = code_of_digit[(number%100)/10] | digit2;
		digit++;
	}
	else
	{
		GPIOB->ODR = code_of_digit[number%10] | digit1;
		digit = 0;
	}
}
