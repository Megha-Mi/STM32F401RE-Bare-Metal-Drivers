# STM32F401RE Bare-Metal Drivers

Bare-metal peripheral drivers for the **STM32F401RE** (ARM Cortex-M4) written from scratch in Embedded C. No HAL, no LL, no CMSIS device headers: everything is built directly from the reference manual (RM0368).

Tested on the **NUCLEO-F401RE** board.

---

## What's inside

```
drivers/
├── Inc/
│   ├── stm32f401re.h              # MCU-specific header
│   └── stm32f401re_gpio_driver.h  # GPIO driver API + config macros
└── Src/
    └── stm32f401re_gpio_driver.c  # GPIO driver implementation
Src/
└── 001led_toggle.c                # Application: toggle on-board LED (PA5)
```

### 1. MCU-specific header (`stm32f401re.h`)
- Base addresses of Flash, SRAM, ROM and the AHB1/AHB2/APB1/APB2 buses
- Base addresses of GPIOA–E/H, I2C1–3, SPI1–4, USART1/2/6, EXTI, SYSCFG, RCC
- Register definition structures: `GPIO_RegDef_t`, `RCC_RegDef_t` (with reserved placeholders so every register lands at the correct offset)
- Peripheral definition macros (`GPIOA`, `RCC`, ...) typecast to their register structures
- Peripheral clock enable/disable macros (`GPIOx_PCLK_EN/DI`, `I2Cx`, `SPIx`, `USARTx`, `SYSCFG`)
- Peripheral reset macros using `RCC_AHB1RSTR` (`do { ... } while(0)` multi-statement macros)

### 2. GPIO driver (`stm32f401re_gpio_driver.h/.c`)
Handle and configuration structures (`GPIO_Handle_t`, `GPIO_PinConfig_t`) plus these APIs:

| API | Description |
|---|---|
| `GPIO_PeriClockControl()` | Enable/disable the peripheral clock for a GPIO port |
| `GPIO_Init()` | Configure mode, speed, pull-up/pull-down, output type and alternate function |
| `GPIO_DeInit()` | Reset all registers of a GPIO port via RCC |
| `GPIO_ReadFromInputPin()` | Read a single pin |
| `GPIO_ReadFromInputPort()` | Read the full 16-bit port |
| `GPIO_WriteToOutputPin()` | Write a single pin |
| `GPIO_WriteToOutputPort()` | Write the full 16-bit port |
| `GPIO_ToggleOutputPin()` | Toggle a pin |
| `GPIO_IRQConfig()` / `GPIO_IRQHandling()` | *Work in progress* |

### 3. Application (`001led_toggle.c`)
Toggles the on-board user LED **LD2 (PA5)** using only the driver APIs above.

```c
GPIO_Handle_t GpioLed;
GpioLed.pGPIOx = GPIOA;
GpioLed.GPIO_PinConfig.GPIO_PinNumber      = GPIO_PIN_NO_5;
GpioLed.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
GpioLed.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_SPEED_FAST;
GpioLed.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OP_TYPE_PP;
GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

GPIO_PeriClockControl(GPIOA, ENABLE);
GPIO_Init(&GpioLed);

while (1) {
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
    delay();
}
```

---

## Key lessons learned
- **Read-modify-write:** writing a register with `=` overwrites every other pin's configuration. On `GPIOA->MODER` this wipes PA13/PA14 (SWD) and disconnects the debugger. Use `&= ~mask` to clear, then `|=` to set.
- **Clear before set:** `|=` alone cannot change `1 -> 0`, so bit fields must be cleared first.
- **Clock first:** a peripheral's registers cannot be written until its clock is enabled in RCC.
- **Reserved registers matter:** missing placeholders in a register struct shift every following register to the wrong address.
- **Alternate function mapping:** register = `pin / 8` (AFRL/AFRH), bit position = `4 * (pin % 8)`.

---

## Build and run
1. Create an **STM32CubeIDE Empty Project** for STM32F401RETx.
2. Copy the `drivers/` folder and `Src/001led_toggle.c` into the project (remove the default `main.c`).
3. Add `drivers/Inc` to *Project → Properties → C/C++ Build → Settings → MCU GCC Compiler → Include paths*.
4. Build and run on a NUCLEO-F401RE. LD2 (green) blinks.

## Roadmap
- [x] GPIO driver (polling)
- [ ] GPIO interrupts (EXTI + NVIC)
- [ ] SPI driver
- [ ] I2C driver
- [ ] USART driver

## Tools and references
- STM32CubeIDE 2.2, arm-none-eabi-gcc
- RM0368 Reference Manual, STM32F401xD/E Datasheet, UM1724 (Nucleo-64 user manual)

---

**Author:** Megha Mittal
