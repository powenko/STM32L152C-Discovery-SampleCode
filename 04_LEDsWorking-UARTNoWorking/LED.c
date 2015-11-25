/*----------------------------------------------------------------------------
 * Name:    LED.c
 * Purpose: low level LED functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2013 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stm32l1xx.h>
#include "LED.h"

const unsigned long led1=6UL;
const unsigned long led2=7UL;

const unsigned long led_mask[] = {1UL << led1, 1UL << led2};

/*-----------------------------------------------------------------------------
 *      LED_Init:  Initialize LED Pins
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_Init (void) {

  RCC->AHBENR |=  (1UL <<  2);                  /* Enable GPIOC clock         */
  
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN; //enable clock for LEDs        /* Enable GPIOC clock         */

  /* Configure LED (PC.8..9) pins as push-pull outputs, No pull-up, pull-down */
  GPIOB->MODER   &= ~((3UL << 2*led1) | (3UL << 2*led2));
  GPIOB->MODER   |=  ((1UL << 2*led1) | (1UL << 2*led2));
  GPIOB->OTYPER  &= ~((1UL <<   led1) | (1UL <<   led2));
  GPIOB->OSPEEDR &= ~((3UL << 2*led1) | (3UL << 2*led2));
  GPIOB->OSPEEDR |=  ((1UL << 2*led1) | (1UL << 2*led2));
  GPIOB->PUPDR   &= ~((3UL << 2*led1) | (3UL << 2*led2));
}


/*-----------------------------------------------------------------------------
 *      LED_On: Turns on requested LED
 *
 * Parameters:  num - LED number
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_On (uint32_t num) {

  if (num < LED_NUM) {
    GPIOB->BSRRL = led_mask[num];
  }
}

/*-----------------------------------------------------------------------------
 *       LED_Off: Turns off requested LED
 *
 * Parameters:  num - LED number
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_Off (uint32_t num) {

  if (num < LED_NUM) {
    GPIOB->BSRRH = led_mask[num];
  }
}

/*-----------------------------------------------------------------------------
 *       LED_Val: Write value to LEDs
 *
 * Parameters:  val - value to be displayed on LEDs
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_Out (uint32_t value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}
