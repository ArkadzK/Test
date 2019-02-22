#include "stm32f4flash.h"

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