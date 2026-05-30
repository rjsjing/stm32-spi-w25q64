#ifndef __W25Q64_H
#define __W25Q64_H

#include "stm32f10x.h"

/* W25Q64 命令码 */
#define W25Q64_CMD_WRITE_ENABLE       0x06
#define W25Q64_CMD_WRITE_DISABLE      0x04
#define W25Q64_CMD_READ_STATUS1       0x05
#define W25Q64_CMD_READ_STATUS2       0x35
#define W25Q64_CMD_READ_DATA          0x03
#define W25Q64_CMD_FAST_READ          0x0B
#define W25Q64_CMD_PAGE_PROGRAM       0x02
#define W25Q64_CMD_SECTOR_ERASE       0x20
#define W25Q64_CMD_BLOCK_ERASE_64K    0xD8
#define W25Q64_CMD_CHIP_ERASE         0xC7
#define W25Q64_CMD_POWER_DOWN         0xB9
#define W25Q64_CMD_RELEASE_POWER_DOWN 0xAB
#define W25Q64_CMD_JEDEC_ID           0x9F
#define W25Q64_CMD_MANUFACTURER_ID    0x90

/* 芯片参数 */
#define W25Q64_PAGE_SIZE      256
#define W25Q64_SECTOR_SIZE    4096
#define W25Q64_BLOCK_SIZE     65536
#define W25Q64_TOTAL_SIZE     8388608

/* 状态寄存器位 */
#define W25Q64_SR1_BUSY       0x01
#define W25Q64_SR1_WEL        0x02

void W25Q64_Init(void);
void W25Q64_ReadJEDECID(uint8_t *id);
void W25Q64_ReadManufacturerID(uint8_t *mid, uint8_t *did);
uint8_t W25Q64_ReadStatus1(void);
void W25Q64_WriteEnable(void);
void W25Q64_WaitBusy(void);
void W25Q64_SectorErase(uint32_t addr);
void W25Q64_BlockErase64K(uint32_t addr);
void W25Q64_ChipErase(void);
void W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint16_t len);
void W25Q64_ReadData(uint32_t addr, uint8_t *buf, uint32_t len);

#endif
