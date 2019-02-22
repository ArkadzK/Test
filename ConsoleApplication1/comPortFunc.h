#pragma once

#ifndef _COMPORTFUNC
#define _COMPORTFUNC

#include <Windows.h>
#include <stdint.h>
#include <stdio.h>
#include "ConsoleApplication1.cpp"

STAGE com_select(void);
STAGE comm_est(void);
uint8_t serial_init(void);
void sendMSG(uint8_t*txd, uint32_t len);
void readMSG(DWORD size);
uint8_t send_cmd_CS(uint8_t sect_st, uint8_t sect_end);
uint8_t send_cmd_RP(uint32_t st_addr, uint32_t end_addr, const char* file_name);
uint8_t send_cmd_WP(uint32_t st_addr, uint32_t end_addr, uint8_t* data);

#endif
