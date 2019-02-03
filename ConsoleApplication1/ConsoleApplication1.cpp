// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//https://msdn.microsoft.com/en-us/library/ff802693.aspx?f=255&MSPPError=-2147217396


#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>



//#define PCOM(a)		COM##a
#define FLASH_SECTOR_MIN			13
#define FLASH_SECTOR_MAX			23
#define FLASH_SECTOR_ADDR_START		(uint32_t)0x08100000
#define FLASH_SECTOR_ADDR_END	    (uint32_t)0x081FFFFF
#define DEC							(uint8_t)0
#define HEX							(uint8_t)1

using namespace std;

HANDLE hSerial;

typedef enum
{
	ERR = 0,
	COMSELECT,
	START,
	COMMAND,
	PARAM,
	COMMEXEC
}STAGE;

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
void clear_buff(uint8_t* buff);
void sendMSG(uint8_t*txd, uint8_t len);
void readMSG(DWORD size);
uint32_t verifMSG(uint8_t* msg, uint8_t* msg2, uint32_t len);
STAGE com_select(void);
STAGE comm_est(void);
STAGE command_form(void);
STAGE param_transmit(void);
STAGE param_transmit(void);

static uint8_t rx_buff[64] = { 0 };
static char buff[64] = { 0 };
const char *cmp_buff[] = {
				"Server is ready\n", //17
				"Clear All",
				"Clear Sector",
				"Clear Page",
				"Read FLASH",
				"Write Sector",
				"Write Page",
				"Recieve massage: " };

static struct _TxBuff
{
	uint8_t lengh_msg;
	int size_flash_area;
	uint8_t comm;
	uint8_t sector_start;
	uint8_t sector_end;
	uint32_t flash_address_start;
	uint32_t flash_address_end;
	uint32_t pattern;
	uint8_t* tx_data = NULL;
}transData;

wchar_t name[] = { L'C',L'O',L'M',L'0',L'\0',L'\0' };
wchar_t number[] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6' ,L'7' ,L'8' ,L'9' };
LPCTSTR sPortName;



STAGE stage;
//uint8_t* uartMSG = NULL;

int main()
{
//	uint8_t repeat_action_flag = 1;
//	uint8_t recData;
//	uint8_t err = 0;
//	uint8_t len = 0;
	/* Scanning of COM-ports, setup parameters	*/
/*	while(repeat_action_flag)
	{ 
		clear_buff(rx_buff);
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

	*/
	////////////////////////////////////////////////////////////////
	//  comm with server////////////////////////////////
/*
	repeat_action_flag = 1;
	while (repeat_action_flag)
	{
		sendMSG((uint8_t*)"COM",4);
		ReadCOM(16);
		if (verifMSG(rx_buff, (uint8_t*)cmp_buff[0], 15) == 0)
		{
			printf("%s \n", rx_buff);
			clear_buff(rx_buff);
			sendMSG((uint8_t*)"OK",2);
			repeat_action_flag = 0;
		}
	}
*/
	/* recieve command  */
/*	repeat_action_flag = 1;
	while (repeat_action_flag)
	{
		clear_buff(rx_buff);
		printf("Enter the command:\n");
		printf("\t : clear all\\sector\\page	NOTHING\\number(dec)\\address(hex)\n");
		printf("\t : read start_address(hex) end_address(hex)\n");
		printf("\t : write sector\\page number(dec)\\start_address(hex) NOTHING\\end_address(hex)\n ");
// Считывание командной строки
		if ((len = read_command(buff)) )
		{
// Обработка сообщения
			if (prep_uart_msg(len - 1) != NULL)
			{
				repeat_action_flag = 0;
				if (transData.comm == 2)
				{
					printf("Clear SECTOR %d\n", transData.sector_start); 
				//	sendMSG(&transData.comm, 1); sendMSG(&transData.lengh_msg, 1);
				}
				else if (transData.comm == 3)
				{
					printf("Clear PAGE address = 0x 0%x\n", transData.flash_address_start);
					
					//sendMSG()
				}
				else if (transData.comm == 4)
				{
					printf("Read from 0x%x to 0x%x\n",transData.flash_address_start,transData.flash_address_end);
					
					//sendMSG()
				}
				else if (transData.comm == 5)
				{
					printf("Write Page 0x%x 0x%x\n",transData.flash_address_start,transData.pattern);
//					for (uint8_t i = 0; i < 8; i++)
	//				{
		//				printf("%x", (transData.tx_data[i]));
			//		}  
					
					
					//sendMSG()
				}
				else if (transData.comm == 6)
				{
					printf("Write Sector\n");
					//sendMSG()
				}
				//				printf("MSG READY  \n") ;// sendMSG()
			}
// Единственная команда нулевой длины
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
		sendMSG(&transData.comm, 1); sendMSG(&transData.lengh_msg, 1);
		return 0;
	}

*/
// Обмен с сервером
/*	repeat_action_flag = 1;
	while (repeat_action_flag)
	{
		uint8_t m[2] = { transData.comm ,transData.lengh_msg };
		sendMSG(m, 2);
		//sendMSG(&(transData.lengh_msg), 1);
		if (verifMSG(m, 2))
		{
			printf("ERROR of verif\n");
			repeat_action_flag = 0;
		}
	}

	*/
//	free(uart_msg);
//	getchar();
stage = COMSELECT;
	while (1)
	{
		switch (stage)//ERR = 0, COMSELECT,START, COMMAND, PARAM
		{
		case ERR: return 1; break;
		case COMSELECT: stage  = com_select(); break;
		case START: stage = comm_est(); break;
		case COMMAND: stage = command_form(); break;//uartMSG = malloc()
		case PARAM: stage = param_transmit(); break;
		case COMMEXEC: break;
//		case: break;
		default: break;
		}

	}
	return 0;
}

/* Scanning of COM-ports, setup parameters	*/
STAGE com_select(void)
{
//	uint8_t err = 0;
	clear_buff(rx_buff);
	if (serial_init() != 0)
	{
		printf("ERROR SerialPortInit! Press any key for repeat or (N) for exit");
		name[4] = '\0';
		char c = getchar();
		if (c == 'N' || c == 'n') return ERR;
	}
	else
	{
		stage = START;
		printf("Init COM%c%c OK\n", name[3], name[4]);
	}
	return stage;
}

uint8_t serial_init(void)
{
	uint8_t er = 1;
	printf(" the follows COM ports are available: ");
	for (int ind = 0; ind < 100; ++ind)
	{
		if (ind < 10)
		{
			name[3] = number[ind];
		}
		else
		{
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
//				buff[0] = '\0';
//				buff[1] = '\0';
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
// установка соединения с сервером
STAGE comm_est(void)
{
	sendMSG((uint8_t*)"COM", 4);
	readMSG(16);
//	ReadCOM(16);
	if (verifMSG(rx_buff, (uint8_t*)cmp_buff[0], 15) == 0)
	{
		printf("%s \n", rx_buff);
		clear_buff(rx_buff);
		sendMSG((uint8_t*)"OK", 2);
		return COMMAND;
	}
	else return START;
}

STAGE command_form(void)
{
	
	uint8_t len = 0;
	clear_buff(rx_buff);
	printf("Enter the command:\n");
	printf("\t : clear all\\sector\\page	NOTHING\\number(dec)\\address(hex)\n");
	printf("\t : read start_address(hex) end_address(hex)\n");
	printf("\t : write sector\\page number(dec)\\start_address(hex) NOTHING\\end_address(hex)\n ");
	// Считывание командной строки
	if ((len = read_command(buff)))
	{
		// Обработка сообщения
		prep_uart_msg(len - 1);
		if (transData.tx_data != NULL)///////////указатель на сообщение!!!!!!!
		{
			if (transData.comm == 2)
			{
				printf("Clear SECTOR %d\n", transData.sector_start);
			}
			else if (transData.comm == 3)
			{
				printf("Clear PAGE address = 0x 0%x\n", transData.flash_address_start);
			}
			else if (transData.comm == 4)
			{
				printf("Read from 0x%x to 0x%x\n", transData.flash_address_start, transData.flash_address_end);
			}
			else if (transData.comm == 5)
			{
				printf("Write Page 0x%x 0x%x\n", transData.flash_address_start, transData.pattern);
				/*					for (uint8_t i = 0; i < 8; i++)
									{
										printf("%x", (transData.tx_data[i]));
									}  */


									//sendMSG()
			}
			else if (transData.comm == 6)
			{
				printf("Write Sector\n");
				//sendMSG()
			}
			//				printf("MSG READY  \n") ;// sendMSG()
		}
		// Единственная команда нулевой длины
		else if (transData.comm == 1)
		{
			printf("CLear ALL\n");// sendMSG()
		}
		else
		{
			printf("Uncorrect input! Press any key for repeat or (N) for exit");

			char c = getchar();
			if (c == 'N' || c == 'n') return ERR;
		}
	}
	else
	{
		printf("Uncorrect input! Press any key for repeat or (N) for exit");
		char c = getchar();
		if (c == 'N' || c == 'n') return ERR;
	}
	sendMSG(&transData.comm, 1); sendMSG(&transData.lengh_msg, 1);
	readMSG(2);
	if ((rx_buff[0] == transData.comm) && (rx_buff[1] == transData.lengh_msg))
	{		
		rx_buff[0] = 0; rx_buff[1] = 0;
		return PARAM;
	}
	else return ERR;

}

STAGE param_transmit(void)
{
	sendMSG(transData.tx_data, transData.lengh_msg);
	readMSG(transData.lengh_msg);
	if (verifMSG(transData.tx_data, rx_buff, transData.lengh_msg !=0)) printf("ERROR verif PARAM!\n");/////////////////////

	printf(" verif PARAM! %u\n", rx_buff);
	return ERR;
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
	///передав коману и длину плате, получить подтверждение. После передачи команды и адреса получить подтверждение из от платы. 
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
		case 'A': transData.comm = 1; transData.lengh_msg = 0; break;//comm1
// clear page address size( in bytes )
		case 'P': /*transData.comm = 2; transData.lengh_msg = 4;*/ i = find_separ(i + 1, size - 1);//comm

			if (number_of_digit(&buff[i], HEX) != 8)
			{
				printf("Uncorrect Address input\n");
				return NULL;
			}

			transData.comm = 3; transData.lengh_msg = 4;
			transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
			tx_buff_form(transData.tx_data, &buff[i], transData.lengh_msg);

			for (i = 0; i < 4; i++)
			{
				transData.flash_address_start = (transData.flash_address_start << 8) | *(transData.tx_data + i);;
			}
			if ((transData.flash_address_start < FLASH_SECTOR_ADDR_START) || (transData.flash_address_start > FLASH_SECTOR_ADDR_END))
			{
				printf("Wrong Address!\n");
				return NULL;
			}
			else
			{
				///////////////////////////////
//				printf("BUFF %s", buff);


				uint32_t addr_korr = transData.flash_address_start % 4;
				if (addr_korr)transData.flash_address_start = transData.flash_address_start - addr_korr;
			}
			break;
		case 'S':
		{
			transData.comm = 2; transData.lengh_msg = 1; i = find_separ(i + 1, size - 1);
			if (is_digit(buff + i, 2) == 0)
			{
				st[0] = buff[i]; st[1] = buff[i + 1];
				transData.sector_start = atoi(st);
				if ((transData.sector_start <= FLASH_SECTOR_MAX) && (transData.sector_start >= FLASH_SECTOR_MIN))
				{
					//					transData.sector_start =  sector; transData.sector_end = sector;
						//				uint8_t size = transData.lengh_msg;
					transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
					//					tx_buff_form(transData.tx_data, &transData.sector_start, transData.lengh_msg);
					*(transData.tx_data) = transData.sector_start;
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
	case 'R':
	{
		// Get Start_Address
		i = find_separ(i + 1, size - 1);
		if (number_of_digit(&buff[i], HEX) != 8)
		{
			printf("Uncorrect Start_Address input\n");
			return NULL;
		}
		transData.comm = 4; transData.lengh_msg = 8;
		transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
		tx_buff_form(transData.tx_data, &buff[i], transData.lengh_msg);
		for (i = 0; i < 4; i++)
		{
			transData.flash_address_start = (transData.flash_address_start << 8) | *(transData.tx_data + i);;
		}
		if ((transData.flash_address_start < FLASH_SECTOR_ADDR_START) || (transData.flash_address_start > FLASH_SECTOR_ADDR_END))
		{
			printf("Wrong Start_Address!\n");
			return NULL;
		}
		else
		{
			uint32_t addr_korr = transData.flash_address_start % 4;
			if (addr_korr)transData.flash_address_start = transData.flash_address_start - addr_korr;
		}
		//Get End_Address
		i = find_separ(i, size - 1);
		if (number_of_digit(&buff[i], HEX) != 8)
		{
			printf("Uncorrect End_Address input\n");
			return NULL;
		}
		tx_buff_form(transData.tx_data+4, &buff[i], transData.lengh_msg);
		for (i = 0; i < 4; i++)
		{
			transData.flash_address_end = (transData.flash_address_end << 8) | *(transData.tx_data + i);;
		}
		if ((transData.flash_address_end < FLASH_SECTOR_ADDR_START) || (transData.flash_address_end > FLASH_SECTOR_ADDR_END))
		{
			printf("Wrong End_Address!\n");
			return NULL;
		}
		else
		{
			uint32_t addr_korr = transData.flash_address_end % 4;
			if (addr_korr)transData.flash_address_end = transData.flash_address_end - addr_korr;
		}
		break;
	}
	case 'W':
	{
		i = find_separ(i, size - 1);
		switch (buff[i])
		{
		case 'P':
		{
			// Get Address	
			i = find_separ(i, size - 1);
			if (number_of_digit(&buff[i], HEX) != 8)
			{
				printf("Uncorrect Address input\n");
				return NULL;
			}

			transData.comm = 5; transData.lengh_msg = 8;
			transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
			tx_buff_form(transData.tx_data, &buff[i], transData.lengh_msg);

			for (i = 0; i < 4; i++)
			{
				transData.flash_address_start = (transData.flash_address_start << 8) | *(transData.tx_data + i);;
			}
			if ((transData.flash_address_start < FLASH_SECTOR_ADDR_START) || (transData.flash_address_start > FLASH_SECTOR_ADDR_END))
			{
				printf("Wrong Address!\n");
				return NULL;
			}
			else
			{
				///////////////////////////////
				printf("BUFF %s", buff);
			}
			//Get Pattern
			i = find_separ(i, size - 1);
			if (number_of_digit(&buff[i], HEX) != 8)
			{
				printf("Uncorrect Pattern input\n");
				return NULL;
			}
			tx_buff_form(transData.tx_data + 4, &buff[i], transData.lengh_msg);
			for (i = 0; i < 4; i++)
			{
				transData.pattern = (transData.pattern << 8) | *(transData.tx_data + i);;
			}
			break;
		}
		break;
		}
//	default: return NULL;
		break;
	}
	default: return NULL;
	return transData.tx_data;
	}
		
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
//		printf("ARRisdigit %c\n", *arr); arr++;
	}
	return err;
}

void tx_buff_form(uint8_t * buf, char* data, uint8_t size)
{
	buf[0] = char_to_uint8(data);
	buf[1] = char_to_uint8(data + 2);
	buf[2] = char_to_uint8(data + 4);
	buf[3] = char_to_uint8(data + 6);
/////////////////////////////////////////////////////
//	printf("%x %x %x %x\n",buf[0], buf[1],buf[2],buf[3]);
///////////////////////////////////////////////////////
}

uint8_t number_of_digit(char* arr, uint8_t type)
{
	uint8_t cnt = 0;
	if (type )
	{ 
		while (((arr[cnt] > 0x2f) && (arr[cnt] < 0x3a)) || ((arr[cnt] < 'G') && (arr[cnt] > '@')))
		{
//			putchar(arr[cnt]);
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

void clear_buff(uint8_t* buff)
{
	uint8_t i = 0;
	while (i < 64)
	{		
		buff[i] = 0;
		i++;
	}
}


void sendMSG(uint8_t* txd, uint8_t len)
{
	
	DWORD dwSize = len;   // размер 
	DWORD dwBytesWritten;    // тут будет количество собственно переданных байт
	BOOL iRet = WriteFile(hSerial, txd, dwSize, &dwBytesWritten, NULL);
}
void readMSG(DWORD size)
{
	DWORD iSize;
	ReadFile(hSerial, rx_buff, size, &iSize, 0);

}



uint8_t WriteCOM(uint8_t* data)
{
	DWORD dwSize = sizeof(data);   // размер этой строки
	DWORD dwBytesWritten;    // тут будет количество собственно переданных байт
	BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
	return 0;
}

uint32_t verifMSG(uint8_t* msg, uint8_t* msg2, uint32_t len)
{
	uint32_t err = 0;
	while (len --)
	{
		if (*(msg++) != *(msg2++)) err++;
		//msg++;		
	}


	return err;
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
