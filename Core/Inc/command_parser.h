/*
 * command_parser.h
 *
 *  Created on: Nov 5, 2026
 *      Author: ntmin
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_

#include "main.h"

#define MAX_BUFFER_SIZE 30
//Cac bien
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

extern uint8_t command_data[MAX_BUFFER_SIZE];
extern uint8_t is_cmd_ready;

//Ham xu li
void command_parser_fsm(void);

#endif /* INC_COMMAND_PARSER_H_ */
