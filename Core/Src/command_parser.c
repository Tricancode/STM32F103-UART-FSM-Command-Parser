/*
 * command_parser.c
 *
 *  Created on: Nov 4, 2026
 *      Author: ntmin
 */
#include "command_parser.h"
#include <string.h>

typedef enum {
    WAIT_START,
    WAIT_END
} ParserState;

ParserState parser_state = WAIT_START;

uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t command_data[MAX_BUFFER_SIZE];
uint8_t is_cmd_ready = 0;
uint8_t command_index = 0;

extern UART_HandleTypeDef huart2;
extern uint8_t temp;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
    	//ghi gia tri cua temp (1 ki tu) vao buffer
        buffer[index_buffer++] = temp;
        if (index_buffer >= MAX_BUFFER_SIZE)
        {
            index_buffer = 0;
        }
        //bat co bao hieu
        buffer_flag = 1;
        //Moi lai ngat UART
        HAL_UART_Receive_IT(&huart2, &temp, 1);
    }
}
//MAY TRANG THAI
void command_parser_fsm(void)
{
	//Vi tri cua ki tu se duoc xu li
	uint8_t last_index = (index_buffer == 0) ? (MAX_BUFFER_SIZE - 1) : (index_buffer - 1);
	uint8_t current_char = buffer[last_index];
	switch(parser_state)
	{
	case WAIT_START:
		//bat dau xu li
		if(current_char =='!')
		{
			parser_state = WAIT_END;
			command_index = 0;
			memset(command_data,0, MAX_BUFFER_SIZE);
		}
		break;
	case WAIT_END:
		//chot lai chuoi
		if(current_char == '#')
		{
			command_data[command_index]= '\0';
			is_cmd_ready=1;
			parser_state = WAIT_START;
		}
		//ghi lai tu dau
		else if(current_char == '!')
		{
			command_index = 0;
			memset(command_data, 0, MAX_BUFFER_SIZE);
		}
		else
		//tien hanh ghi cac ky tu vao mang
		{
			if(command_index < MAX_BUFFER_SIZE -1)
			{
				command_data[command_index++] = current_char;
			}
		}
		break;

	default:
		parser_state = WAIT_START;
		break;
	}
}







