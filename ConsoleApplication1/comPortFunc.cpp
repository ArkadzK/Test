#include "pch.h"
#include <Windows.h>
#include "comPortFunc.h"



extern uint8_t rx_buff[64];
extern uint32_t error;
extern uint8_t* flash_data_buffer;
extern uint8_t* recovery_buffer_st;
extern uint8_t* recovery_buffer_end;
extern STAGE stage;
HANDLE hSerial;
FILE *pFile;
LPCTSTR sPortName;
wchar_t name[] = { L'\\',L'\\',L'.',L'\\', L'C',L'O',L'M',L'0',L'\0',L'\0' };
const wchar_t number[] = { L'0',L'1',L'2',L'3',L'4',L'5',L'6' ,L'7' ,L'8' ,L'9' };
extern errno_t err;

STAGE com_select(void)
{
	clear_buff(rx_buff, 64);
	if (serial_init() != 0)
	{
		printf("ERROR SerialPortInit! Press any key for repeat or (N) for exit");
		name[8] = '\0';
		uint8_t c = 0;
		c = read_command(buff);
		if (buff[0] == 'N' || buff[0] == 'n')
		{
			clear_buff((uint8_t*)buff, c);
			return ERR;
		}
		else
		{
			clear_buff((uint8_t*)buff, c);
			return PORTSELECT;
		}
	}
	else
	{
		printf("Init COM%c%c OK\n", name[7], name[8]);
	}
	return START;
}

STAGE comm_est(void)
{
	//	sendMSG((uint8_t*)"COM", 4);//////////////////////////////////////
	sendMSG((uint8_t*)"CO", 2);
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
		///////////////////////////////////////////////////////////////////////

		while (len < 2)
		{
			len = read_command(buff);
			if (len == 1) printf("Empty entry. Repeat\nInput the number of COM");
		}
		if (len < 3)
		{
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
	}
	return er;
}

void sendMSG(uint8_t* txd, uint32_t len)
{
	DWORD dwSize = len;   
	DWORD dwBytesWritten;    
	BOOL iRet = WriteFile(hSerial, txd, dwSize, &dwBytesWritten, NULL);
}

void readMSG(DWORD size)
{
	DWORD iSize;
	ReadFile(hSerial, rx_buff, size, &iSize, 0);
}




uint8_t send_cmd_CS(uint8_t sect_st, uint8_t sect_end)
{
	uint8_t err = 2;
	sendMSG(&err, 1); sendMSG(&err, 1);
	readMSG(2);
	if ((err != rx_buff[0]) || (err != rx_buff[1]))error = 5;
	err = 0;
	rx_buff[0] = 0; rx_buff[1] = 0;
	sendMSG(&sect_st, 1);
	sendMSG(&sect_end, 1);
	readMSG(2);
	if ((sect_st != rx_buff[0]) || (sect_st != rx_buff[1]))error = 5;
	readMSG(4);
	if (verifMSG((uint8_t*)"CSOK", rx_buff, 4) != 0)
	{
		error = (uint32_t)rx_buff;
		printf(" CLEAR SECTOR error = %x\n", error);
	}
	clear_buff(rx_buff, 4);
	return err;
}

uint8_t send_cmd_RP(uint32_t st_addr, uint32_t end_addr, const char* file_name)
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
	sendMSG(&err, 1);// send command Write Page and number of Bytes 
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
	readMSG(4);//  wate for ServerReady signal

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
