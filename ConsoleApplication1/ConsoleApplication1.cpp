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
#define DEC						(uint8_t)0
#define HEX						(uint8_t)1

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
void tx_buff_form (uint8_t* buf, uint8_t* data, uint8_t size);
uint8_t number_of_digit(char* arr, uint8_t type);

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
				printf("MSG READY \n");// sendMSG()
			}
			else if (transData.comm == 1)
			{
				repeat_action_flag = 0;
				printf("MSG READY  CLear ALL\n");// sendMSG()
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

			if (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
//				printf("serial port %d does not exist.\n", ind);
				//return err = 1;
				
			}
//			printf("some other error occurred.\n");
			continue;
			//return err = 2;
		}
		else
		{
			//			cnt_av_ports++;

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
		/*		LPCTSTR*/ sPortName = name;
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
	////////////////////////////////////////////////////////////////////////////
/*
	uint8_t scanCOMports();
	LPCTSTR sPortName = nbr;
		uint8_t err;

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
*/
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
		case 'P': transData.comm = 2; transData.lengh_msg = 4; i = find_separ(i + 1, size - 1);
			if (number_of_digit(&buff[i], HEX) != 4)
			{
				printf("Uncorrect Address input\n");
				return NULL;

			}
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

void tx_buff_form(uint8_t * buf, uint8_t* data, uint8_t size)
{
	int i = 0;
	while (size--)
	{
		buf[i] = data[i] - '0';
		i++;
	}

}

uint8_t number_of_digit(char* arr, uint8_t type)
{
	uint8_t cnt = 0;
	if (type )
	{ 
		while (((arr[cnt] > 0x2f) && (arr[cnt] < 0x3a)) || ((buff[cnt] < 'G') && (buff[cnt] > '@')))
		{
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
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
