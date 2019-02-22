#pragma once


#ifndef _STM23F429FLASH
#define _STM23F429FLASH

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


#endif