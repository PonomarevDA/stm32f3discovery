#ifndef __LEDS_ROTATION_HPP
#define __LEDS_ROTATION_HPP

#include "stm32f3xx.h"
#include "soft_timer.hpp"

/**
* @brief ������� ������������ �� ����� � ������ ���������
*/
class LedsRotation
{
	private:
		enum 
		{
			CLOCKWISE_ACCELERATION = 0, 
			CLOCKWISE_DECELERATION = 1, 
			COUNTERCLOCKWISE_ACCELERATION = 2, 
			COUNTERCLOCKWISE_DECELERATION = 3,
		};
		enum
		{
			BLINK_PERIOD_MIN = 10,		// 10 ��
			BLINK_PERIOD_MAX = 100,		// 100 ��
			BLINK_PERION_ITERATION = 10,// 10 ��
		};
		SoftTimer Timer;
		uint8_t LedOnNumber;
		uint8_t LedOnNumberPrevious;
		uint8_t BlinkPeriod;
		uint8_t Direction;
	public:
		LedsRotation(): 
			LedOnNumber(TargetBase::LD_MIN),
			LedOnNumberPrevious(TargetBase::LD_MIN),
			BlinkPeriod(BLINK_PERIOD_MIN),
			Direction(CLOCKWISE_ACCELERATION) {}
		void LedsRotarion();
		
};


#endif	// __LEDS_ROTATION_HPP
