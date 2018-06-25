/**
* @file timer.cpp
* @brief ���������� ������������ �������
*/

#include <soft_timer.hpp>

Timer2 SoftTimer::HardTimer;

/**
* @brief ����������� ������������ �������
*/
SoftTimer::SoftTimer(): Status(TIMER_CREATED)
{
	if (HardTimer.Status == Timer2::HARD_TIMER_NOT_INITIALIZED)
	{
		HardTimer.Init();
	}
}


/**
* @brief ������ ������ �� ����� � ���
* @param timeUs - ����� � ���
*/
void SoftTimer::StartUs(uint16_t timeUs)
{
	
}


/**
* @brief ������ ������ �� ����� � ��
* @param timeMs - ����� � ���
*/
void SoftTimer::StartMs(uint16_t timeMs)
{
	if (timeMs != 0)
	{
		StartCount = HardTimer.GetCount();
		StartOverflows = HardTimer.GetOverflowsCount();
	
		EndCount = StartCount + timeMs * Timer2::ONE_MS;
		EndOverflows = StartOverflows + ( (EndCount < StartCount) ? 1 : 0);
	
		Status = TIMER_WORKING;
	}
	else
	{
		Status = TIMER_FINISHED;
	}
}


/**
* @brief �������� ������ �������
* @return status - ������ ������� 
*/
uint8_t SoftTimer::GetStatus()
{
	uint32_t nowCount = HardTimer.GetCount();
	if ( Status == TIMER_WORKING && IsTimerEnd(nowCount) )
    {
        Status = TIMER_FINISHED;
    }
    return Status;
}


/**
* @brief �������� ������ �������
* @return status - ������ ������� 
*/
uint8_t SoftTimer::IsTimerEnd(uint32_t nowCount)
{
	uint8_t NowOverflows = HardTimer.GetOverflowsCount();
    
    if ( (EndOverflows < NowOverflows) || ( (EndOverflows == NowOverflows) && (EndCount <= nowCount) ) )
        return 1;
    return 0;
}
