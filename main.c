/* add user code begin Header */
/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "at32f421_wk_config.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */
#define PIN_V2 						GPIOA,GPIO_PINS_0
#define PIN_IN2 					GPIOA,GPIO_PINS_1
#define PIN_DIR 					GPIOA,GPIO_PINS_2
#define PIN_STEP 					GPIOA,GPIO_PINS_3
#define PIN_SLEEP 				GPIOA,GPIO_PINS_4
#define PIN_OUT 					GPIOB,GPIO_PINS_1
#define PIN_V1 						GPIOA,GPIO_PINS_6
#define PIN_IN1 					GPIOA,GPIO_PINS_5
/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */
static int out_pin_high = 0;

static int32_t counter = 0;


char calibration_on = 1;

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */
void count()
{
	if (out_pin_high)
	{		
		--counter;
	}
	
	else
	{
		++counter;
	//if (counter & (1<<1) == 0 ){allow_stop=1}
	}
}

	void ms_20_tick(void)
	{	
		
	
	//	tmr_interrupt_enable(TMR6,TMR_OVF_INT,FALSE);
		count();
		
		gpio_bits_set(PIN_STEP);
		tmr_flag_clear(TMR6,TMR_OVF_FLAG);

	}
/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

void get_out()
{
	static char buf;
	buf = buf << 1;
	if (gpio_input_data_bit_read(PIN_OUT)==1)
	{
	buf |= (1<<0);
	}
	else 
	{
	buf &= ~(1<<0);
	}
	if (buf==0)
	out_pin_high = 0;
	if (buf ==  255)
	out_pin_high =1;
}
	
	
int main(void)
{
  /* add user code begin 1 */

  /* add user code end 1 */

  /* system clock config. */
  wk_system_clock_config();

  /* config periph clock. */
  wk_periph_clock_config();

  /* nvic config. */
  wk_nvic_config();

  /* init wdt function. */
  wk_wdt_init();

  /* init gpio function. */
  wk_gpio_config();

  /* init tmr6 function. */
  wk_tmr6_init();


  /* add user code begin 2 */

  /* add user code end 2 */

	gpio_bits_reset(PIN_DIR);
	gpio_bits_set(PIN_SLEEP);
	
	gpio_bits_set(PIN_V2);
	gpio_bits_set(PIN_V1);
	
	
	static int v1_pin_high = 0;
	static int v2_pin_high = 0;
	
	static int in1_pin_high = 0;
	static int in2_pin_high = 0;
	
	static int motor_divider = 0;
	
	motor_divider=4096;
	tmr_interrupt_enable(TMR6,TMR_OVF_INT,TRUE);
	
	
  while(1)
  {
    /* add user code begin 3 */
	
	  gpio_bits_reset(PIN_STEP);
		
		tmr_period_value_set(TMR6,motor_divider);
		
		//tmr_counter_enable(TMR6,TRUE);
		
		
		
		
		
		get_out();
		v1_pin_high=gpio_input_data_bit_read(PIN_V1);
		v2_pin_high=gpio_input_data_bit_read(PIN_V2);
		
		//if (gpio_input_data_bit_read(PIN_OUT) )
	//	{
			//tmr_counter_enable(TMR6,FALSE);
		
		
		
			if (v1_pin_high   )
		{
			in1_pin_high=gpio_input_data_bit_read(PIN_IN1);
	
		}

		
		
		if (v2_pin_high)
		{
			in2_pin_high=gpio_input_data_bit_read(PIN_IN2);
		
		}
		
		
		
			if (out_pin_high == 0)
			{
			//	current_target=opened;
				
				if (in1_pin_high==0) 
				{
						gpio_bits_set(PIN_SLEEP);
				tmr_counter_enable(TMR6,TRUE);
				}
				else
				{	
					tmr_counter_enable(TMR6,FALSE);
					gpio_bits_reset(PIN_SLEEP);
				}
				
			
				gpio_bits_set(PIN_DIR);
			}
		else
			{
				//current_target=closed;
			
				if(in2_pin_high==0)
				{
						gpio_bits_set(PIN_SLEEP);
				tmr_counter_enable(TMR6,TRUE);
				}
				else
				{
					tmr_counter_enable(TMR6,FALSE);
						gpio_bits_reset(PIN_SLEEP);
				}
				gpio_bits_reset(PIN_DIR);
			}
		
		
		
		
	
		
		
		
    /* add user code end 3 */
  }
}
