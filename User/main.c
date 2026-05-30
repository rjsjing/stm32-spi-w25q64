#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MySPI.h"
#include "W25Q64.h"

int main(void)
{
    uint8_t jedecID[3];
    uint8_t mid, did;
    uint8_t testData[4] = {0x12, 0x34, 0x56, 0x78};
    uint8_t readBuf[4] = {0};

    OLED_Init();
    OLED_ShowString(1, 1, "W25Q64 Init...");

    W25Q64_Init();
    Delay_ms(10);

    /* 读 JEDEC ID */
    W25Q64_ReadJEDECID(jedecID);
    OLED_Clear();
    OLED_ShowString(1, 1, "JEDEC ID:");
    OLED_ShowHexNum(2, 1, jedecID[0], 2);
    OLED_ShowHexNum(2, 4, jedecID[1], 2);
    OLED_ShowHexNum(2, 7, jedecID[2], 2);

    /* 读 Manufacturer/Device ID */
    W25Q64_ReadManufacturerID(&mid, &did);
    OLED_ShowString(3, 1, "Mf/Dev:");
    OLED_ShowHexNum(3, 9, mid, 2);
    OLED_ShowHexNum(3, 12, did, 2);

    /* 擦除首扇区, 写入测试数据, 读回验证 */
    W25Q64_SectorErase(0x000000);
    W25Q64_PageProgram(0x000000, testData, 4);
    W25Q64_ReadData(0x000000, readBuf, 4);

    OLED_ShowString(4, 1, "RD:");
    OLED_ShowHexNum(4, 4, readBuf[0], 2);
    OLED_ShowHexNum(4, 7, readBuf[1], 2);
    OLED_ShowHexNum(4, 10, readBuf[2], 2);
    OLED_ShowHexNum(4, 13, readBuf[3], 2);

    while (1)
    {

    }
}
