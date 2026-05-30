# stm32-spi-w25q64

STM32F103C8T6 软件模拟SPI读取W25Q64 Flash + SSD1306 OLED显示

## 硬件连接

| STM32F103C8 | W25Q64 | OLED |
|-------------|--------|------|
| PB13 (SCK)  | CLK    | —    |
| PB14 (MISO) | DO     | —    |
| PB15 (MOSI) | DI     | —    |
| PA4  (CS)   | CS     | —    |
| PB5  (SCL)  | —      | SCL  |
| PB6  (SDA)  | —      | SDA  |
| 3.3V / GND  | VCC/GND | VCC/GND |

## 目录结构

```
├── Start/          CMSIS启动文件 + system_stm32f10x
├── Library/        ST标准外设库 v3.5.0
├── Hardwera/       自定义驱动（MySPI, W25Q64, OLED）
├── System/         系统工具（Delay）
├── User/           应用层（main.c, conf.h, it.c）
├── build/          EIDE构建输出
├── Objects/        Keil MDK编译产物
└── Listings/       编译器清单
```

## 开发环境

- **Keil MDK v5** — 打开 `Project.uvprojx`
- **VSCode + EIDE** — 安装 `cl.eide` 插件后打开项目目录
- **调试器** — ST-Link (SWD)
- **工具链** — ARMCC v5 (AC5)

## 构建与烧录

```bash
# 清理构建产物
keilkill.bat

# Keil: F7 编译 → F8 烧录
# EIDE: Ctrl+Shift+P → "EIDE: Build"
```

## 继续 Claude Code 会话

在 PowerShell 中进入此目录后：

```bash
claude --resume
```

这将恢复你上次在此项目中的 Claude Code 会话。

## 参考

- [开发流程.md](./开发流程.md)
- [W25Q64 数据手册](https://www.winbond.com/hq/product/code-storage-flash-memory/serial-nor-flash/?partNo=W25Q64JV)
- [STM32F103C8 参考手册](https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html)
