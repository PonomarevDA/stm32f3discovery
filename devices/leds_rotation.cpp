/**
* @file target.cpp
* @brief Implementation of a class of circular blinking LED's
*/

#include <target.hpp>
#include <leds_rotation.hpp>
#include <adc.hpp>

LedsRotation Leds;
extern ADC Adc;

/**
* @brief LED's blinking with speed from ADC
*/
void LedsRotation::Do()
{
	if (Timer.GetStatus() != TIMER_WORKING)
	{
		// 1. �������� ������ ���������:
		Target::LedOff(LedOnNumberPrevious);
		Target::LedOn(LedOnNumber);
		LedOnNumberPrevious = LedOnNumber;
		
		// 2. ���������� ����������� ������������ �����������:
		if (Direction & COUNTERCLOCKWISE_ACCELERATION)
		{
			if (LedOnNumber == Target::LD_MIN)
				LedOnNumber = Target::LD_MAX;
			else
				LedOnNumber--;
		}
		else // if clockwise
		{
			if (LedOnNumber == Target::LD_MAX)
				LedOnNumber = Target::LD_MIN;
			else
				LedOnNumber++;
		}
		// 3. ���������� �������� ������������ �����������:
		BlinkPeriod = Adc.Do() >> 5;
		/*
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
		*/
		Timer.StartMs(BlinkPeriod);
	}
}
