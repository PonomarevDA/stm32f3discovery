/**
* @file encoder.cpp
* @brief Implementation of encoder sensor
*/

#include "encoder.hpp"

static uint32_t Counter = 0;

void Encoder::Init()
{
	
	//EXTI->FTSR |= EXTI_FTSR_TR10;					/// �� ���������� ������
	EXTI->RTSR |= EXTI_RTSR_TR10;					/// �� ������������ ������
	EXTI->IMR |= EXTI_IMR_MR10;						/// ��������� ���������� �������
	SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PD; 	/// �������� ��������� ���������� PD[10]
	NVIC_EnableIRQ(EXTI15_10_IRQn);					/// ��������� ���������� EXTI10 � NVIC
}


uint32_t Encoder::GetPulses()
{
	return 777;
}


extern "C"
{
	void EXTI15_10_IRQHandler(void)
	{
		Counter++;
		EXTI->PR |= EXTI_PR_PR10;
	}
}
