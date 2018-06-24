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
	if (Timer.GetStatus() != TIMER_WORKING)
	{
		// 1. �������� ������ ���������:
		Target.LedOff(LedOnNumberPrevious);
		Target.LedOn(LedOnNumber);
		LedOnNumberPrevious = LedOnNumber;
		
		// 2. ���������� ����������� ������������ �����������:
		if (Direction & COUNTERCLOCKWISE_ACCELERATION)
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
			if ( ((Direction == CLOCKWISE_ACCELERATION) || (Direction == COUNTERCLOCKWISE_ACCELERATION)) )
			{
				if (BlinkPeriod != BLINK_PERIOD_MAX)						
					BlinkPeriod += BLINK_PERION_ITERATION;
				else// (more slow)
					Direction = 3 & (~Direction);	// ������ �������
			}
			else												
			{
				if (BlinkPeriod > BLINK_PERIOD_MIN)							
					BlinkPeriod -= BLINK_PERION_ITERATION;
				else// (more fast)
					Direction &= ~1;	// ������ �������
			}
		}
		Timer.StartMs(BlinkPeriod);
	}
}
