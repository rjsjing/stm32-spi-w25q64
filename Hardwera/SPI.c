#include "MySPI.h"

/**
 * 初始化软件SPI GPIO
 * SCK/MOSI/CS → 推挽输出, MISO → 上拉输入
 * 模式0: SCK空闲低电平, CS初始高电平(未选中)
 */
void MySPI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(MYSPI_RCC, ENABLE);  //MYSPI_RCC = RCC_APB2Periph_GPIOA

    /* SCK, MOSI, CS — 推挽输出 */
    /*MYSPI_SCK_PIN=GPIO_Pin_5*/
    /*MYSPI_MOSI_PIN=GPIO_Pin_7*/
    /*MYSPI_CS_PIN=GPIO_Pin_4*/
    GPIO_InitStructure.GPIO_Pin   = MYSPI_SCK_PIN | MYSPI_MOSI_PIN | MYSPI_CS_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MYSPI_PORT, &GPIO_InitStructure);

    /* MISO — 上拉输入 */
    GPIO_InitStructure.GPIO_Pin  = MYSPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(MYSPI_PORT, &GPIO_InitStructure);

    /* 初始电平: SCK=0, MOSI=0, CS=1 (不选中) */
    GPIO_ResetBits(MYSPI_PORT, MYSPI_SCK_PIN | MYSPI_MOSI_PIN);
    GPIO_SetBits(MYSPI_PORT, MYSPI_CS_PIN);  //pin4=CS, 初始高电平(未选中)
}

/**
 * 发送一字节, 同时接收一字节 (MSB first)
 * SPI 模式0: CPOL=0, CPHA=0
 *   上升沿采样 → SCK拉高后读MISO
 *   下降沿切换数据 → SCK拉低前写MOSI
 */
uint8_t MySPI_ReadWriteByte(uint8_t txData)
{
    uint8_t rxData = 0;
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        /* 写 MOSI (MSB first) */
        if (txData & 0x80)   //txData最高位为1
            GPIO_SetBits(MYSPI_PORT, MYSPI_MOSI_PIN);
        else
            GPIO_ResetBits(MYSPI_PORT, MYSPI_MOSI_PIN);
        txData <<= 1;  //txData左移1位, 下一bit移到最高位

        /* 上升沿: 从机锁存MOSI, 主机采样MISO */
        GPIO_SetBits(MYSPI_PORT, MYSPI_SCK_PIN);

        /* 读 MISO */
        rxData <<= 1;
        if (GPIO_ReadInputDataBit(MYSPI_PORT, MYSPI_MISO_PIN))
            rxData |= 0x01;

        /* 下降沿: 数据切换准备下一bit */
        GPIO_ResetBits(MYSPI_PORT, MYSPI_SCK_PIN);
    }

    return rxData;
}
