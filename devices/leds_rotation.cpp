/**
* @file target.cpp
* @brief ���������� ������ ������� ������������ �� ����� � ���������� � �����������
*/

#include <target.hpp>
#include <leds_rotation.hpp>

LedsRotation Leds;
extern TargetBase Target;

/**
* @brief ������� ������������ �� ������� � ������ ���������
*/
void LedsRotation::LedsRotarion()
{
	if (!(Counter & TimerDivider))
	{
		// 1. �������� ������ ���������:
		Target.LedOff(LedOnNumberPrevious);
		Target.LedOn(LedOnNumber);
		LedOnNumberPrevious = LedOnNumber;
		
		// 2. ���������� ����������� ������������ �����������:
		if (DirectionOfRotation & COUNTERCLOCKWISE_ACCELERATION)
		{
			if (LedOnNumber == TargetBase::LD_MIN)
				LedOnNumber = TargetBase::LD_MAX;
			else
				LedOnNumber--;
		}
		else // if clockwise
		{
			if (LedOnNumber == TargetBase::LD_MAX)
				LedOnNumber = TargetBase::LD_MIN;
			else
				LedOnNumber++;
		}
		// 3. ���������� �������� ������������ �����������:
		if (LedOnNumber == 10)
		{
			if ( ((DirectionOfRotation == CLOCKWISE_ACCELERATION) || (DirectionOfRotation == COUNTERCLOCKWISE_ACCELERATION)) )
			{
				if (TimerDivider != 16383)						
					TimerDivider = (TimerDivider << 1) + 1;
				else													// if more slow
					DirectionOfRotation = 3 & (~DirectionOfRotation);	// ������ ����������� �������� � ��������� ������ ��������
			}
			else												
			{
				if (TimerDivider > 2)							
					TimerDivider = TimerDivider >> 1;
				else													// if more fast
					DirectionOfRotation &= ~1;	 						// ������ ��������� ������ ��������
			}
		}
	}
	Counter++;
}
