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

const unsigned long led_mask[] = {1UL << 8, 1UL << 9};

/*-----------------------------------------------------------------------------
 *      LED_Init:  Initialize LED Pins
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_Init (void) {

  RCC->AHBENR |=  (1UL <<  2);                  /* Enable GPIOC clock         */

  /* Configure LED (PC.8..9) pins as push-pull outputs, No pull-up, pull-down */
  GPIOC->MODER   &= ~((3UL << 2*8) | (3UL << 2*9));
  GPIOC->MODER   |=  ((1UL << 2*8) | (1UL << 2*9));
  GPIOC->OTYPER  &= ~((1UL <<   8) | (1UL <<   9));
  GPIOC->OSPEEDR &= ~((3UL << 2*8) | (3UL << 2*9));
  GPIOC->OSPEEDR |=  ((1UL << 2*8) | (1UL << 2*9));
  GPIOC->PUPDR   &= ~((3UL << 2*8) | (3UL << 2*9));
}


/*-----------------------------------------------------------------------------
 *      LED_On: Turns on requested LED
 *
 * Parameters:  num - LED number
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_On (uint32_t num) {

  if (num < LED_NUM) {
    GPIOC->BSRRL = led_mask[num];
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
    GPIOC->BSRRH = led_mask[num];
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
