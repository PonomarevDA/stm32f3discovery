/**
* @file timer.cpp
* @brief ���������� �������
*/

#include <timer.hpp>
#include <target.hpp>
extern TargetBase Target;

uint8_t OverflowsCount = 0;

/**
* @brief ������������� �������
*/
void Timer2::Init()
{
	if (Status == HARD_TIMER_NOT_INITIALIZED)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	// Clocking
		TIM2->CR1 = 0x01;					// Counter enabled
        TIM2->DIER = TIM_DIER_TIE;          // Trigger interrupt enabled
		TIM2->DIER |= TIM_DIER_UIE;         // Update interrupt enabled
		//TIM2->ARR = 0x0000FFFF;          	// Auto-reload value
		NVIC_EnableIRQ(TIM2_IRQn);			// Enable interrupt
		Status = HARD_TIMER_INITIALIZED;	
	}
}


/**
* @brief �������� �� ������ �������� �������� � ���-�� ����������
* @param count - ������ �� ����������, ��������� �������� ��������
* @param interruptCount - ������ �� ���-�� ����������
*/
uint32_t Timer2::GetCount()
{
    return TIM2->CNT;
}


/**
* @brief �������� �������� ���-�� ������������ �������
* @return OverflowCount - ���-�� ������������ �������
*/
uint8_t Timer2::GetOverflowsCount()
{
    return OverflowsCount;
}


/**
* @brief ���������� �������2 �� ������������
*/
extern "C"
{
	void TIM2_IRQHandler()
	{
		TIM2->SR = 0;
		OverflowsCount++;
	}
}
