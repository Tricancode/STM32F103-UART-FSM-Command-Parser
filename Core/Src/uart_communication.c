/*
 * uart_communication.c
 *
 *  Created on: Nov 5, 2026
 *      Author: ntmin
 */
#include "uart_communication.h"
#include "command_parser.h"
#include "timer.h"
#include <string.h>
#include <stdio.h>

typedef enum {
    WAIT_RST,
    WAIT_ACK
} UartState;

UartState uart_state = WAIT_RST;

uint32_t adc_value = 0;
char str_transmit[50];

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

void uart_communication_fsm(void)
{
    switch(uart_state)
    {
        case WAIT_RST:
            if (is_cmd_ready == 1)
            {
                is_cmd_ready = 0;

                //kiem tra co phai la RST
                if (strcmp((char*)command_data, "RST") == 0)
                {
                    //Doc gia tri
                    HAL_ADC_Start(&hadc1);
                    HAL_ADC_PollForConversion(&hadc1, 100);
                    adc_value = HAL_ADC_GetValue(&hadc1);

                    //dong goi va gui qua UART
                    sprintf(str_transmit, "!ADC=%lu#\r\n", adc_value);
                    HAL_UART_Transmit(&huart2, (uint8_t*)str_transmit, strlen(str_transmit), 1000);

                    //Dat thoi gian 3s
                    setTimer(0, 3000);
                    uart_state = WAIT_ACK;
                }
            }
            break;

        case WAIT_ACK:
        	//Nhan duoc phan hoi
            if (is_cmd_ready == 1)
            {
                is_cmd_ready = 0;
                if (strcmp((char*)command_data, "OK") == 0)
                {
                    uart_state = WAIT_RST;
                }
            }
            // Neu qua han ma chua duoc nhan OK
            else if (timer_flag[0] == 1)
            {
                //Gui lai goi tin cu
                HAL_UART_Transmit(&huart2, (uint8_t*)str_transmit, strlen(str_transmit), 1000);

                setTimer(0, 3000);
            }
            break;

        default:
            uart_state = WAIT_RST;
            break;
    }
}

