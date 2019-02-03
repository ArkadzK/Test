// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//https://msdn.microsoft.com/en-us/library/ff802693.aspx?f=255&MSPPError=-2147217396

// PARAM - не правильно передаётся второй адрес при пережаче команды чтения флэш

//#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



//#define PCOM(a)		COM##a
#define FLASH_SECTOR_MIN			13
#define FLASH_SECTOR_MAX			23
#define FLASH_SECTOR_ADDR_START		(uint32_t)0x08100000
#define FLASH_SECTOR_ADDR_END	    (uint32_t)0x081FFFFF
#define DEC							(uint8_t)0
#define HEX							(uint8_t)1

#define FLASH_SECTOR_0     ((uint8_t) 0)   /*!< Sector Number 0   */
#define FLASH_SECTOR_1     ((uint8_t) 1)   /*!< Sector Number 1   */
#define FLASH_SECTOR_2     ((uint8_t) 2)   /*!< Sector Number 2   */
#define FLASH_SECTOR_3     ((uint8_t) 3)   /*!< Sector Number 3   */
#define FLASH_SECTOR_4     ((uint8_t) 4)   /*!< Sector Number 4   */
#define FLASH_SECTOR_5     ((uint8_t) 5)   /*!< Sector Number 5   */
#define FLASH_SECTOR_6     ((uint8_t) 6)   /*!< Sector Number 6   */
#define FLASH_SECTOR_7     ((uint8_t) 7)   /*!< Sector Number 7   */
#define FLASH_SECTOR_8     ((uint8_t) 8)   /*!< Sector Number 8   */
#define FLASH_SECTOR_9     ((uint8_t) 9)   /*!< Sector Number 9   */
#define FLASH_SECTOR_10    ((uint8_t) 10)  /*!< Sector Number 10  */
#define FLASH_SECTOR_11    ((uint8_t) 11)  /*!< Sector Number 11  */
#define FLASH_SECTOR_12    ((uint8_t) 12)  /*!< Sector Number 12  */
#define FLASH_SECTOR_13    ((uint8_t) 13)  /*!< Sector Number 13  */
#define FLASH_SECTOR_14    ((uint8_t) 14)  /*!< Sector Number 14  */
#define FLASH_SECTOR_15    ((uint8_t) 15)  /*!< Sector Number 15  */
#define FLASH_SECTOR_16    ((uint8_t) 16)  /*!< Sector Number 16  */
#define FLASH_SECTOR_17    ((uint8_t) 17)  /*!< Sector Number 17  */
#define FLASH_SECTOR_18    ((uint8_t) 18)  /*!< Sector Number 18  */
#define FLASH_SECTOR_19    ((uint8_t) 19)  /*!< Sector Number 19  */
#define FLASH_SECTOR_20    ((uint8_t) 20)  /*!< Sector Number 20  */
#define FLASH_SECTOR_21    ((uint8_t) 21)  /*!< Sector Number 21  */
#define FLASH_SECTOR_22    ((uint8_t) 22)  /*!< Sector Number 22  */
#define FLASH_SECTOR_23    ((uint8_t) 23)  /*!< Sector Number 23  */

/*Base address of the Flash sectors Bank 1 */
#define ADDR_FLASH_SECTOR_0		((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

/* Base address of the Flash sectors Bank 2 */
#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x08100000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x08104000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x08108000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0810C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_16     ((uint32_t)0x08110000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_17     ((uint32_t)0x08120000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18     ((uint32_t)0x08140000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19     ((uint32_t)0x08160000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20     ((uint32_t)0x08180000) /* Base @ of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_21     ((uint32_t)0x081A0000) /* Base @ of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_22     ((uint32_t)0x081C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23     ((uint32_t)0x081E0000) /* Base @ of Sector 11, 128 Kbytes */



using namespace std;

HANDLE hSerial;
typedef enum
{
	CLEAR_ALL,
	CLEAR_SECTOR,
	READ,
	WRITE
} COMMAND;

typedef enum
{
	ERR = 0,
	PORTSELECT,
	START,
	COMM,
//	PARAM,
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
void sendMSG(uint8_t*txd, uint32_t len);
void readMSG(DWORD size);
uint32_t verifMSG(uint8_t* msg, uint8_t* msg2, uint32_t len);
STAGE com_select(void);
STAGE comm_est(void);
STAGE command_form(void);
STAGE param_transmit(void);//???????????????????
STAGE command_execut(void);
uint8_t read_address(char* buf, uint8_t* addr, uint32_t* data, uint8_t size);
void corr_address(uint8_t* addr, uint32_t* data);
uint8_t get_sector(uint32_t address);
uint32_t get_sector_size(uint8_t sector);
uint32_t get_sector_address(uint8_t sector);
uint32_t buffer_file(uint32_t st_addr, uint32_t end_addr);

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

wchar_t name[] = {L'\\',L'\\',L'.',L'\\', L'C',L'O',L'M',L'0',L'\0',L'\0' };
wchar_t number[] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6' ,L'7' ,L'8' ,L'9' };
LPCTSTR sPortName;


COMMAND command;
STAGE stage;
uint8_t error = 0;
uint8_t* flash_data_buffer;
FILE *pFile;
errno_t err;

int main()
{

	
	
//	free(uart_msg);
//	getchar();
	stage =PORTSELECT; // COMM;

	while (1)
	{
		if (error) stage = (STAGE)(error-1);
		switch (stage)//ERR = 0, PORTSELECT,START, COMM,// PARAM
		{
		case ERR: return 1; break;
		case PORTSELECT: stage  = com_select(); break;
		case START: stage = comm_est(); break;
		case COMM: stage = command_form(); break;//uartMSG = malloc()
//		case PARAM: error = 0; stage = param_transmit(); break;
		case COMMEXEC: error = 0; stage = command_execut(); break;
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
		printf("Init COM%c%c OK\n", name[7], name[8]);
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
			name[7] = number[ind];
		}
		else
		{
			name[8] = number[ind % 10];
			name[7] = number[ind / 10];
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
				name[7] = number[(uint8_t)(buff[0] - '0')];
				name[8] = (buff[1]? number[(uint8_t)(buff[1] - '0')] : '\0');
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
		return COMM;
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
				printf("Clear PAGE address_start = 0x 0%x  address_end = 0x 0%x\n", transData.flash_address_start, transData.flash_address_end);
			}
			else if (transData.comm == 4)
			{
				printf("Read from 0x%x to 0x%x\n", transData.flash_address_start, transData.flash_address_end);
			}
			else if (transData.comm == 5)//
			{
				printf("Write Sector\n");				
			}
			else if (transData.comm == 6)
			{
				printf("Write Page 0x%x 0x%x\n", transData.flash_address_start, transData.flash_address_end);
			}
			stage = COMMEXEC;//PARAM;
			
		}
		// Единственная команда нулевой длины
		else if (transData.comm == 1)
		{
			printf("CLear ALL\n");// sendMSG()
			stage = COMMEXEC;
		}
		else
		{
			printf("Uncorrect input! Press any key for repeat or (N) for exit");

			char c = getchar();
			if (c == 'N' || c == 'n') stage = ERR;
			else stage = COMM;
		}
	}
	else
	{
		printf("Uncorrect input! Press any key for repeat or (N) for exit");
		char c = getchar();
		if (c == 'N' || c == 'n') return ERR;//ВЫХОД
		else stage = COMM;
	}

/////////////////////////////////////ПЕРЕНЕСЕНО В COMMEXEC//////////////////////////////////////////////
/*
	sendMSG(&transData.comm, 1); sendMSG(&transData.lengh_msg, 1);// перенести в COMMEXEC
	readMSG(2);
	if ((rx_buff[0] == transData.comm) && (rx_buff[1] == transData.lengh_msg))
	{		
		rx_buff[0] = 0; rx_buff[1] = 0;
//		return PARAM;
	}
	else printf("Error of Command verification \n");// завести сервер в рестарт!!!!!
*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	return stage;

}

STAGE param_transmit(void)
{
	sendMSG(transData.tx_data, transData.lengh_msg);
	readMSG(transData.lengh_msg);
	if (verifMSG(transData.tx_data, rx_buff, transData.lengh_msg) != 0)
	{
		printf("ERROR verif PARAM!\n");
		error = 4;
	}
	printf("PARAM transmit OK!\n");//////////////////////////////////////////////
	free(transData.tx_data);
	clear_buff(rx_buff);
	return COMMEXEC;
}

STAGE command_execut(void)
{
	static volatile uint8_t step = 0;/////////////////////// шаг выполнения комбинированной команды
	uint32_t size;
	switch (transData.comm)
	{
	case 1: 
		readMSG(2); 
		printf("CLEAR ALL is OK\n"); 
		stage = COMM; 
		break;
	case 2: // Clear Sector
		{
			readMSG(1);
			if (rx_buff[0])
			{
				printf("ERROR of CLEARING\n"); error = 4;
			}
			else stage = COMM; printf("CLEARING is OK\n");
			break;
		}
	case 3: // Clear Page  - вычитать сектора в буфер, очистить их, записать флэш по адресам страницы из буфера
		{
			transData.sector_start = get_sector(transData.flash_address_start);
			transData.sector_end = get_sector(transData.flash_address_end);

			//////////////////////////////////////УДАЛЕНО ДЛЯ ПЕРЕДЕЛКИ
/*			transData.sector_start = get_sector(transData.flash_address_start);
			transData.sector_end = get_sector(transData.flash_address_end);
//			if (transData.sector_start == transData.sector_end)
//			{
			size = get_sector_address(transData.sector_end + 1) - get_sector_address(transData.sector_start);
			flash_data_buffer = (uint8_t*)malloc(size);
			DWORD iSize;
			sendMSG((uint8_t*)"ST", 2);
			ReadFile(hSerial, flash_data_buffer, size, &iSize, 0);
			readMSG(4);// "EOF"
			if (verifMSG((uint8_t*)"EOF", rx_buff, 4) != 0) error = 6;
			sendMSG((uint8_t*)"CS", 2);
			rx_buff[0] = 0; rx_buff[1] = 0; rx_buff[2] = 0; rx_buff[3] = 0;
			readMSG(2);// подтверждение очистки
			sendMSG((uint8_t*)flash_data_buffer, size);
			readMSG(4);//"EOP"
			if (verifMSG((uint8_t*)"EOP", rx_buff, 4) != 0) error = 6;
			rx_buff[0] = 0; rx_buff[1] = 0; rx_buff[2] = 0; rx_buff[3] = 0;
//			}
//			else
//			{
	
//			}
*/			break;
		}
	case 4: //read flash from address to address
		{
			if (buffer_file(transData.flash_address_start, transData.flash_address_end) != NULL)
			{
			printf("ERROR of opening FILE\n");
			stage = COMM;
			}
			break;
		}
	case 5: // write sector
		{
			size = get_sector_size(transData.sector_start);
			flash_data_buffer = (uint8_t*)malloc(size);
			if ((err = fopen_s(&pFile, "flash_buffer_file", "w+")) != NULL)
			{
				printf("ERROR of opening FILE\n");
				exit(1);
			}
			fscanf_s(pFile, "%x", flash_data_buffer, size);
			uint32_t address = get_sector_address(transData.sector_start);
			uint32_t address_end = get_sector_address(transData.sector_start) + get_sector_size(transData.sector_start) + 4;
			uint32_t ind = 0;
			while (address < address_end)
			{
				sendMSG((uint8_t*)&flash_data_buffer[ind], 1024);
				ind += 1024;
				readMSG(4);
				if (verifMSG((uint8_t*)"NEXT", rx_buff, 4) != 0) printf("ERROR write flash %x\n", *(uint32_t*)rx_buff);
			}
			readMSG(4);
			if (verifMSG((uint8_t*)"WROK", rx_buff, 4) != 0) printf("ERROR write flash %x\n", *(uint32_t*)rx_buff);
			else printf("WRITE OK\n");
		}
		break;
	
	case 6: // write page from address to address
		{
			size = transData.flash_address_end - transData.flash_address_start + 4;
			flash_data_buffer = (uint8_t*)malloc(size);
			if ((err = fopen_s(&pFile, "flash_buffer_file", "r")) != NULL)
			{
				printf("ERROR of opening FILE\n");
				stage = COMM;
			}
			
			for (uint32_t i = 0; i < size;)
			{
				fscanf_s(pFile, "%02x", (flash_data_buffer + i), size);
				//fscanf_s(pFile, "%08x", (uint32_t*)(flash_data_buffer+i), size);
				//i += 4;
//				printf("%02x", *(flash_data_buffer + i));
				i += 1;
			}
			break;
		}
	}
	stage = COMM;
	return stage;
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
	///передав команду и длину плате, получить подтверждение. После передачи команды и адреса получить подтверждение из от платы. 
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
			case 'A': 
				transData.comm = 1;
				transData.lengh_msg = 0;
				transData.tx_data = NULL; 
				break;//comm1
// clear page address size( in bytes )
			case 'P':
				transData.comm = 3; transData.lengh_msg = 8;
				transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
				i = read_address(&buff[i], transData.tx_data, &transData.flash_address_start, size); 
				if (error) stage = COMM;
				i = read_address(&buff[i], transData.tx_data + 4, &transData.flash_address_end, size); 
				if ( error ) stage = COMM;
				break;
			case 'S':
				{
					transData.comm = 2; 
					transData.lengh_msg = 1; 
					i = find_separ(i + 1, size - 1);
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
							transData.tx_data = (uint8_t*) &transData.sector_start;
						}
						else
						{
							printf("WRONG Sector number!\n");
							transData.tx_data = NULL;
						}
					}
					else
					{
						printf("WRONG Sector format!\n");
						transData.tx_data = NULL;
					}
					break;
				}	
			default: 
				printf("ERROR_Clear command\n");
				transData.tx_data = NULL;
				break;
			}
		} break;
	case 'R':
		{
		
			transData.comm = 4; transData.lengh_msg = 8;
			transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
			// Get Start_Address
			i = read_address(&buff[i], transData.tx_data, &transData.flash_address_start, size);
			if (error) stage = COMM;
			// Get End_Address
			i = read_address(&buff[i], transData.tx_data + 4, &transData.flash_address_end, size);
			if (error) stage = COMM;
			break;
		}
	case 'W':
		{
			i = find_separ(i, size - 1);
			switch (buff[i])
			{
			case 'S':
				{
					transData.comm = 5; transData.lengh_msg = 1; i = find_separ(i + 1, size - 1);
					if (is_digit(buff + i, 2) == 0)
					{
						st[0] = buff[i]; st[1] = buff[i + 1];
						transData.sector_start = atoi(st);
						if ((transData.sector_start <= FLASH_SECTOR_MAX) && (transData.sector_start >= FLASH_SECTOR_MIN))
						{
//							transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);					
							transData.tx_data = (uint8_t*)&transData.sector_start;
						}
						else
						{
							printf("WRONG Sector number!\n");
							transData.tx_data = NULL;
						}
					}
					else
					{
						printf("WRONG Sector format!\n"); 
						transData.tx_data = NULL;
					}
					break;	
				}
			case 'P':
				{
					// Get Address	
/*					i = find_separ(i, size - 1);
					if (number_of_digit(&buff[i], HEX) != 8)
					{
						printf("Uncorrect Address input\n");
						return NULL;
					}
*/
					transData.comm = 6; transData.lengh_msg = 8; //transData.lengh_msg = 12
					transData.tx_data = (uint8_t*)malloc(transData.lengh_msg);
					i = read_address(&buff[i], transData.tx_data, &transData.flash_address_start, size);
					if (error) stage = COMM;
					i = read_address(&buff[i], transData.tx_data + 4, &transData.flash_address_end, size);
					if (error) stage = COMM;
	
/*					tx_buff_form(transData.tx_data, &buff[i], transData.lengh_msg);

					for (i = 0; i < 4; i++)	
					{
						transData.flash_address_start = (transData.flash_address_start << 8) | *(transData.tx_data + i);
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
*/
					//Get Pattern
/*					i = find_separ(i, size - 1);
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
*/					break;
				}
				break;
			}
//		    default: return NULL;
			break;
		}
		default: transData.tx_data = NULL;
	
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
//		printf("ARRisdigit %c\n", *arr); arr++;
	}
	return err;
}

void tx_buff_form(uint8_t * buf, char* data, uint8_t size)
{
	buf[0] = char_to_uint8(data + 6);
	buf[1] = char_to_uint8(data + 4);
	buf[2] = char_to_uint8(data + 2);
	buf[3] = char_to_uint8(data);
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

void sendMSG(uint8_t* txd, uint32_t len)
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
	}
	return err;
}

uint8_t read_address(char* buf,uint8_t* addr, uint32_t* data, uint8_t size)
{
	uint8_t i = buf - &buff[0];
	i = find_separ(i + 1, size - 1);
	if (number_of_digit(&buff[i], HEX) != 8)
	{
		printf("Uncorrect Address input\n");
		return NULL;
	}

	tx_buff_form(addr, &buff[i], transData.lengh_msg);
	corr_address(addr, data);
	if ((*data < FLASH_SECTOR_ADDR_START) || (*data > FLASH_SECTOR_ADDR_END))
	{
		printf("Wrong Address!\n");
		error = 4;
	}
	return i;
}

void corr_address(uint8_t* addr, uint32_t* data)
{
	uint32_t corr = (*(uint32_t*)addr) % 4;
	*data = *(uint32_t*)addr - corr;
	*addr -= (uint8_t)corr;
}

uint8_t get_sector(uint32_t address)
{
	uint8_t sector = 0;

	if ((address < ADDR_FLASH_SECTOR_1) && (address >= ADDR_FLASH_SECTOR_0))
	{
		sector = FLASH_SECTOR_0;
	}
	else if ((address < ADDR_FLASH_SECTOR_2) && (address >= ADDR_FLASH_SECTOR_1))
	{
		sector = FLASH_SECTOR_1;
	}
	else if ((address < ADDR_FLASH_SECTOR_3) && (address >= ADDR_FLASH_SECTOR_2))
	{
		sector = FLASH_SECTOR_2;
	}
	else if ((address < ADDR_FLASH_SECTOR_4) && (address >= ADDR_FLASH_SECTOR_3))
	{
		sector = FLASH_SECTOR_3;
	}
	else if ((address < ADDR_FLASH_SECTOR_5) && (address >= ADDR_FLASH_SECTOR_4))
	{
		sector = FLASH_SECTOR_4;
	}
	else if ((address < ADDR_FLASH_SECTOR_6) && (address >= ADDR_FLASH_SECTOR_5))
	{
		sector = FLASH_SECTOR_5;
	}
	else if ((address < ADDR_FLASH_SECTOR_7) && (address >= ADDR_FLASH_SECTOR_6))
	{
		sector = FLASH_SECTOR_6;
	}
	else if ((address < ADDR_FLASH_SECTOR_8) && (address >= ADDR_FLASH_SECTOR_7))
	{
		sector = FLASH_SECTOR_7;
	}
	else if ((address < ADDR_FLASH_SECTOR_9) && (address >= ADDR_FLASH_SECTOR_8))
	{
		sector = FLASH_SECTOR_8;
	}
	else if ((address < ADDR_FLASH_SECTOR_10) && (address >= ADDR_FLASH_SECTOR_9))
	{
		sector = FLASH_SECTOR_9;
	}
	else if ((address < ADDR_FLASH_SECTOR_11) && (address >= ADDR_FLASH_SECTOR_10))
	{
		sector = FLASH_SECTOR_10;
	}
	else if ((address < ADDR_FLASH_SECTOR_12) && (address >= ADDR_FLASH_SECTOR_11))
	{
		sector = FLASH_SECTOR_11;
	}
	else if ((address < ADDR_FLASH_SECTOR_13) && (address >= ADDR_FLASH_SECTOR_12))
	{
		sector = FLASH_SECTOR_12;
	}
	else if ((address < ADDR_FLASH_SECTOR_14) && (address >= ADDR_FLASH_SECTOR_13))
	{
		sector = FLASH_SECTOR_13;
	}
	else if ((address < ADDR_FLASH_SECTOR_15) && (address >= ADDR_FLASH_SECTOR_14))
	{
		sector = FLASH_SECTOR_14;
	}
	else if ((address < ADDR_FLASH_SECTOR_16) && (address >= ADDR_FLASH_SECTOR_15))
	{
		sector = FLASH_SECTOR_15;
	}
	else if ((address < ADDR_FLASH_SECTOR_17) && (address >= ADDR_FLASH_SECTOR_16))
	{
		sector = FLASH_SECTOR_16;
	}
	else if ((address < ADDR_FLASH_SECTOR_18) && (address >= ADDR_FLASH_SECTOR_17))
	{
		sector = FLASH_SECTOR_17;
	}
	else if ((address < ADDR_FLASH_SECTOR_19) && (address >= ADDR_FLASH_SECTOR_18))
	{
		sector = FLASH_SECTOR_18;
	}
	else if ((address < ADDR_FLASH_SECTOR_20) && (address >= ADDR_FLASH_SECTOR_19))
	{
		sector = FLASH_SECTOR_19;
	}
	else if ((address < ADDR_FLASH_SECTOR_21) && (address >= ADDR_FLASH_SECTOR_20))
	{
		sector = FLASH_SECTOR_20;
	}
	else if ((address < ADDR_FLASH_SECTOR_22) && (address >= ADDR_FLASH_SECTOR_21))
	{
		sector = FLASH_SECTOR_21;
	}
	else if ((address < ADDR_FLASH_SECTOR_23) && (address >= ADDR_FLASH_SECTOR_22))
	{
		sector = FLASH_SECTOR_22;
	}
	else /*((address < FLASH_USER_END_ADDR) && (address >= ADDR_FLASH_SECTOR_23))*/
	{
		sector = FLASH_SECTOR_23;
	}
	return sector;
}

uint32_t get_sector_size(uint8_t sector)
{
	uint32_t sectorsize = 0x00;
	if ((sector == FLASH_SECTOR_0) || (sector == FLASH_SECTOR_1) || (sector == FLASH_SECTOR_2) || \
		(sector == FLASH_SECTOR_3) || (sector == FLASH_SECTOR_12) || (sector == FLASH_SECTOR_13) || \
		(sector == FLASH_SECTOR_14) || (sector == FLASH_SECTOR_15))
	{
		sectorsize = 16 * 1024;
	}
	else if ((sector == FLASH_SECTOR_4) || (sector == FLASH_SECTOR_16))
	{
		sectorsize = 64 * 1024;
	}
	else
	{
		sectorsize = 128 * 1024;
	}
	return sectorsize;
}

uint32_t get_sector_address(uint8_t sector)
{
	uint32_t address;
	switch (sector)
	{
	case 0: address = ADDR_FLASH_SECTOR_0; break;
	case 1: address = ADDR_FLASH_SECTOR_1; break;
	case 2: address = ADDR_FLASH_SECTOR_2; break;
	case 3: address = ADDR_FLASH_SECTOR_3; break;
	case 4: address = ADDR_FLASH_SECTOR_4; break;
	case 5: address = ADDR_FLASH_SECTOR_5; break;
	case 6: address = ADDR_FLASH_SECTOR_6; break;
	case 7: address = ADDR_FLASH_SECTOR_7; break;
	case 8: address = ADDR_FLASH_SECTOR_8; break;
	case 9: address = ADDR_FLASH_SECTOR_9; break;
	case 10: address = ADDR_FLASH_SECTOR_10; break;
	case 11: address = ADDR_FLASH_SECTOR_11; break;
	case 12: address = ADDR_FLASH_SECTOR_12; break;
	case 13: address = ADDR_FLASH_SECTOR_13; break;
	case 14: address = ADDR_FLASH_SECTOR_14; break;
	case 15: address = ADDR_FLASH_SECTOR_15; break;
	case 16: address = ADDR_FLASH_SECTOR_16; break;
	case 17: address = ADDR_FLASH_SECTOR_17; break;
	case 18: address = ADDR_FLASH_SECTOR_18; break;
	case 19: address = ADDR_FLASH_SECTOR_19; break;
	case 20: address = ADDR_FLASH_SECTOR_20; break;
	case 21: address = ADDR_FLASH_SECTOR_21; break;
	case 22: address = ADDR_FLASH_SECTOR_22; break;
	case 23: address = ADDR_FLASH_SECTOR_23; break;
	default: address = 0; break;
	}
	return address;
}

uint32_t buffer_file(uint32_t st_addr, uint32_t end_addr)
{
	uint32_t size;
	uint32_t err;
	if ((err = (uint32_t)fopen_s(&pFile, "flash_buffer_file", "w+")) != NULL)
	{
		printf("ERROR of opening FILE\n");
	}
	size = transData.flash_address_end - transData.flash_address_start + 4;
	flash_data_buffer = (uint8_t*)malloc(size);
	DWORD iSize;
	ReadFile(hSerial, flash_data_buffer, size, &iSize, 0);
	for (uint32_t i = 0; i < size;)
	{
		//	fprintf(pFile, "%08x",  *(uint32_t*)(flash_data_buffer + i)); i += 4;
		fprintf(pFile, "%02x", *(flash_data_buffer + i)); i += 1;
	}
	fclose(pFile);
	free(flash_data_buffer);
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
