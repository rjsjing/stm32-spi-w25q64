#include "W25Q64.h"
#include "MySPI.h"

void W25Q64_Init(void)
{
    MySPI_Init();
    MYSPI_CS_HIGH();
}

/** 读取JEDEC ID (厂商+类型+容量, 3字节) */
void W25Q64_ReadJEDECID(uint8_t *id)
{
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_JEDEC_ID);
    MySPI_ReadBytes(id, 3);
    MYSPI_CS_HIGH();
}

/** 读取厂商/设备ID (0x90命令) */
void W25Q64_ReadManufacturerID(uint8_t *mid, uint8_t *did)
{
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_MANUFACTURER_ID);
    MySPI_WriteByte(0x00);
    MySPI_WriteByte(0x00);
    MySPI_WriteByte(0x00);
    *mid = MySPI_ReadByte();
    *did = MySPI_ReadByte();
    MYSPI_CS_HIGH();
}

/** 读状态寄存器1 */
uint8_t W25Q64_ReadStatus1(void)
{
    uint8_t sr;
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_READ_STATUS1);
    sr = MySPI_ReadByte();
    MYSPI_CS_HIGH();
    return sr;
}

/** 写使能 */
void W25Q64_WriteEnable(void)
{
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_WRITE_ENABLE);
    MYSPI_CS_HIGH();
}

/** 等待BUSY位清除 */
void W25Q64_WaitBusy(void)
{
    while (W25Q64_ReadStatus1() & W25Q64_SR1_BUSY);
}

/** 扇区擦除 (4KB) */
void W25Q64_SectorErase(uint32_t addr)
{
    W25Q64_WriteEnable();
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_SECTOR_ERASE);
    MySPI_WriteByte((addr >> 16) & 0xFF);
    MySPI_WriteByte((addr >> 8)  & 0xFF);
    MySPI_WriteByte(addr         & 0xFF);
    MYSPI_CS_HIGH();
    W25Q64_WaitBusy();
}

/** 块擦除 (64KB) */
void W25Q64_BlockErase64K(uint32_t addr)
{
    W25Q64_WriteEnable();
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_BLOCK_ERASE_64K);
    MySPI_WriteByte((addr >> 16) & 0xFF);
    MySPI_WriteByte((addr >> 8)  & 0xFF);
    MySPI_WriteByte(addr         & 0xFF);
    MYSPI_CS_HIGH();
    W25Q64_WaitBusy();
}

/** 全片擦除 */
void W25Q64_ChipErase(void)
{
    W25Q64_WriteEnable();
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_CHIP_ERASE);
    MYSPI_CS_HIGH();
    W25Q64_WaitBusy();
}

/** 页编程 (最多256字节, 不可跨页) */
void W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint16_t len)
{
    uint16_t i;
    W25Q64_WriteEnable();
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_PAGE_PROGRAM);
    MySPI_WriteByte((addr >> 16) & 0xFF);
    MySPI_WriteByte((addr >> 8)  & 0xFF);
    MySPI_WriteByte(addr         & 0xFF);
    for (i = 0; i < len; i++)
    {
        MySPI_WriteByte(data[i]);
    }
    MYSPI_CS_HIGH();
    W25Q64_WaitBusy();
}

/** 读取数据 */
void W25Q64_ReadData(uint32_t addr, uint8_t *buf, uint32_t len)
{
    uint32_t i;
    MYSPI_CS_LOW();
    MySPI_WriteByte(W25Q64_CMD_READ_DATA);
    MySPI_WriteByte((addr >> 16) & 0xFF);
    MySPI_WriteByte((addr >> 8)  & 0xFF);
    MySPI_WriteByte(addr         & 0xFF);
    for (i = 0; i < len; i++)
    {
        buf[i] = MySPI_ReadByte();
    }
    MYSPI_CS_HIGH();
}
