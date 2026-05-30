#ifndef __MYSPI_H
#define __MYSPI_H

#include "stm32f10x.h"

/* SPI 引脚定义 — PA端口 */
#define MYSPI_SCK_PIN   GPIO_Pin_5
#define MYSPI_MISO_PIN  GPIO_Pin_6
#define MYSPI_MOSI_PIN  GPIO_Pin_7
#define MYSPI_CS_PIN    GPIO_Pin_4

#define MYSPI_PORT      GPIOA
#define MYSPI_RCC       RCC_APB2Periph_GPIOA

/* CS 片选宏 — 低电平有效 */
#define MYSPI_CS_LOW()  GPIO_ResetBits(MYSPI_PORT, MYSPI_CS_PIN)
#define MYSPI_CS_HIGH() GPIO_SetBits(MYSPI_PORT, MYSPI_CS_PIN)

void MySPI_Init(void);
uint8_t MySPI_ReadWriteByte(uint8_t txData);
void MySPI_WriteByte(uint8_t txData);
uint8_t MySPI_ReadByte(void);
void MySPI_WriteBytes(uint8_t *data, uint16_t len);
void MySPI_ReadBytes(uint8_t *buf, uint16_t len);

#endif
