/**
* @file uart.cpp
* @brief ���������� UART
*/

#include <uart.hpp>
#include <string.h>	// for memcpy (why not <cstring>???)

Buffer BufferRX;

enum
{
	BAUD_RATE_600 = SYSCLOCK/600,		///< 13333
	BAUD_RATE_1200 = SYSCLOCK/1200,		///< 6666
	BAUD_RATE_2400 = SYSCLOCK/2400,		///< 3333
	BAUD_RATE_4800 = SYSCLOCK/4800,		///< 1666
	BAUD_RATE_9600 = SYSCLOCK/9600,		///< 833
	
	BAUD_RATE_14400 = SYSCLOCK/14400,	///< 555
	BAUD_RATE_19200 = SYSCLOCK/19200,	///< 416
	BAUD_RATE_28800 = SYSCLOCK/28800,	///< 277
	BAUD_RATE_38400 = SYSCLOCK/38400,	///< 208
	BAUD_RATE_56000 = SYSCLOCK/56000,	///< 142
	
	BAUD_RATE_57600 = SYSCLOCK/57600,	///< 138
	BAUD_RATE_115200 = SYSCLOCK/115200, ///< 69
	BAUD_RATE_128000 = SYSCLOCK/128000,	///< 62
	BAUD_RATE_256000 = SYSCLOCK/260000,	///< 30
};


/**
* @brief ������������� UART
*/
void UART::Init()
{
	// UART configuration
	enum
	{
		CR1_CONFIG = 						// Word length = 8 bit
											// Oversampling by 16
											// Parity control disabled
											// Parity selection (if control enabled)
					0*USART_CR1_TXEIE | 	// TX Interrupt Enable
					1*USART_CR1_RXNEIE |	// RX Interrupt Enable	
											// 1 stop bit
											// CTS disable
											// RTS disable
					1*USART_CR1_TE |		// Transmitter enable
					1*USART_CR1_RE,			// Receiver enable
		CR2_CONFIG =0,						// Default
		CR3_CONFIG =USART_CR3_DMAT |		// DMA mode is disabled for transmission
					USART_CR3_DMAR, 		// DMA mode is disabled for reception
	};
	
	// 0. Clock and interrupt enable
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	NVIC_EnableIRQ(USART1_IRQn);
	
	// 1. Configure UART
	USART1->CR3 = CR3_CONFIG;	
	USART1->CR1 = CR1_CONFIG;
	
	// 2. Select the desired baud rate using the baud rate register USART_BRR 
	USART1->BRR = BAUD_RATE_128000;
	
	// 3. Enable USART
	USART1->CR1 |=  USART_CR1_UE;
}


/**
* @brief ��������� ������ ������
* @param arr - ��������� �� ������
* @param len - ����� �������
*/
void UART::SendArr(const uint8_t* arr, const uint8_t& len)
{
	uint8_t length = len;
	while(length--)
	{
		if (*arr != 0) 
			SendChar( *arr );
		arr++;
	}
}


/**
* @brief ��������� ���� ���� ������
* @param byte - ����
*/
void UART::SendChar(const uint8_t byte) 
{
	USART1->TDR = byte;
	while( !(USART1->ISR & USART_ISR_TC) );
}


/**
* @brief �������� ��������� �� ������ ������ � ����� �������
* @param ptrArr - ��������� �� ������ ������
* @param length - ������ �� ����� ������� ������
*/
void UART::GetData(uint8_t* ptrArr, uint8_t& length)
{
	BufferRX.PopAll(ptrArr, length);
}


/**
* @brief ���������� ���������� UART
*/
extern "C"
{
	void USART1_IRQHandler()
	{
		// If Read data register not empty
		if ( (USART1->ISR & USART_ISR_RXNE) )
		{	
			BufferRX.Push(USART1->RDR);
		}
		// If Overrun error
		if ( USART1->ISR & USART_ISR_ORE)
		{
			USART1->ICR |= USART_ICR_ORECF;
		}
	}
}


/**
* @brief �������� ���� � ������
* @param byte - ����
*/
void Buffer::Push(const uint8_t byte)
{
	if (Size != MaxSize)
	{
		Arr[Size++] = byte;
	}
}


/**
* @brief �������� ��������� �� ������ ������ � ��� �����
* @param destptr - ��������� ������, � ������� ����� �������� ������
* @param length - ���-�� ���������� ������ ������
*/
void Buffer::PopAll(uint8_t* destptr, uint8_t& length)
{
	memcpy(destptr, Arr, Size);
	length = Size;
	Size = 0;
}

