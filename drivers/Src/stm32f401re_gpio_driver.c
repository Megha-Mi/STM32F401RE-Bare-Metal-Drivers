/*
 * stm32f401re_gpio_driver.c
 *
 *  Created on: 17 Nov 2026
 *      Author: Megha Mittal
 */

#include "stm32f401re_gpio_driver.h"
/*********************************************************************
 * @fn          - GPIO_PeriClockControl
 *
 * @brief       - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]   - base address of the GPIO peripheral
 * @param[in]   - ENABLE or DISABLE macros
 *
 * @return      - none
 *
 * @Note        - none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{

	    if(EnorDi == ENABLE)
	    {
	        if(pGPIOx == GPIOA)
	        {
	            GPIOA_PCLK_EN();
	        }else if(pGPIOx == GPIOB)
	        {
	            GPIOB_PCLK_EN();
	        }else if(pGPIOx == GPIOC)
	        {
	            GPIOC_PCLK_EN();
	        }else if(pGPIOx == GPIOD)
	        {
	            GPIOD_PCLK_EN();
	        }else if(pGPIOx == GPIOE)
	        {
	            GPIOE_PCLK_EN();
	        }else if(pGPIOx == GPIOH)
	        {
	            GPIOH_PCLK_EN();
	        }
	    }
	    else
	    {
	    	if(pGPIOx == GPIOA){
	    		GPIOA_PCLK_DI();
	    	}
	    	else if(pGPIOx == GPIOB){
	    		GPIOB_PCLK_DI();
	    	}
	    	else if(pGPIOx == GPIOC){
	    		GPIOC_PCLK_DI();
	    	}
	    	else if(pGPIOx == GPIOD){
	    		GPIOD_PCLK_DI();
	    	}
	    	else if(pGPIOx == GPIOE){
	    		GPIOE_PCLK_DI();
	    	}
	    	else if(pGPIOx == GPIOH){
	    		GPIOH_PCLK_DI();
	    	}
	    }

}


/*********************************************************************
 * @fn          - GPIO_Init
 *
 * @brief       - This function initializes the given GPIO pin (mode, speed, pupd, otype, altfn)
 *
 * @param[in]   - pointer to the GPIO handle structure
 *
 * @return      - none
 *
 * @Note        - none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;   /* temp. register */

    /* 1. configure the mode of gpio pin */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        /* the non interrupt mode */
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));   /* clearing */
        pGPIOHandle->pGPIOx->MODER |= temp;                                                         /* setting */
    }
    else
    {
        /* interrupt mode: will code later */
    }

    temp = 0;

    /* 2. configure the speed */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));   /* clearing */
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp = 0;

    /* 3. configure the pupd settings */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));     /* clearing */
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp = 0;

    /* 4. configure the optype (1 bit per pin) */
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);          /* clearing */
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp = 0;

    /* 5. configure the alt functionality (4 bits per pin) */
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1, temp2;

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;   /* which register: AFR[0] or AFR[1] */
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;   /* position inside that register */
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));                                    /* clearing */
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
    }
}
/*********************************************************************
 * @fn          - GPIO_DeInit
 *
 * @brief       - This function resets all the registers of the given GPIO port
 *
 * @param[in]   - base address of the GPIO peripheral
 *
 * @return      - none
 *
 * @Note        - uses RCC AHB1 peripheral reset register
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	 if(pGPIOx == GPIOA)
		        {
		            GPIOA_REG_RESET();
		        }else if(pGPIOx == GPIOB)
		        {
		            GPIOB_REG_RESET();
		        }else if(pGPIOx == GPIOC)
		        {
		            GPIOC_REG_RESET();
		        }else if(pGPIOx == GPIOD)
		        {
		            GPIOD_REG_RESET();
		        }else if(pGPIOx == GPIOE)
		        {
		            GPIOE_REG_RESET();
		        }else if(pGPIOx == GPIOH)
		        {
		            GPIOH_REG_RESET();
		        }

}


/*********************************************************************
 * @fn          - GPIO_ReadFromInputPin
 *
 * @brief       - This function reads the state of the given GPIO pin
 *
 * @param[in]   - base address of the GPIO peripheral
 * @param[in]   - pin number (0 to 15)
 *
 * @return      - 0 or 1
 *
 * @Note        - none
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	 uint8_t value;

	    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);

	    return value;
}


/*********************************************************************
 * @fn          - GPIO_ReadFromInputPort
 *
 * @brief       - This function reads all 16 pins of the given GPIO port
 *
 * @param[in]   - base address of the GPIO peripheral
 *
 * @return      - 16-bit value of the port
 *
 * @Note        - none
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;

	    value = (uint16_t)pGPIOx->IDR;

	    return value;
}


/*********************************************************************
 * @fn          - GPIO_WriteToOutputPin
 *
 * @brief       - This function writes a value to the given GPIO pin
 *
 * @param[in]   - base address of the GPIO peripheral
 * @param[in]   - pin number (0 to 15)
 * @param[in]   - GPIO_PIN_SET or GPIO_PIN_RESET
 *
 * @return      - none
 *
 * @Note        - none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	  if(Value == GPIO_PIN_SET)
	    {
	        pGPIOx->ODR |= (1 << PinNumber);      /* bit SET   -> pin HIGH */
	    }else
	    {
	        pGPIOx->ODR &=~(1 << PinNumber);    /* bit CLEAR -> pin LOW */
	    }
}


/*********************************************************************
 * @fn          - GPIO_WriteToOutputPort
 *
 * @brief       - This function writes a 16-bit value to the given GPIO port
 *
 * @param[in]   - base address of the GPIO peripheral
 * @param[in]   - 16-bit value
 *
 * @return      - none
 *
 * @Note        - none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;

}


/*********************************************************************
 * @fn          - GPIO_ToggleOutputPin
 *
 * @brief       - This function toggles the given GPIO pin
 *
 * @param[in]   - base address of the GPIO peripheral
 * @param[in]   - pin number (0 to 15)
 *
 * @return      - none
 *
 * @Note        - none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^=(1 << PinNumber);

}


/*********************************************************************
 * @fn          - GPIO_IRQConfig
 *
 * @brief       - This function configures the IRQ (enable/disable, priority) in NVIC
 *
 * @param[in]   - IRQ number
 * @param[in]   - IRQ priority
 * @param[in]   - ENABLE or DISABLE macros
 *
 * @return      - none
 *
 * @Note        - none
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

}


/*********************************************************************
 * @fn          - GPIO_IRQHandling
 *
 * @brief       - This function handles the interrupt of the given pin (clears EXTI PR bit)
 *
 * @param[in]   - pin number (0 to 15)
 *
 * @return      - none
 *
 * @Note        - none
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
