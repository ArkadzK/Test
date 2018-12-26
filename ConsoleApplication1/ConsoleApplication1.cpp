// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//https://msdn.microsoft.com/en-us/library/ff802693.aspx?f=255&MSPPError=-2147217396

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>



//#define PCOM(a)		COM##a
#define FLASH_SECTOR_MIN			1
#define FLASH_SECTOR_MAX			23
#define FLASH_SECTOE_ADDR_START		(uint32_t)0x08000000
#define FLASH_SECTOE_ADDR_END	    (uint32_t)0x08100000
#define DEC							(uint8_t)0
#define HEX							(uint8_t)1

using namespace std;

HANDLE hSerial;
uint8_t scanCOMports(void);
uint8_t serial_init(void);
uint8_t read_command(char *arr);
uint8_t select_act(void);
uint8_t* prep_uart_msg(uint8_t size);
uint8_t find_separ(uint8_t i, uint8_t limit);
uint8_t is_digit(char* arr, uint8_t len);
uint8_t is_digit_hex(char* arr, uint8_t len);
void tx_buff_form (uint8_t* buf, char* data, uint8_t size);
uint8_t number_of_digit(char* arr, uint8_t type);
uint8_t char_to_uint8(char* arr);

static char buff[64] = { 0 };
static struct _TxBuff
{
	int lengh_msg;
	int size_flash_area;
	uint8_t comm;
	uint8_t sector_start;
	uint8_t sector_end;
	uint32_t flash_address_start;
	uint32_t flash_address_end;
	uint8_t* tx_data = NULL;
}transData;

wchar_t name[] = { L'C',L'O',L'M',L'0',L'\0',L'\0' };
wchar_t number[] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6' ,L'7' ,L'8' ,L'9' };
LPCTSTR sPortName;


int main()
{
	uint8_t repeat_action_flag = 1;

	uint8_t err = 0;
	uint8_t len = 0;
	/* Scanning of COM-ports, setup parameters	*/
	while(repeat_action_flag)
	{ 
		if ((err=serial_init()) != 0)
		{
			printf("ERROR SerialPortInit! Press any key for repeat or (N) for exit");
			name[4] = '\0';
			char c = getchar();
			if (c == 'N' || c == 'n') return 1;
		}
		else 
		{
			repeat_action_flag = 0;
			printf("Init COM%c%c OK\n",name[3],name[4]);
		}
	}
	/////////////////////////////////////////////////
/*	char c[] = "f0e1d2c3";
	unsigned int t =(unsigned int) atoi(c);
	printf("%s\t%x\n", c, t);
	uint8_t* r = (uint8_t*)&t;
	printf("DATA %x		 %x		 %x			%x \n", *r, *(r + 1), *(r + 2), *(r + 3));
	printf("Addr %x %x %x %x\n", (unsigned int)r, (unsigned int)(r + 1), (unsigned int)(r + 2), (unsigned int)(r + 3));
	printf("DATA %x\n", t);
	printf("Addr %x\n", (unsigned int)&t);




	return 0;*/
	//////////////////////////////////////////////////

	/* recieve command  */
	repeat_action_flag = 1;
	while (repeat_action_flag)
	{
		printf("Enter the command:\n");
		printf("\t : clear all\\sector\\page	NOTHING\\number(dec)\\address(hex)\n");
		printf("\t : read start_address(hex) end_address(hex)\n");
		printf("\t : write sector\\page number(dec)\\start_address(hex) NOTHING\\end_address(hex)\n ");
		if ((len = read_command(buff)) )
		{
			if (prep_uart_msg(len - 1) != NULL)
			{

				repeat_action_flag = 0;
				if (transData.comm == 3)
				{
					printf("Clear PAGE address = 0x 0%x\n", transData.flash_address_start);
					//sendMSG()
				}
				printf("MSG READY  \n") ;// sendMSG()
			}
			else if (transData.comm == 1)
			{
				repeat_action_flag = 0;
				printf("CLear ALL\n");// sendMSG()
			}
			else
			{
				printf("Uncorrect input! Press any key for repeat or (N) for exit");

				char c = getchar();
				if (c == 'N' || c == 'n') return 1;
			}
		}
		else
		{
			printf("Uncorrect input! Press any key for repeat or (N) for exit");
			char c = getchar();
			if (c == 'N' || c == 'n') return 1;
		}
	}
		
//	free(uart_msg);
//	getchar();
	return 0;
}

uint8_t serial_init(void)
{
//	wchar_t *nbr;// = { L'C',L'O',L'M',L'3',L'\0' };
//	LPCTSTR sPortName = L"COM3";
	///////////////////////////////////////////////////////////////////////////////

	uint8_t er = 1;
	printf(" the follows COM ports are available: ");
	for (int ind = 0; ind < 100; ++ind)
	{
		if (ind < 10)
		{
//			wchar_t name[] = { L'C',L'O',L'M',L'0',L'\0' };
			name[3] = number[ind];
		}
		else
		{
//			wchar_t name[] = { L'C',L'O',L'M',L'0',L'0',L'\0' };
			name[4] = number[ind % 10];
			name[3] = number[ind / 10];
		}
		LPCTSTR sPortName = name;
		

		hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (hSerial == INVALID_HANDLE_VALUE)
		{
/*
			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				printf("serial port %d does not exist.\n", ind);
				//return err = 1;
				
			}
			printf("some other error occurred.\n");*/
			continue;
			//return err = 2;
		}
		else
		{
			printf("\tCOM%d", ind);
			er = 0;
		}
		CloseHandle(hSerial);
	}
	if (er == 1) printf(" NO \n");
	else
	{
		printf("\n Input the number of COM");
		char nb[2] = { 0 };
		uint8_t len = 0;
		if ((len= read_command(buff))<3) 
			if (is_digit(buff, len) == 0)
			{				
				name[3] = number[(uint8_t)(buff[0] - '0')];
				name[4] = (buff[1]? number[(uint8_t)(buff[1] - '0')] : '\0');
				buff[0] = '\0';
				buff[1] = '\0';
				sPortName = name;
				hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				if (hSerial == INVALID_HANDLE_VALUE)
				{
					CloseHandle(hSerial);
					printf("ERROR of opening COM%c%c\n", name[3],name[4]);
					er = 1;

				}
				else
				{
					DCB dcbSerialParams = { 0 };
					dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
					if (!GetCommState(hSerial, &dcbSerialParams))
					{
						printf("getting state error\n");
					}
					dcbSerialParams.BaudRate = CBR_115200;
					dcbSerialParams.ByteSize = 8;
					dcbSerialParams.StopBits = ONESTOPBIT;
					dcbSerialParams.Parity = NOPARITY;
					if (!SetCommState(hSerial, &dcbSerialParams))
					{
						printf("error setting serial port state\n");
					}

				}
			}
		

	}
		return er;

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
//		putchar(c);
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
		case 'P': transData.comm = 2; transData.lengh_msg = 4; i = find_separ(i + 1, size - 1);
			if (number_of_digit(&buff[i], HEX) != 8)
			{
				printf("Uncorrect Address input\n");
				return NULL;

			}

			transData.comm = 3; transData.lengh_msg = 4;
			transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
			tx_buff_form(transData.tx_data, &buff[i], transData.lengh_msg);
			uint32_t addr_st;
//			transData.flash_address_start = &addr_st;

			for (i = 0; i < 4; i++) {
				transData.flash_address_start = (transData.flash_address_start << 8) | *(transData.tx_data + i);;
			}
			if ((transData.flash_address_start < FLASH_SECTOE_ADDR_START) || (transData.flash_address_start > FLASH_SECTOE_ADDR_END))
			{
				printf("Wrong Address!\n");
				return NULL;
			}
			else
			{
				uint32_t addr_korr = transData.flash_address_start % 4;
				if (addr_korr)transData.flash_address_start = transData.flash_address_start - addr_korr;
			}
			break;
		case 'S':
		{
			transData.comm = 3; transData.lengh_msg = 1; i = find_separ(i + 1, size - 1);
			if (is_digit(buff + i, 2) == 0)
			{ 
				st[0] = buff[i]; st[1] = buff[i + 1];   uint8_t sector = atoi(st); 
				if ((sector < FLASH_SECTOR_MAX) && (sector > FLASH_SECTOR_MIN))
				{
//					transData.sector_start =  sector; transData.sector_end = sector;
	//				uint8_t size = transData.lengh_msg;
					transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
//					tx_buff_form(transData.tx_data, &transData.sector_start, transData.lengh_msg);
					*(transData.tx_data) = sector;
					printf("Clear SECTOR %d\n", sector);
				}

				else
				{
					printf("WRONG Sector number!\n");
					return NULL;
				}
			}
			else
			{
				printf("WRONG Sector format!\n"); return NULL;
			}
			break;
		}
		default: printf("ERROR_Clear command\n"); break;
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

void tx_buff_form(uint8_t * buf, char* data, uint8_t size)
{
	buf[0] = char_to_uint8(data);
	buf[1] = char_to_uint8(data+2);
	buf[2] = char_to_uint8(data + 4);
	buf[3] = char_to_uint8(data + 6);
/////////////////////////////////////////////////////
	printf("%x %x %x %x\n",buf[0], buf[1],buf[2],buf[3]);

}

uint8_t number_of_digit(char* arr, uint8_t type)
{
	uint8_t cnt = 0;
	if (type )
	{ 
		while (((arr[cnt] > 0x2f) && (arr[cnt] < 0x3a)) || ((arr[cnt] < 'G') && (arr[cnt] > '@')))
		{
			putchar(arr[cnt]);
			cnt++;
		}
	}
	else
	{
		while (((arr[cnt] > 0x2f) && (arr[cnt] < 0x3a)))
		{
			cnt++;
		}
	}
	return cnt;
}

uint8_t char_to_uint8(char* arr)
{
	uint8_t d;
	if ((*arr > 0x2f) && (*arr < 0x3a)) d = (uint8_t)((*arr - '0') * 16);
	else d = (uint8_t)((*arr - 55) * 16);
	if ( (*(arr+1) > 0x2f) && (*(arr+1) < 0x3a) ) d = d + (uint8_t)(*(arr+1) - '0') ;
	else d = d + (uint8_t)(*(arr+1) - 55);
	return d;
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
