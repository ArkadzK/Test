// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//https://msdn.microsoft.com/en-us/library/ff802693.aspx?f=255&MSPPError=-2147217396
//http://qaru.site/questions/34929/cannot-find-or-open-the-pdb-file-in-visual-studio-c-2010

#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



//#define PCOM(a)		COM##a
#define FLASH_SECTOR_MIN			12
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
void select_act(void);
//uint8_t* prep_uart_msg(uint8_t size);
void prep_comm(uint8_t size);
uint8_t find_separ(uint8_t i, uint8_t limit);
uint8_t is_digit(char* arr, uint8_t len);
uint8_t is_digit_hex(char* arr, uint8_t len);
void tx_buff_form(uint8_t* buf, char* data, uint8_t size);
uint8_t number_of_digit(char* arr, uint8_t type);
uint8_t char_to_uint8(char* arr);
void uin32_to_uint8(uint8_t* buf, uint32_t* data);
void clear_buff(uint8_t* buff, uint32_t lenght);
void sendMSG(uint8_t*txd, uint32_t len);
void readMSG(DWORD size);
uint32_t verifMSG(uint8_t* msg, uint8_t* msg2, uint32_t len);
STAGE com_select(void);
STAGE comm_est(void);
STAGE command_form(void);
//STAGE param_transmit(void);//???????????????????
STAGE command_execut(void);
//uint8_t read_address(char* buf, uint8_t* addr, uint32_t* data, uint8_t size);
uint8_t address_form(char* buf, uint32_t* data, uint8_t size);
uint8_t sector_form(char* buf, uint8_t* data, uint8_t size);
//void corr_address(uint8_t* addr, uint32_t* data);
uint8_t get_sector(uint32_t address);
uint32_t get_sector_size(uint8_t sector);
uint32_t get_sector_address(uint8_t sector);
void buffer_file(uint32_t size);
uint8_t send_cmd_CS(uint8_t sect_st, uint8_t sect_end);
//uint8_t send_cmd_RP(uint32_t st_addr, uint32_t end_addr/*, uint8_t* data*/);
uint8_t send_cmd_RP(uint32_t st_addr, uint32_t end_addr, uint8_t* data, const char* file_name);
uint8_t send_cmd_WP(uint32_t st_addr, uint32_t end_addr, uint8_t* data);
uint32_t buffer_is_not_cleared(uint8_t* buff, uint32_t length);
uint32_t page_is_busy(uint32_t address_start, uint32_t address_end, uint8_t* buff, uint8_t* sect_busy);

static uint8_t rx_buff[64] = { 0 };
static char buff[64] = { 0 };
/*
const char *cmp_buff[] = {
				"Server is ready\n", //17
				"Clear All",
				"Clear Sector",
				"Clear Page",
				"Read FLASH",
				"Write Sector",
				"Write Page",
				"Recieve massage: " };
*/
static struct _TxBuff
{

	uint32_t flash_address_start;
	uint32_t flash_address_end;
	uint32_t flash_sector_address_start;//////////////// 
	uint32_t flash_sector_address_end;//////////////////
	uint8_t lengh_msg;
	uint8_t comm;
	uint8_t sector_start;
	uint8_t sector_end;
	//	uint8_t* tx_data = NULL;

}transData;

wchar_t name[] = { L'\\',L'\\',L'.',L'\\', L'C',L'O',L'M',L'0',L'\0',L'\0' };
wchar_t number[] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6' ,L'7' ,L'8' ,L'9' };
LPCTSTR sPortName;
char filename[40] = { '\0' };

COMMAND command;
STAGE stage;
static uint32_t error = 0;//1 - uncorrect address input,2- wrong address,3- wrong sector,4 -wrong input,5-UNKNOWN Command
uint8_t* flash_data_buffer;
uint8_t* recovery_buffer_st;
uint8_t* recovery_buffer_end;
FILE *pFile;
errno_t err;

int main()
{
	stage = PORTSELECT;
	while (1)
	{
		switch (stage)//ERR = 0, PORTSELECT,START, COMM, COMMEXEC
		{
		case ERR: return 1; break;
		case PORTSELECT: stage = com_select(); break;
		case START: stage = comm_est(); break;//+
		case COMM: stage = command_form(); break;// 
		case COMMEXEC: error = 0; stage = command_execut(); break;
		default: break;
		}
	}
	return 0;
}

/* Scanning of COM-ports, setup parameters	*/
STAGE com_select(void)
{
	clear_buff(rx_buff, 64);
	if (serial_init() != 0)
	{
		printf("ERROR SerialPortInit! Press any key for repeat or (N) for exit");
		name[8] = '\0';
		char c = getchar();
		if (c == 'N' || c == 'n') return ERR;
		else return PORTSELECT;
	}
	else
	{
		printf("Init COM%c%c OK\n", name[7], name[8]);
	}
	return START;
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
			/*			if (GetLastError() == ERROR_FILE_NOT_FOUND)
						{
							printf("serial port %d does not exist.\n", ind);
							//return err = 1;
						}
						printf("some other error occurred.\n");			*/
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
		if ((len = read_command(buff)) < 3)
			if (is_digit(buff, len) == 0)
			{
				name[7] = number[(uint8_t)(buff[0] - '0')];
				if (buff[1] == '\n') name[8] = '\0';
				else name[8] = number[(uint8_t)(buff[1] - '0')];
				//			name[8] = (buff[1] ? number[(uint8_t)(buff[1] - '0')] : '\0');
							//				buff[0] = '\0';
							//				buff[1] = '\0';
				sPortName = name;
				hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
				if (hSerial == INVALID_HANDLE_VALUE)
				{
					CloseHandle(hSerial);
					printf("ERROR of opening COM%c%c\n", name[7], name[8]);
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
					dcbSerialParams.BaudRate = CBR_115200;//CBR_9600;//
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
	if (verifMSG(rx_buff, (uint8_t*)"Server is ready\n", 15) == 0)
	{
		printf("%s \n", rx_buff);
		clear_buff(rx_buff, 16);
		sendMSG((uint8_t*)"OK", 2);
		return COMM;
	}
	else return START;
}
// 
STAGE command_form(void)
{
	uint8_t len = 0;
	//clear_buff(rx_buff,64);
	printf("Enter the command:\n");
	printf("\t : clear all\\sector\\page	NOTHING\\number(dec)\\start_address(hex) end_address(hex)\n");
	printf("\t : read start_address(hex) end_address(hex)\n");
	printf("\t : write pege\\sector address(hex)\\sector(dec)  address(hex)\\nothing\n");
	printf("\t : write address(for test) to flash_buffer_file: start_address(hex) end_address(hex)\n ");
	// Считывание командной строки
	if ((len = read_command(buff)))
	{
		// Обработка сообщения
		prep_comm(len - 1);
		if (transData.comm == 1)
		{
			printf("CLear ALL\n");
		}
		else if (transData.comm == 2)
		{
			printf("Clear SECTOR %d %d\n", transData.sector_start, transData.sector_end);
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
			printf("Write Sector %d \n", transData.sector_start);
		}
		else if (transData.comm == 6)
		{
			printf("Write Page 0x%x 0x%x\n", transData.flash_address_start, transData.flash_address_end);
		}
		else if (transData.comm == 7)
		{
			printf("Write Address to flash (for test) 0x%x 0x%x\n", transData.flash_address_start, transData.flash_address_end);
		}
		else
		{
			printf("Uncorrect input! Press any key for repeat or (N) for exit");
			char c = getchar();
			if (c == 'N' || c == 'n') exit(1);
		}
	}
	else
	{
		printf("Uncorrect input! Press any key for repeat or (N) for exit");
		char c = getchar();
		if (c == 'N' || c == 'n') exit(1);
	}
	if (error)
	{
		printf("Error command_form()%d\n", error);
		error = 0;
		stage = COMM;
	}
	else stage = COMMEXEC;
	return stage;
}

void prep_comm(uint8_t size)
{
	uint8_t i = 0;
	char st[3] = { 0 };
	switch (buff[0])
	{
	case 'C':
	{
		i = find_separ(i + 1, size - 1);
		switch (buff[i])
		{
		case 'A':	//Clear All
			transData.comm = 1;
			transData.lengh_msg = 0;
			break;
		case 'S':
			transData.comm = 2;
			transData.lengh_msg = 2;
			i = sector_form(buff + i, &transData.sector_start, size);
			i = sector_form(buff + i, &transData.sector_end, size);
			break;
		case 'P':
			transData.comm = 3;
			//				transData.lengh_msg = 8;
			i = address_form(buff + i, &transData.flash_address_start, size);
			i = address_form(buff + i, &transData.flash_address_end, size);
			transData.sector_start = get_sector(transData.flash_address_start);
			transData.sector_end = get_sector(transData.flash_address_end);
			transData.flash_sector_address_start = get_sector_address(transData.sector_start);
			transData.flash_sector_address_end = get_sector_address(transData.sector_end) + get_sector_size(transData.sector_end) - 4;
			break;
		default:
			printf("UNKNOWN Command\n");
			error = 5;
			break;
		}
		break;
	}
	case 'R':
	{
		transData.comm = 4;
		transData.lengh_msg = 8;
		i = address_form(buff + i, &transData.flash_address_start, size);
		i = address_form(buff + i, &transData.flash_address_end, size);
		break;
	}
	case 'W':
	{
		i = find_separ(i + 1, size - 1);
		switch (buff[i])
		{
		case 'S':
			transData.comm = 5;
			sector_form(buff + i, &transData.sector_start, size);
			transData.flash_sector_address_start = get_sector_address(transData.sector_start);
			transData.flash_sector_address_end = transData.flash_sector_address_start + get_sector_size(transData.sector_start) - 4;
			break;
		case 'P':
			transData.comm = 6;
			i = address_form(buff + i, &transData.flash_address_start, size);
			i = address_form(buff + i, &transData.flash_address_end, size);
			transData.sector_start = get_sector(transData.flash_address_start);
			transData.sector_end = get_sector(transData.flash_address_end);
			transData.flash_sector_address_start = get_sector_address(transData.sector_start);
			transData.flash_sector_address_end = get_sector_address(transData.sector_end) + get_sector_size(transData.sector_end) - 4;
			break;
			// тестовый режим записи адреса ячейки во flash
		case 'A':
			transData.comm = 7;
			i = address_form(buff + i, &transData.flash_address_start, size);
			i = address_form(buff + i, &transData.flash_address_end, size);
			transData.lengh_msg = 8;
			break;
		default:
			printf("UNKNOWN Command\n");
			error = 5;
			break;
		}
		break;
	}
	default:
		printf("UNKNOWN Command\n");
		error = 5;
		break;
	}
}

STAGE command_execut(void)
{
	//	uint8_t d = 0;
	uint32_t ind = 0;
	uint8_t sect;
	uint8_t sect_busy[24] = { 0 };
	uint32_t i;
	switch (transData.comm)
	{
	case 1:
		sendMSG(&transData.comm, 1); sendMSG(&transData.lengh_msg, 1);
		readMSG(2);
		if ((transData.comm == rx_buff[0]) && (transData.lengh_msg == rx_buff[1]) == 0)error = 5;
		rx_buff[0] = 0; rx_buff[1] = 0;
		readMSG(4);
		if (verifMSG((uint8_t*)"CLOK", rx_buff, 4) != 0)
		{
			error = (uint32_t)rx_buff;
			printf("CLEAR ALL error = %d\n", error);
		}
		else printf("CLEAR ALL is OK\n");
		clear_buff(rx_buff, 4);
		//		stage = COMM;
		break;
	case 2: // Clear Sectors
	{
		send_cmd_CS(transData.sector_start, transData.sector_end);
		//			stage = COMM;
		break;
	}
	case 3: // Clear Page  - вычитать сектора в буфер, очистить их, записать флэш по адресам вне страницы из буфера
	{
		///////////////////////// ВАРИАНТ С созданием одного буфера , обнулением страницы и записью во flash
		uint32_t ind;
		//			uint8_t sect;
		uint32_t size = transData.flash_sector_address_end - transData.flash_sector_address_start + 4;
		flash_data_buffer = (uint8_t*)malloc(size);
		send_cmd_RP(transData.flash_sector_address_start, transData.flash_sector_address_end, flash_data_buffer, "flash_buffer_file");
		readMSG(4);
		if (verifMSG((uint8_t*)"EOF", rx_buff, 4) != 0)
		{
			error = (uint32_t)rx_buff;
			printf("Error of buffering = %d\n", error);
		}
		size = transData.flash_address_end - transData.flash_address_start + 4;
		ind = transData.flash_address_start - transData.flash_sector_address_start;
		uint32_t i;
		while (ind < size)
		{
			i = buffer_is_not_cleared(&flash_data_buffer[ind], size - ind - 4);
			if (i)
			{
				ind += i;
				sect = get_sector(transData.flash_sector_address_start + ind);
				//				printf("currentaddress=%08X\t", ind + transData.flash_sector_address_start);
				sect_busy[sect] = 1;
				if (sect < 23)
				{
					ind = get_sector_address(sect + 1) - transData.flash_sector_address_start;
					//				printf("next_address=%08X\n", ind + transData.flash_sector_address_start);
				}
			}
			else break;
		}
		// очистка секторов 
		ind = transData.sector_start;
		for (ind = transData.sector_start; ind <= transData.sector_end; ind++)
		{
			if (sect_busy[ind])
			{
				printf(" send CS%d\n", ind);////////////////////////////////////////////
				send_cmd_CS(ind, ind);
			}
		}
		// восстановление участков вне страницы очистки
		if (send_cmd_WP(transData.flash_sector_address_start, transData.flash_address_start - 4, flash_data_buffer))
		{
			printf("Error of recovery sector %d\n", transData.sector_start);
		}
		else printf("Recovery sector %d is OK\n", transData.sector_start);
		ind = transData.flash_address_end - transData.flash_sector_address_start + 4;
		if (send_cmd_WP(transData.flash_address_end + 4, transData.flash_sector_address_end, &flash_data_buffer[ind]))
		{
			printf("Error of recovery sector %d\n", transData.sector_end);
		}
		else printf("Recovery sector %d is OK\n", transData.sector_end);
		free(flash_data_buffer);
		break;
	}
	case 4: //read flash from address to address  - работает!
	{
		send_cmd_RP(transData.flash_address_start, transData.flash_address_end, flash_data_buffer, "flash_buffer_file");
		readMSG(4);
		if (verifMSG((uint8_t*)"EOF", rx_buff, 4) != 0)
		{
			error = (uint32_t)rx_buff;
			printf("Error of buffering = %d\n", error);
		}
		break;
	}

	case 5: // write sector - работает
	{
		uint32_t size = get_sector_size(transData.sector_start);
		printf("Enter the filename with data for writing\n");
		scanf_s("%s", filename, 40);
		getchar();						// очищаем буфер ввода от '\n'
		printf("%s\n", filename);
		flash_data_buffer = (uint8_t*)malloc(size);
		send_cmd_RP(transData.flash_sector_address_start, transData.flash_sector_address_end, flash_data_buffer, "flash_buffer_file");
		readMSG(4);
		if (verifMSG((uint8_t*)"EOF", rx_buff, 4) != 0)
		{
			error = (uint32_t)rx_buff;
			printf("Error of buffering = %d\n", error);
		}
		if (buffer_is_not_cleared(flash_data_buffer, size))
		{
			send_cmd_CS(transData.sector_start, transData.sector_start);
		}
		fclose(pFile);
		if ((err = (uint32_t)fopen_s(&pFile, filename, "r+")) != NULL)
		{
			printf("ERROR of opening FILE\n");
			return COMM;
		}
		for (uint32_t i = 0; i < size; i++)
		{
			fscanf_s(pFile, "%02x", (flash_data_buffer + i), size);
		}
		fclose(pFile);
		if (send_cmd_WP(transData.flash_sector_address_start, transData.flash_sector_address_end, flash_data_buffer))
		{
			printf("Error of Write Sector%d\n", error);
		}
		printf("Write Sector%d OK\n", transData.sector_start);
		if (flash_data_buffer) free(flash_data_buffer);
		break;
	}
	case 6: // write page from address to address
	{
		/////////////////////////////////////////
		uint8_t* recovery_buff_begin;
		uint8_t* recovery_buff_end;
		uint32_t address;
		/////////////////////////////
		uint32_t ind;
		//			uint8_t sect;
		uint32_t size = transData.flash_sector_address_end - transData.flash_sector_address_start + 4;
		printf("Enter the filename with data for writing\n");
		scanf_s("%s", filename, 40);
		getchar();						// очищаем буфер ввода от '\n'
		printf("%s\n", filename);
		flash_data_buffer = (uint8_t*)malloc(size);
		send_cmd_RP(transData.flash_sector_address_start, transData.flash_sector_address_end, flash_data_buffer, "page_buffer_file");
		readMSG(4);
		if (verifMSG((uint8_t*)"EOF", rx_buff, 4) != 0)
		{
			error = (uint32_t)rx_buff;
			printf("Error of buffering = %d\n", error);
		}
		fclose(pFile);
		uint32_t size_b = transData.flash_address_start - transData.flash_sector_address_start;	//////////////////////////////////////////////////////////////
		recovery_buff_begin = (uint8_t*)malloc(size_b);
		if (size_b)
		{
			printf("Recovery Buffer_begin:\n");
			address = transData.flash_sector_address_start;

			for (ind = 0; address < transData.flash_address_start; ind++)
			{
				recovery_buff_begin[ind] = flash_data_buffer[ind];
				if (address % 16 == 0)printf("\n Address %08x : ", address);
				if (address % 4 == 0) printf("   ");
				printf("%02x ", recovery_buff_begin[ind]);
				address++;
			}
			printf("\n");
		}
		uint32_t size_e = transData.flash_sector_address_end - transData.flash_address_end;
		recovery_buff_end = (uint8_t*)malloc(size_e);
		if (size_e)
		{
			address = transData.flash_address_end + 4;

			printf("Recovery Buffer_end:\n");
			i = 0;
			for (ind = (address - transData.flash_sector_address_start); address < transData.flash_sector_address_end + 4; ind++)
			{
				recovery_buff_end[i] = flash_data_buffer[ind];
				if (address % 16 == 0)printf("\n Address %08x : ", address);
				if (address % 4 == 0) printf("   ");
				printf("%02x ", recovery_buff_end[i]); i++;
				address++;
			}
		}
		free(flash_data_buffer);
		size = transData.flash_address_end - transData.flash_address_start + 4;
		flash_data_buffer = (uint8_t*)malloc(size);
		if ((err = (uint32_t)fopen_s(&pFile, filename, "r+")) != NULL)
		{
			printf("ERROR of opening FILE %s\n", filename);
			return COMM;
		}
		printf("flash_data_buffer_:\n");
		address = transData.flash_address_start;
		for (ind = 0; ind < size; ind++)
		{
			fscanf_s(pFile, "%02x", (flash_data_buffer + ind), size);
			if (ind % 16 == 0)printf("\n Address %08x :   ", address + ind);
			if (ind % 4 == 0) printf("   ");
			printf("%02x", flash_data_buffer[ind]);
		}
		fclose(pFile);
		size = transData.flash_address_end - transData.flash_address_start + 4;
		ind = transData.flash_address_start - transData.flash_sector_address_start;
		uint32_t i;
		while (ind < size)
		{
			i = buffer_is_not_cleared(&flash_data_buffer[ind], size - ind - 4);
			if (i)
			{
				ind += i;
				sect = get_sector(transData.flash_sector_address_start + ind);
				//				printf("currentaddress=%08X\t", ind + transData.flash_sector_address_start);
				sect_busy[sect] = 1;
				if (sect < 23)
				{
					ind = get_sector_address(sect + 1) - transData.flash_sector_address_start;
					//				printf("next_address=%08X\n", ind + transData.flash_sector_address_start);
				}
			}
			else break;
		}
		ind = transData.sector_start;
		for (ind = transData.sector_start; ind <= transData.sector_end; ind++)
		{
			if (sect_busy[ind])
			{
				printf(" send CS%d\n", ind);////////////////////////////////////////////
				send_cmd_CS(ind, ind);
			}
		}
		if (size_b)
		{
			if (send_cmd_WP(transData.flash_sector_address_start, transData.flash_address_start - 4, recovery_buff_begin))
			{
				printf("Error of Write recovery_buff_begin %08x to %08x OK\n", transData.flash_sector_address_start, transData.flash_address_start);
			}
			else printf("Write recovery_buff_begin OK\n");
		}
		if (size_e)
		{
			if (send_cmd_WP(transData.flash_address_end + 4, transData.flash_sector_address_end, recovery_buff_end))
			{
				printf("Error of Write Pagefrom address %08x to %08x OK\n", transData.flash_address_start, transData.flash_address_end);
			}
			else printf("Write recovery_buff_end OK\n");
		}
		if (size)
		{
			if (send_cmd_WP(transData.flash_address_start, transData.flash_address_end, flash_data_buffer))
			{
				printf("Error of Write Pagefrom address %08x to %08x OK\n", transData.flash_address_start, transData.flash_address_end);
			}
			else printf("Write flash_data_buffer OK\n");
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*			size = transData.flash_address_end - transData.flash_address_start + 4;
					ind = transData.flash_address_start - transData.flash_sector_address_start;
					uint32_t i;
					while (ind < size)
					{
						i = buffer_is_not_cleared(&flash_data_buffer[ind], size - ind - 4);
						if (i)
						{
							ind += i;
							sect = get_sector(transData.flash_sector_address_start + ind);
							//				printf("currentaddress=%08X\t", ind + transData.flash_sector_address_start);
							sect_busy[sect] = 1;
							if (sect < 23)
							{
								ind = get_sector_address(sect + 1) - transData.flash_sector_address_start;
								//				printf("next_address=%08X\n", ind + transData.flash_sector_address_start);
							}
						}
						else break;
					}
					// очистка секторов
					ind = transData.sector_start;
					for (ind = transData.sector_start; ind <= transData.sector_end; ind++)
					{
						if (sect_busy[ind])
						{
							printf(" send CS%d\n", ind);////////////////////////////////////////////
							send_cmd_CS(ind, ind);
						}
					}
					// формирование буфера для записи
					ind = transData.flash_address_start - transData.flash_sector_address_start;// size не менялся
					if ((err = (uint32_t)fopen_s(&pFile, filename, "r+")) != NULL)
					{
						printf("ERROR of opening FILE %s\n", filename);
						return COMM;
					}
					uint32_t ind_max = transData.flash_address_end - transData.flash_sector_address_start + 1;
					size = ind_max - ind;
					while (ind < ind_max)
					{
						fscanf_s(pFile, "%02x", (flash_data_buffer + ind), size);
						ind++;
					}
					fclose(pFile);
		////////////////////////////////////////////////////////////////////////////////////////////
					size = transData.flash_sector_address_end - transData.flash_sector_address_start + 4;
					for (ind = 0; ind < size; ind++)
					{
						if ((ind) % 16 == 0) printf("\n A %08x :   ", ind + transData.flash_sector_address_start);
						printf("%02x", flash_data_buffer[ind]);
						if ((ind + 1) % 4 == 0) printf("   ");

					}
		////////////////////////////////////////////////////////////////////////////////////////////
					if (send_cmd_WP(transData.flash_address_start, transData.flash_address_end, flash_data_buffer))
					{
						printf("Error of Write Pagefrom address %08x to %08x OK\n", transData.flash_address_start, transData.flash_address_end);
					}
			*/	//	printf("Write Page from address %08x to %08x OK\n", transData.flash_address_start, transData.flash_address_end);
		break;
	}
	case 7:
	{
		if ((err = (uint32_t)fopen_s(&pFile, "flash_buffer_file", "w+")) != NULL)
		{
			printf("ERROR of opening FILE\n");
		}
		for (uint32_t i = transData.flash_address_start; i < transData.flash_address_end + 1;)
		{
			fprintf(pFile, "%02x", *(uint8_t*)&i);
			fprintf(pFile, "%02x", *((uint8_t*)&i + 1));
			fprintf(pFile, "%02x", *((uint8_t*)&i + 2));
			fprintf(pFile, "%02x", *((uint8_t*)&i + 3));
			i += 4;
		}
		fclose(pFile);
		break;
	}
	}
	return COMM;
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

void uin32_to_uint8(uint8_t* buf, uint32_t* data)
{
	buf[0] = *(uint8_t*)data;
	buf[1] = *((uint8_t*)data + 1);
	buf[2] = *((uint8_t*)data + 2);
	buf[3] = *((uint8_t*)data + 3);
}
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
	} while ((c != '\0') && (c != '\n'));
	return len;
}

void select_act(void)
{
	char* ptr_arr = buff;
	while ((*ptr_arr != '\0') && (*ptr_arr != '\n'))
	{
		ptr_arr++;
	}
}

uint8_t find_separ(uint8_t i, uint8_t limit)
{
	while ((((buff[i] > '/') && (buff[i] < ':')) || ((buff[i] > '@') && (buff[i] < '['))/* ||((buff[i] >='a')&&(buff[i] <'{'))*/) && (i < limit))
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
	}
	return err;
}

void tx_buff_form(uint8_t * buf, char* data, uint8_t size)
{
	buf[0] = char_to_uint8(data + 6);
	buf[1] = char_to_uint8(data + 4);
	buf[2] = char_to_uint8(data + 2);
	buf[3] = char_to_uint8(data);
}

uint8_t number_of_digit(char* arr, uint8_t type)
{
	uint8_t cnt = 0;
	if (type)
	{
		while (((arr[cnt] > 0x2f) && (arr[cnt] < 0x3a)) || ((arr[cnt] < 'G') && (arr[cnt] > '@')))
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

uint8_t char_to_uint8(char* arr)
{
	uint8_t d;
	if ((*arr > 0x2f) && (*arr < 0x3a)) d = (uint8_t)((*arr - '0') * 16);
	else d = (uint8_t)((*arr - 55) * 16);
	if ((*(arr + 1) > 0x2f) && (*(arr + 1) < 0x3a)) d = d + (uint8_t)(*(arr + 1) - '0');
	else d = d + (uint8_t)(*(arr + 1) - 55);
	return d;
}

void clear_buff(uint8_t* buff, uint32_t lenght)
{
	uint8_t i = 0;
	while (i < lenght)
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
	DWORD dwSize = sizeof(data);
	DWORD dwBytesWritten;
	BOOL iRet = WriteFile(hSerial, data, dwSize, &dwBytesWritten, NULL);
	return 0;
}

uint32_t verifMSG(uint8_t* msg, uint8_t* msg2, uint32_t len)
{
	uint32_t err = 0;
	while (len--)
	{
		if (*(msg++) != *(msg2++)) err++;
	}
	return err;
}

uint8_t address_form(char* buf, uint32_t* data, uint8_t size)
{
	uint8_t i = buf - &buff[0];
	i = find_separ(i + 1, size - 1);
	if (number_of_digit(&buff[i], HEX) != 8)
	{
		printf("Uncorrect Address input\n");
		error = 1;
	}
	*(uint8_t*)data = char_to_uint8(&buff[i] + 6);
	*(((uint8_t*)data) + 1) = char_to_uint8(&buff[i] + 4);
	*(((uint8_t*)data) + 2) = char_to_uint8(&buff[i] + 2);
	*(((uint8_t*)data) + 3) = char_to_uint8(&buff[i]);
	if ((*data < FLASH_SECTOR_ADDR_START) || (*data > FLASH_SECTOR_ADDR_END))
	{
		printf("Wrong Address!\n");
		error = 2;
	}
	*data = *data - *data % 4;
	return i;
}

uint8_t sector_form(char* buf, uint8_t* data, uint8_t size)
{
	uint8_t i = buf - &buff[0];
	char st[2] = { 0 };
	i = find_separ(i + 1, size - 1);
	if (is_digit(buff + i, 2) == 0)
	{
		st[0] = buff[i]; st[1] = buff[i + 1];
		*data = atoi(st);
		if ((*data > FLASH_SECTOR_MAX) || (*data < FLASH_SECTOR_MIN))
		{
			printf("WRONG Sector number! %d\n", *data);////////////////////////////////////////////
			error = 3;
		}
	}
	else if (data == &transData.sector_start)
	{
		printf("WRONG Sector format!\n");
		error = 4;
	}
	else transData.sector_end = transData.sector_start;
	return i;
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
void buffer_file(uint32_t size)
{
	DWORD iSize;
	flash_data_buffer = (uint8_t*)malloc(size);
	ReadFile(hSerial, flash_data_buffer, size, &iSize, 0);
	for (uint32_t i = 0; i < size;)
	{
		fprintf(pFile, "%02x", *(flash_data_buffer + i)); i += 1;
	}
	if (transData.comm == 4) free(flash_data_buffer);
}
uint8_t send_cmd_CS(uint8_t sect_st, uint8_t sect_end)
{
	uint8_t err = 2;
	sendMSG(&err, 1); sendMSG(&err, 1);
	readMSG(2);// верификация команды и длины данных
	if ((err != rx_buff[0]) || (err != rx_buff[1]))error = 5;
	err = 0;
	rx_buff[0] = 0; rx_buff[1] = 0;
	sendMSG(&sect_st, 1);
	sendMSG(&sect_end, 1);
	readMSG(2);
	if ((sect_st != rx_buff[0]) || (sect_st != rx_buff[1]))error = 5;
	readMSG(4);
	if (verifMSG((uint8_t*)"CSOK", rx_buff, transData.lengh_msg) != 0)
	{
		error = (uint32_t)rx_buff;
		printf(" CLEAR SECTOR error = %x\n", error);
	}
	clear_buff(rx_buff, 4);
	return err;
}

uint8_t send_cmd_RP(uint32_t st_addr, uint32_t end_addr, uint8_t* data, const char* file_name)
{
	if ((err = (uint32_t)fopen_s(&pFile, file_name, "w+")) != NULL)
	{
		printf("ERROR of opening FILE\n");
	}
	uint8_t err = 0;
	err = 3;
	sendMSG(&err, 1);
	err = 8;
	sendMSG(&err, 1);
	readMSG(2);
	if (((3 == rx_buff[0]) || (err == rx_buff[1])) == 0)
	{
		error = 5;
	}
	else err = 0;
	rx_buff[0] = 0; rx_buff[1] = 0;
	printf("Command_RP is transmit\n");
	uin32_to_uint8(rx_buff, &st_addr);
	uin32_to_uint8(&rx_buff[4], &end_addr);
	sendMSG(rx_buff, 8);
	clear_buff(rx_buff, 8);
	readMSG(8);
	buffer_file(end_addr - st_addr + 4);
	fclose(pFile);
	return err;
}

uint8_t send_cmd_WP(uint32_t st_addr, uint32_t end_addr, uint8_t* data)
{
	uint32_t size_d = 0;
	uint32_t ind = 0;
	uint8_t err = 4;
	sendMSG(&err, 1);
	err = 8;
	sendMSG(&err, 1);// отправка команды Write Page и количества байт 
	readMSG(2);
	if ((4 == rx_buff[0]) && (err == rx_buff[1]) == 0)err = 5;
	else err = 0;
	rx_buff[0] = 0; rx_buff[1] = 0;
	sendMSG((uint8_t*)&st_addr, 4);
	sendMSG((uint8_t*)&end_addr, 4);
	readMSG(8);
	if (verifMSG((uint8_t*)&st_addr, rx_buff, 4))printf("Error of verif St_addr\n");
	if (verifMSG((uint8_t*)&end_addr, &rx_buff[4], 4))printf("Error of verif end_addr\n");
	size_d = end_addr - st_addr + 4;
	readMSG(4);//  ожидание сигнала готовности сервера к приёму

	if (verifMSG((uint8_t*)"RDRV", rx_buff, 4) != 0)
	{
		error = (uint32_t)rx_buff;
		printf(" Server is not ready for WP\n");
	}
	uint32_t size_c = size_d - size_d % 1024;
	if (size_d / 1024)
	{
		for (ind = 0; ind < size_c;)
		{
			sendMSG(&data[ind], 1024);
			readMSG(4);
			ind += 1024;
			if (verifMSG((uint8_t*)"WROK", rx_buff, 4) != 0)
			{
				error = (uint32_t)rx_buff;
				printf("Error %x Write 1kFrame addr=%x\n", error, transData.flash_address_start + 1024 * ind);
				stage = COMM;
			}
		}
	}
	clear_buff(rx_buff, 4);/////////////////////////////////////////////////////////////////
	if (size_d % 1024)
	{
		sendMSG(&data[ind], size_d % 1024);
	}
	//	sendMSG((uint8_t*)"EOF", 4);
	readMSG(4);
	if (verifMSG((uint8_t*)"EOWR", rx_buff, 4) != 0)
	{
		error = (uint32_t)rx_buff;
		printf("Error %d Write Frame addr=%d\n", error, transData.flash_address_start + ind);
	}
	return err;
}

void send_cmd_CP(void)
{


}

uint32_t buffer_is_not_cleared(uint8_t* buff, uint32_t length)
{
	uint32_t i = 0;
	while (length--)
	{
		if ((buff[i] != 0xff) || (buff[i + 1] != 0xff) || (buff[i + 2] != 0xff) || (buff[i + 3] != 0xff)) return i + 1;
		i += 4;
	}
	return 0;// буфер свободен
}

uint32_t page_is_busy(uint32_t address_start, uint32_t address_end, uint8_t* buff, uint8_t* sect_busy)
{
	uint32_t size = address_end - address_start + 4;
	uint32_t ind = transData.flash_address_start - transData.flash_sector_address_start;
	uint32_t ret = ind;
	uint8_t sect = 0;
	uint32_t i;
	while (ind < size)
	{
		i = buffer_is_not_cleared(&buff[ind], size - ind - 4);
		if (i)
		{
			ind += i;
			sect = get_sector(transData.flash_sector_address_start + ind);
			//				printf("currentaddress=%08X\t", ind + transData.flash_sector_address_start);
			sect_busy[sect] = 1;
			if (sect < 23)
			{
				ind = get_sector_address(sect + 1) - transData.flash_sector_address_start;
				//				printf("next_address=%08X\n", ind + transData.flash_sector_address_start);
			}
		}
		else break;
	}
	return ind - ret;
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

