// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//https://msdn.microsoft.com/en-us/library/ff802693.aspx?f=255&MSPPError=-2147217396

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>



//#define PCOM(a)		COM##a
#define FLASH_SECTOR_MIN		1
#define FLASH_SECTOR_MAX		23

using namespace std;

HANDLE hSerial;

uint8_t serial_init(void);
uint8_t read_command(char *arr);
uint8_t select_act(void);
uint8_t* prep_uart_msg(uint8_t size);
uint8_t find_separ(uint8_t i, uint8_t limit);
uint8_t is_digit(char* arr, uint8_t len);
uint8_t is_digit_hex(char* arr, uint8_t len);
 void tx_buff_form (uint8_t* buf, uint8_t* data, uint8_t size);

static char buff[64] = { 0 };
static struct _TxBuff
{
	int lengh_msg;
	int size_flash_area;
	uint8_t comm;
	uint8_t sector_start;
	uint8_t sector_end;
	uint32_t* flash_address_start;
	uint32_t* flash_address_end;
	uint8_t* tx_data = NULL;
}transData;

int main()
{
	////////////////////////////////
	int i = 0;
	/////////////////////////////
	uint8_t err = 0;
	uint8_t len = 0;
	if ((err=serial_init()) != 0)
	{
		cout << "ERROR SerialPortInit " << err << endl;
		return err;
	}
	else printf("Init SerialPort COM3");
	
	if ((len = read_command(buff)) >= 1)
	{		
		if (prep_uart_msg(len - 1) != NULL)  printf("MSG READY \n") ;
		else if (transData.comm == 1) printf("MSG READY  CLear ALL\n");
	}
	else printf("Uncorrect input\n");

		
//	free(uart_msg);
//	getchar();
	return 0;
}

uint8_t serial_init(void)
{

	LPCTSTR sPortName = L"COM3";
//	for (char i = 31; i < 33; i++)
//	{
//	char i = '3';
//		uint8_t cnt_av_ports = 0;
		uint8_t err;
//		LPCTSTR sPortName = L/**/PCOM(3);
		hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hSerial == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				printf("serial port does not exist.\n");
				return err = 1;
				//continue;
			}
			printf("some other error occurred.\n");
			return err = 2;
		}
		else
		{
//			cnt_av_ports++;
//			cout << "Available COM(" << i << ")\t";
			err = 0;
		}
		return err;
//	}
}

/*
void toupper_string(char*str) {
	while (*str) {
		if (*str >= 'a' && *str <= 'z') {
			*str -= ' ';
			++str;
		}
	}
}
*/

uint8_t read_command(char* arr)
{
	uint8_t len = 0;
	char c;
	do
	{
		c = getchar();
		if ((c > 0x60) && (c < '{')) c = c - ' ';// преобразовали прописные в заглавные
		
		*arr = c;
		arr++;
		len++;
		putchar(c);
	} while ((c != '\0')&&(c != '\n'));

	return len;
}

uint8_t select_act(void)
{
	char* ptr_arr = buff;
	while ((*ptr_arr != '\0') && (*ptr_arr != '\n'))
	{

		ptr_arr++;
	}
	return 0;
}

uint8_t* prep_uart_msg(uint8_t size)
{
//	static uint8_t* uart_msg = NULL;// (uint8_t*)malloc(size);//!!!!! Перенести после расшифровки команды и определния длины сообщения!!!!!!!!!!
	//// в массив uart_msg внести данные после длины сообщения. Длину передавать первым пакетом длиной 1 байт!!!!
	/// при проверке адреса ввести проверку системы счисления (индекс 0x перед HEX, DEC - без индекса.
	///передав длину плате, получить подтверждение длины.После передачи команды и адреса получить подтверждение из от платы. 
	////верифицировать. Подтвердить через консоль операцию!!!!!
	uint8_t i = 0;
	char st[3] = { 0 };

	switch (buff[0])
	{
	case 'C': 
	{
		i = find_separ(i + 1, size - 1);
		switch (buff[i])
		{
		case 'A': transData.comm = 1; transData.lengh_msg = 0; break;
// clear page address size( in bytes )
		case 'P': transData.comm = 2; transData.lengh_msg = 8; i = find_separ(i + 1, size - 1);
			if (is_digit_hex(buff + i, 4) == 0)
			{
				for (uint8_t ind = i; ind < (i + 4); ind++)
				{
					switch (buff[ind])
					{
//					case '0' ... 'F': break;
//					case 'a' ... 'f': break;
					default: break;
					}
				}
			}

			printf("ClearPAGE\n"); break;
		case 'S':
		{
			transData.comm = 3; transData.lengh_msg = 1; i = find_separ(i + 1, size - 1);
			if (is_digit(buff + i, 2) == 0)
				
				st[0] = buff[i]; st[1] = buff[i + 1];   uint8_t sector = atoi(st); 
				if ((sector < FLASH_SECTOR_MAX) && (sector > FLASH_SECTOR_MIN))
				{
					transData.sector_start =  sector; transData.sector_end = sector;
	//				uint8_t size = transData.lengh_msg;
					transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
					tx_buff_form(transData.tx_data, &transData.sector_start, transData.lengh_msg);
					printf("ClearSECTOR %d\n", sector);
				}

				else printf("Sector number ERROR\n"); break;
			{
				printf("WRONG Sector ADDRESS\n");
			}
			break;
		}
		default: printf("ERROR_Clear\n"); break;
		} 
	} break;
	case 'R': i = find_separ(i, size - 1) + 1; break;
	case 'W': i = find_separ(i, size - 1) + 1; break;
	default: return NULL;
	}


	return transData.tx_data;
}

uint8_t find_separ(uint8_t i, uint8_t limit)
{
	while((((buff[i] > '/') && (buff[i] < ':')) || ((buff[i] > '@') && (buff[i] < '['))/* ||((buff[i] >='a')&&(buff[i] <'{'))*/) && (i<limit))
//                       1 ... 9								  A ... Z									a ...z
	{
		++i;
	}
	while (((buff[i] < '0') || ((buff[i] > '9') && (buff[i] < 'A')) || (buff[i] >= 'Z')) && (i < limit))

	{
		++i;
	}
	return i;
}

uint8_t is_digit(char* arr, uint8_t len)
{
	uint8_t err = 0;
	while (len--)
	{
		if ((*arr > '9') || (*arr < '0'))
		{
			err++;
		}
	}
	return err;
}

uint8_t is_digit_hex(char* arr, uint8_t len)
{
	uint8_t err = 0;
	while (len--)
	{
		if ((*arr < '0') || (*arr > '9') && (*arr < 'A') || (*arr > 'F')/* && (*arr < 'a') || (*arr > 'f')*/)
		{
			err++;
		}
		printf("ARRisdigit %c\n", *arr); arr++;
	}
	return err;
}

void tx_buff_form(uint8_t * buf, uint8_t* data, uint8_t size)
{
	int i = 0;
	while (size--)
	{
		buf[i] = data[i];
		i++;
	}

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
