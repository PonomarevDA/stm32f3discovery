/**
* @file target.cpp
* @brief ���������� ��������� �������� �����
*/

#include "stm32f3xx.h"
#include <target.hpp>
#include <soft_timer.hpp>
#include <leds_rotation.hpp>

extern TargetBase Target;
extern LedsRotation Leds;


int main()
{
    Target.InitGPIO();
    SoftTimer Timer;
    while (1)
    {
		Leds.LedsRotarion();
	}
}

