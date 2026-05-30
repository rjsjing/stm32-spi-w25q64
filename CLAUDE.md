# CLAUDE.md — STM32F103C8T6 硬件SPI读写W25Q64

## 技术栈

- **MCU**: STM32F103C8T6（Cortex-M3, 64KB Flash, 20KB SRAM, 72MHz）
- **库**: ST 标准外设库 v3.5.0（非 HAL/CubeMX）
- **构建工具**: Keil MDK uVision5（ARMCC v5 / AC5）+ EIDE (VSCode 插件 `cl.eide`)
- **调试器**: ST-Link (SWD)
- **SPI 通信**: 使用 STM32 硬件 SPI1 外设（替代软件模拟 GPIO 位翻转），全双工主机模式，模式0（CPOL=0, CPHA=0）
- **没有 .ioc 文件**，不使用 CubeMX 代码生成

## 目录结构

```
├── Start/           CMSIS 启动 + system_stm32f10x（core_cm3, startup_xxx.s）
├── Library/         ST 标准外设库 v3.5.0 (misc, gpio, rcc, tim, usart...)
├── Hardwera/        自定义硬件驱动
│   ├── SPI.c/h      ← 硬件SPI1（模式0, PA5/PA6/PA7, PA4软件片选, 含读写分离+多字节）
│   ├── W25Q64.c/h   ← W25Q64 Flash命令集（擦除/编程/读取/JEDEC ID）
│   ├── OLED.c/h     ← SSD1306 I2C OLED驱动（已实现）
│   └── OLED_Font.h  ← 8×16 ASCII字库
├── System/          Delay.c/h — SysTick微秒/毫秒/秒延时
├── User/            main.c, stm32f10x_conf.h, stm32f10x_it.c/h
├── build/           EIDE构建输出
├── Objects/         Keil编译产物
└── Listings/        编译清单(.map)
```

## Git 规范

### 分支命名
```
main              ← 稳定分支
feature/<name>    ← 新功能（如 feature/myspi-driver）
fix/<name>        ← 修复
```

### 提交信息格式
```
<type>: <简短描述>

feat: 实现MySPI字节读写
fix: 修正W25Q64扇区擦除地址
docs: 更新CLAUD.md
```

### 不提交的文件（已在 .gitignore）
```
build/  .eide/cache/  *.o  *.d  *.elf  *.bin  *.hex  .vscode/
Objects/  Listings/   ← 应加入 .gitignore
```

## 编码规范

- **函数命名**: `模块名_操作()`，如 `MySPI_Init()`, `W25Q64_ReadID()`
- **禁止魔法数字**: GPIO引脚、外设地址、命令码 必须用 `#define` 宏
- **分组**: 所有 `#define` 放在对应 `.h` 文件中
- **SPI引脚（STM32 硬件 SPI1）**:
  ```
  PA5 = SPI1_SCK  （硬件SPI时钟）
  PA6 = SPI1_MISO （硬件SPI主机输入）
  PA7 = SPI1_MOSI （硬件SPI主机输出）
  PA4 = CS        （软件GPIO片选，推挽输出）
  PB5 = I2C SCL, PB6 = I2C SDA
  ```
- **头文件包含**: 只包含实际使用的标准外设头文件（`stm32f10x_conf.h` 中控制）
- **编码**: UTF-8，注释用中文

## 构建命令

```
Keil:  打开 Project.uvprojx → F7 编译 → F8 烧录
EIDE:  Ctrl+Shift+P → "EIDE: Build"
清理:  keilkill.bat
```

## 注意事项

- `stm32f10x_conf.h` 中需要启用 GPIO、RCC、SPI、TIM 外设
- `USE_STDPERIPH_DRIVER` 和 `STM32F10X_MD` 宏必须在编译选项中定义
- 启动文件用 `startup_stm32f10x_md.s`（中密度，对应 C8 型号）
- `W25Q64.c/h` 已实现完整Flash命令集，`main.c` 演示读取ID+擦写读验证
