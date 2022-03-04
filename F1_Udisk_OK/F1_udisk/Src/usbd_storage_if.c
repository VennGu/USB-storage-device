/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @version        : v2.0_Cube
  * @brief          : Memory management layer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @defgroup USBD_STORAGE
  * @brief Usb mass storage device module
  * @{
  */

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */
static uint8_t FAT[512]={ 0xEB, 0x3C, 0x90, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2E, 0x30, 0x00, 0x02, 0x01, 0x06, 0x00, 
                          0x02, 0x00, 0x02, 0x80, 0x00, 0xF8, 0x01, 0x00, 0x3F, 0x00, 0xFF, 0x00, 0x3F, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x29, 0x15, 0xDC, 0x81, 0x66, 0x4E, 0x4F, 0x20, 0x4E, 0x41, 
                          0x4D, 0x45, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x31, 0x32, 0x20, 0x20, 0x20, 0x33, 0xC9, 
                          0x8E, 0xD1, 0xBC, 0xF0, 0x7B, 0x8E, 0xD9, 0xB8, 0x00, 0x20, 0x8E, 0xC0, 0xFC, 0xBD, 0x00, 0x7C,
                          0x38, 0x4E, 0x24, 0x7D, 0x24, 0x8B, 0xC1, 0x99, 0xE8, 0x3C, 0x01, 0x72, 0x1C, 0x83, 0xEB, 0x3A, 
                          0x66, 0xA1, 0x1C, 0x7C, 0x26, 0x66, 0x3B, 0x07, 0x26, 0x8A, 0x57, 0xFC, 0x75, 0x06, 0x80, 0xCA, 
                          0x02, 0x88, 0x56, 0x02, 0x80, 0xC3, 0x10, 0x73, 0xEB, 0x33, 0xC9, 0x8A, 0x46, 0x10, 0x98, 0xF7, 
                          0x66, 0x16, 0x03, 0x46, 0x1C, 0x13, 0x56, 0x1E, 0x03, 0x46, 0x0E, 0x13, 0xD1, 0x8B, 0x76, 0x11, 
                          0x60, 0x89, 0x46, 0xFC, 0x89, 0x56, 0xFE, 0xB8, 0x20, 0x00, 0xF7, 0xE6, 0x8B, 0x5E, 0x0B, 0x03, 
                          0xC3, 0x48, 0xF7, 0xF3, 0x01, 0x46, 0xFC, 0x11, 0x4E, 0xFE, 0x61, 0xBF, 0x00, 0x00, 0xE8, 0xE6, 
                          0x00, 0x72, 0x39, 0x26, 0x38, 0x2D, 0x74, 0x17, 0x60, 0xB1, 0x0B, 0xBE, 0xA1, 0x7D, 0xF3, 0xA6,
                          0x61, 0x74, 0x32, 0x4E, 0x74, 0x09, 0x83, 0xC7, 0x20, 0x3B, 0xFB, 0x72, 0xE6, 0xEB, 0xDC, 0xA0,
                          0xFB, 0x7D, 0xB4, 0x7D, 0x8B, 0xF0, 0xAC, 0x98, 0x40, 0x74, 0x0C, 0x48, 0x74, 0x13, 0xB4, 0x0E, 
                          0xBB, 0x07, 0x00, 0xCD, 0x10, 0xEB, 0xEF, 0xA0, 0xFD, 0x7D, 0xEB, 0xE6, 0xA0, 0xFC, 0x7D, 0xEB, 
                          0xE1, 0xCD, 0x16, 0xCD, 0x19, 0x26, 0x8B, 0x55, 0x1A, 0x52, 0xB0, 0x01, 0xBB, 0x00, 0x00, 0xE8, 
                          0x3B, 0x00, 0x72, 0xE8, 0x5B, 0x8A, 0x56, 0x24, 0xBE, 0x0B, 0x7C, 0x8B, 0xFC, 0xC7, 0x46, 0xF0, 
                          0x3D, 0x7D, 0xC7, 0x46, 0xF4, 0x29, 0x7D, 0x8C, 0xD9, 0x89, 0x4E, 0xF2, 0x89, 0x4E, 0xF6, 0xC6, 
                          0x06, 0x96, 0x7D, 0xCB, 0xEA, 0x03, 0x00, 0x00, 0x20, 0x0F, 0xB6, 0xC8, 0x66, 0x8B, 0x46, 0xF8, 
                          0x66, 0x03, 0x46, 0x1C, 0x66, 0x8B, 0xD0, 0x66, 0xC1, 0xEA, 0x10, 0xEB, 0x5E, 0x0F, 0xB6, 0xC8, 
                          0x4A, 0x4A, 0x8A, 0x46, 0x0D, 0x32, 0xE4, 0xF7, 0xE2, 0x03, 0x46, 0xFC, 0x13, 0x56, 0xFE, 0xEB, 
                          0x4A, 0x52, 0x50, 0x06, 0x53, 0x6A, 0x01, 0x6A, 0x10, 0x91, 0x8B, 0x46, 0x18, 0x96, 0x92, 0x33, 
                          0xD2, 0xF7, 0xF6, 0x91, 0xF7, 0xF6, 0x42, 0x87, 0xCA, 0xF7, 0x76, 0x1A, 0x8A, 0xF2, 0x8A, 0xE8, 
                          0xC0, 0xCC, 0x02, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0x80, 0x7E, 0x02, 0x0E, 0x75, 0x04, 0xB4, 0x42, 
                          0x8B, 0xF4, 0x8A, 0x56, 0x24, 0xCD, 0x13, 0x61, 0x61, 0x72, 0x0B, 0x40, 0x75, 0x01, 0x42, 0x03, 
                          0x5E, 0x0B, 0x49, 0x75, 0x06, 0xF8, 0xC3, 0x41, 0xBB, 0x00, 0x00, 0x60, 0x66, 0x6A, 0x00, 0xEB,
                          0xB0, 0x42, 0x4F, 0x4F, 0x54, 0x4D, 0x47, 0x52, 0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x52, 0x65, 
                          0x6D, 0x6F, 0x76, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x73, 0x20, 0x6F, 0x72, 0x20, 0x6F, 0x74, 
                          0x68, 0x65, 0x72, 0x20, 0x6D, 0x65, 0x64, 0x69, 0x61, 0x2E, 0xFF, 0x0D, 0x0A, 0x44, 0x69, 0x73, 
                          0x6B, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0xFF, 0x0D, 0x0A, 0x50, 0x72, 0x65, 0x73, 0x73, 0x20, 
                          0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x72, 0x65, 0x73, 0x74, 0x61, 
                          0x72, 0x74, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xCB, 0xD8, 0x55, 0xAA};
/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @brief Private defines.
  * @{
  */
/* USER CODE BEGIN PRIVATE_DEFINES */
#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  128
#define STORAGE_BLK_SIZ                  0x200
#define FLASH_PAGE_NBR                   32
#define FLASH_PAGE_SIZ                   0x400U
#define NUM_OF_PAGE_SIZ                  2
#define WAIT_TIMEOUT                     5000
#define FLASH_WAIT_TIMEOUT               100000
#define USB_START_ADDR                   0x08010000  
#define USB_END_ADDR                     (0x08010000+0x10000)
#define USB_USER_SIZE                    (USB_START_ADDR - USB_END_ADDR)
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Variables
  * @brief Private variables.
  * @{
  */

/* USER CODE BEGIN INQUIRY_DATA_FS */
/** USB Mass storage Standard Inquiry Data. */
const int8_t STORAGE_Inquirydata_FS[] = {/* 36 */
  
  /* LUN 0 */
  0x00,
  0x80,
  0x02,
  0x02,
  (STANDARD_INQUIRY_DATA_LEN - 5),
  0x00,
  0x00,	
  0x00,
  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
}; 
/* USER CODE END INQUIRY_DATA_FS */

/* USER CODE BEGIN PRIVATE_VARIABLES */
static uint8_t cache[NUM_OF_PAGE_SIZ][STORAGE_BLK_SIZ];
static uint8_t read_flag = 0;
static FLASH_EraseInitTypeDef USB_ZONE;
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;
int8_t STORAGE_MEMSET_MY_USB(void);
/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */
/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
/*
lun: logical unit number
*/
static int8_t STORAGE_Init_FS(uint8_t lun);
static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
static int8_t STORAGE_IsReady_FS(uint8_t lun);
static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun);
static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_FS(void);
/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
  STORAGE_Init_FS,
  STORAGE_GetCapacity_FS,
  STORAGE_IsReady_FS,
  STORAGE_IsWriteProtected_FS,
  STORAGE_Read_FS,
  STORAGE_Write_FS,
  STORAGE_GetMaxLun_FS,
  (int8_t *)STORAGE_Inquirydata_FS
};

/* Private functions ---------------------------------------------------------*/

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */
/**
  * @brief  Initializes over USB FS IP
  * @param  lun:
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Init_FS(uint8_t lun)
{
  /* USER CODE BEGIN 2 */
  HAL_StatusTypeDef Erase_status;
  HAL_FLASH_Unlock();
  return (USBD_OK);
  /* USER CODE END 2 */
}

/**
  * @brief  .
  * @param  lun: .
  * @param  block_num: .
  * @param  block_size: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  /* USER CODE BEGIN 3 */
  *block_num  = STORAGE_BLK_NBR;
  *block_size = STORAGE_BLK_SIZ;
  return (USBD_OK);
  /* USER CODE END 3 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsReady_FS(uint8_t lun)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_IsWriteProtected_FS(uint8_t lun)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 6 */
  if(lun == 0) {
	  uint32_t n , i, ADDRESS;
    ADDRESS = USB_START_ADDR + (blk_addr * STORAGE_BLK_SIZ);
 #if 0
 
    for(i =0; i < (blk_len*STORAGE_BLK_SIZ); i+=2){
      buf[i] = *((uint16_t*)(USB_START_ADDR + (blk_addr*STORAGE_BLK_SIZ)+ i));
    }
  #endif
    memcpy(buf, (uint16_t*)ADDRESS, blk_len*STORAGE_BLK_SIZ);
    return (USBD_OK);
  }
  else 
    return USBD_FAIL;
  /* USER CODE END 6 */
}

/**
  * @brief  .
  * @param  lun: .
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  /* USER CODE BEGIN 7 */
  if (lun == 0) {
    HAL_StatusTypeDef Write_status;
    uint16_t data, cpy, pat;
    volatile int k = 0; 
    uint32_t n ,i , j, ADDRESS, PAG_OF_USB_FLASH, PageStart;
    HAL_FLASH_Unlock();

    ADDRESS = USB_START_ADDR + (blk_addr*STORAGE_BLK_SIZ);
    PAG_OF_USB_FLASH = (ADDRESS - USB_START_ADDR) / 0x400U;
    PageStart = USB_START_ADDR + PAG_OF_USB_FLASH*0x400U;

    USB_ZONE.NbPages     = 1;
    USB_ZONE.PageAddress = PageStart;
    USB_ZONE.TypeErase   = FLASH_TYPEERASE_PAGES;
    uint32_t PageError   = 0;
    memset(cache, 0, 2*512);
  
    for (n = 0; n < 2; n++) {
      for(i = 0; i < 512; i += 2) {            
        cpy  = *(( uint16_t*)(PageStart + (n*512) + i));
        pat  = (cpy&0xFF00)>> 8 | (cpy&0x00FF) << 8;
        cache[n][i]   = (uint8_t)(pat>>8);
        cache[n][i+1] = (uint8_t)(pat);
      }
    }

  if(FLASH_WaitForLastOperation(FLASH_WAIT_TIMEOUT) != HAL_TIMEOUT)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);

  Write_status = HAL_FLASHEx_Erase(&USB_ZONE, &PageError);

  for (n = 0; n < blk_len; n++){         
    for(i = 0; i < STORAGE_BLK_SIZ; i++) {         
      cache[((blk_addr%2)+n)][i] = buf[ (n*512) + i ];
    }
  }
 
    
  if(0xFFFFFFFF != PageError){
    return USBD_FAIL;
  }

  if(FLASH_WaitForLastOperation(FLASH_WAIT_TIMEOUT) != HAL_TIMEOUT)
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGERR);

  
  for (n = 0; n < 2; n++){
    for(i = 0; i < 512; i += 2){  
      data = cache[n][i]  << 8 | cache[n][i+1];
      pat  = (data & 0xFF00)>> 8 | (data & 0x00FF) << 8;
      HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 
                       (PageStart + (n * STORAGE_BLK_SIZ) + i),
                       pat );//
      }
    }
    HAL_FLASH_Lock();  
    return (USBD_OK);
  }
  else 
    return USBD_FAIL;
  /* USER CODE END 7 */
}

/**
  * @brief  .
  * @param  None
  * @retval .
  */
int8_t STORAGE_GetMaxLun_FS(void)
{
  /* USER CODE BEGIN 8 */
  return (STORAGE_LUN_NBR - 1);
  /* USER CODE END 8 */
}

/**
  * @brief  .
  * @param  None
  * @retval .
  */
int8_t STORAGE_MEMSET_MY_USB(void){
  
  uint8_t sector_num;
  uint32_t Start_address, End_address;
  uint32_t n, i;
  Start_address  =   USB_START_ADDR;
  End_address    =   USB_END_ADDR;
  sector_num     = 0;

  HAL_FLASH_Unlock();
  USB_ZONE.NbPages     = 32;
  USB_ZONE.PageAddress = USB_START_ADDR;
  USB_ZONE.TypeErase   = FLASH_TYPEERASE_PAGES;
  uint32_t PageError   = 0;

  HAL_FLASHEx_Erase(&USB_ZONE, &PageError);
  if(0xFFFFFFFF != PageError) {
    printf("PageError: %x", PageError);
    return USBD_FAIL;
  } 
  
  for(sector_num = 0; sector_num < 32; sector_num++) {
    for(n = 0; n < 4; n++) {
      for(i = 0; i < STORAGE_BLK_SIZ; i+=4) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, 
                          (USB_START_ADDR + sector_num*2048 + (n * STORAGE_BLK_SIZ) + i),
                          (uint32_t)0);
    }
  }
 }
  
  USB_ZONE.NbPages     = 32;
  USB_ZONE.PageAddress = USB_START_ADDR;
  USB_ZONE.TypeErase   = FLASH_TYPEERASE_PAGES;
  HAL_FLASHEx_Erase(&USB_ZONE, &PageError);
 
  for(i = 0;i < STORAGE_BLK_SIZ;i+=4) {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, 
                          (USB_START_ADDR + i),
                          *(uint32_t*)(&FAT[i]));
  }
      
 
  printf("inited\n");
  HAL_FLASH_Lock();
  return (USBD_OK);
}  
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
