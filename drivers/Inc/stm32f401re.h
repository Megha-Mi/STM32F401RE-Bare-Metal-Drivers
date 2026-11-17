/*
 * stm32f401re.h
 *
 *  Created on: 16 Nov 2026
 *      Author: Megha Mittal
 */

#ifndef INC_STM32F401RE_H_
#define INC_STM32F401RE_H_

#include <stdint.h>

#define __vo   volatile


/*
 * Base addresses of FLASH and SRAM memories
 * (Source: RM0368, Flash module organization, page 45)
 */
#define FLASH_BASEADDR      0x08000000U     /* Main memory, 512 KB  */
#define SRAM1_BASEADDR      0x20000000U     /* Main SRAM, 96 KB     */
#define ROM_BASEADDR        0x1FFF0000U     /* System memory, 30 KB */
#define SRAM                SRAM1_BASEADDR


/*
 * AHBx and APBx bus peripheral base addresses
 * (Source: RM0368, Table 1, memory map)
 */
#define PERIPH_BASE         0x40000000U
#define APB1PERIPH_BASE     PERIPH_BASE
#define APB2PERIPH_BASE     0x40010000U
#define AHB1PERIPH_BASE     0x40020000U
#define AHB2PERIPH_BASE     0x50000000U


/*
 * Base addresses of peripherals on AHB1 bus
 * (Source: RM0368, Table 1, memory map)
 */
#define GPIOA_BASEADDR      (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR      (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR      (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR      (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR      (AHB1PERIPH_BASE + 0x1000)
#define GPIOH_BASEADDR      (AHB1PERIPH_BASE + 0x1C00)
#define RCC_BASEADDR        (AHB1PERIPH_BASE + 0x3800)


/*
 * Base addresses of peripherals on APB1 bus
 */
#define I2C1_BASEADDR       (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR       (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR       (APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR       (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR       (APB1PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR     (APB1PERIPH_BASE + 0x4400)


/*
 * Base addresses of peripherals on APB2 bus
 */
#define EXTI_BASEADDR       (APB2PERIPH_BASE + 0x3C00)
#define SYSCFG_BASEADDR     (APB2PERIPH_BASE + 0x3800)

#define SPI1_BASEADDR       (APB2PERIPH_BASE + 0x3000)
#define SPI4_BASEADDR       (APB2PERIPH_BASE + 0x3400)

#define USART1_BASEADDR     (APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR     (APB2PERIPH_BASE + 0x1400)


/*
 * Peripheral register definition structure for GPIO
 * (Source: RM0368, GPIO register map, page 164)
 */
typedef struct
{
    __vo uint32_t MODER;      /* 0x00 GPIO port mode register               */
    __vo uint32_t OTYPER;     /* 0x04 GPIO port output type register        */
    __vo uint32_t OSPEEDR;    /* 0x08 GPIO port output speed register       */
    __vo uint32_t PUPDR;      /* 0x0C GPIO port pull-up/pull-down register  */
    __vo uint32_t IDR;        /* 0x10 GPIO port input data register         */
    __vo uint32_t ODR;        /* 0x14 GPIO port output data register        */
    __vo uint32_t BSRR;       /* 0x18 GPIO port bit set/reset register      */
    __vo uint32_t LCKR;       /* 0x1C GPIO port configuration lock register */
    __vo uint32_t AFR[2];     /* 0x20 AFR[0] = AFRL, 0x24 AFR[1] = AFRH     */
} GPIO_RegDef_t;


/*
 * Peripheral register definition structure for RCC
 * (Source: RM0368, RCC register map, page 137)
 * Reserved offsets keep a placeholder so the next registers stay at the right offset.
 */
typedef struct
{
    __vo uint32_t CR;            /* 0x00 */
    __vo uint32_t PLLCFGR;       /* 0x04 */
    __vo uint32_t CFGR;          /* 0x08 */
    __vo uint32_t CIR;           /* 0x0C */
    __vo uint32_t AHB1RSTR;      /* 0x10 */
    __vo uint32_t AHB2RSTR;      /* 0x14 */
    uint32_t      RESERVED0[2];  /* 0x18, 0x1C */
    __vo uint32_t APB1RSTR;      /* 0x20 */
    __vo uint32_t APB2RSTR;      /* 0x24 */
    uint32_t      RESERVED1[2];  /* 0x28, 0x2C */
    __vo uint32_t AHB1ENR;       /* 0x30 */
    __vo uint32_t AHB2ENR;       /* 0x34 */
    uint32_t      RESERVED2[2];  /* 0x38, 0x3C */
    __vo uint32_t APB1ENR;       /* 0x40 */
    __vo uint32_t APB2ENR;       /* 0x44 */
    uint32_t      RESERVED3[2];  /* 0x48, 0x4C */
    __vo uint32_t AHB1LPENR;     /* 0x50 */
    __vo uint32_t AHB2LPENR;     /* 0x54 */
    uint32_t      RESERVED4[2];  /* 0x58, 0x5C */
    __vo uint32_t APB1LPENR;     /* 0x60 */
    __vo uint32_t APB2LPENR;     /* 0x64 */
    uint32_t      RESERVED5[2];  /* 0x68, 0x6C */
    __vo uint32_t BDCR;          /* 0x70 */
    __vo uint32_t CSR;           /* 0x74 */
    uint32_t      RESERVED6[2];  /* 0x78, 0x7C */
    __vo uint32_t SSCGR;         /* 0x80 */
    __vo uint32_t PLLI2SCFGR;    /* 0x84 */
    uint32_t      RESERVED7;     /* 0x88 */
    __vo uint32_t DCKCFGR;       /* 0x8C */
} RCC_RegDef_t;


/*
 * Peripheral definitions (base addresses typecasted to xxx_RegDef_t)
 */
#define GPIOA   ((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOH   ((GPIO_RegDef_t*) GPIOH_BASEADDR)

#define RCC     ((RCC_RegDef_t*) RCC_BASEADDR)


/*
 * Clock enable macros for GPIOx peripherals (RM0368 p118, RCC_AHB1ENR)
 */
#define GPIOA_PCLK_EN()    (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()    (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()    (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()    (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()    (RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()    (RCC->AHB1ENR |= (1 << 7))

/*
 * Clock enable macros for I2Cx peripherals (RCC_APB1ENR)
 */
#define I2C1_PCLK_EN()     (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()     (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()     (RCC->APB1ENR |= (1 << 23))

/*
 * Clock enable macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()     (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()     (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()     (RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()     (RCC->APB2ENR |= (1 << 13))

/*
 * Clock enable macros for USARTx peripherals
 */
#define USART1_PCLK_EN()   (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()   (RCC->APB1ENR |= (1 << 17))
#define USART6_PCLK_EN()   (RCC->APB2ENR |= (1 << 5))

/*
 * Clock enable macro for SYSCFG peripheral (RM0368 p122, RCC_APB2ENR)
 */
#define SYSCFG_PCLK_EN()   (RCC->APB2ENR |= (1 << 14))


/*
 * Clock disable macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 7))

/*
 * Clock disable macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 23))

/*
 * Clock disable macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 13))

/*
 * Clock disable macros for USARTx peripherals
 */
#define USART1_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()   (RCC->APB1ENR &= ~(1 << 17))
#define USART6_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock disable macro for SYSCFG peripheral
 */
#define SYSCFG_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 14))

/*
 * Some generic macros
 */
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET

/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOH_REG_RESET()   do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)

#include "stm32f401re_gpio_driver.h"

#endif /* INC_STM32F401RE_H_ */
