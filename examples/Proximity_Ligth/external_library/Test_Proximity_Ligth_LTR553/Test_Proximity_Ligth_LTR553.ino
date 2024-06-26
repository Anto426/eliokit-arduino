#include <Arduino.h>
#include <Wire.h>
#include "ltr_5xx.h"

#define I2C_SDA 4 // GPIO4
#define I2C_SCL 5 // GPIO5

/*you can only choose one device LTR553,LTR556,or LTR507*/
/*Change the macro definition in the ltr_5xx.h file.LTR55X or LTR507*/

// if use LTR553 or LTR556
LTR5XX ltr5xx_device(I2C_SDA, I2C_SCL, LTR55X_ADDR);

// if use LTR507
// LTR5XX ltr5xx_device(I2C_SDA, I2C_SCL, LTR507_SEL_FLOAT_ADDR); //LTR507_SEL_FLOAT_ADDR or LTR507_SEL_VDD_ADDR or LTR507_SEL_GND_ADDR

// Define initialization parameters
Ltr5xx_Init_Basic_Para device_init_base_para = LTR5XX_BASE_PARA_CONFIG_DEFAULT;

uint16_t read_ps_value;
uint16_t read_als_value;

/*Get values directly without interruption*/
void setup(void)
{
  Serial.begin(57600);
  Serial.println("=================\r\n");
  Serial.println("ltr5xx base one device test!");
  Serial.println("=================\r\n");
  // set some of your custom parameters.
  // Please select the correct parameter range based on the device of your choice
  device_init_base_para.ps_led_pulse_freq = LTR5XX_LED_PULSE_FREQ_40KHZ;
  device_init_base_para.ps_measurement_rate = LTR5XX_PS_MEASUREMENT_RATE_50MS;
  device_init_base_para.als_gain = LTR5XX_ALS_GAIN_48X;

  ltr5xx_device.ltr5xx_basic_init(&device_init_base_para);

  // active ps
  ltr5xx_device.ps_set_mode(LTR5XX_PS_ACTIVE_MODE);

  // active als
  ltr5xx_device.als_set_mode(LTR5XX_ALS_ACTIVE_MODE);
  // not active ps
  // ltr5xx_device.ps_set_mode(LTR5XX_PS_STAND_BY_MODE);

  // not active als
  // ltr5xx_device.als_set_mode(LTR5XX_ALS_STAND_BY_MODE);
}

void loop(void)
{
  read_ps_value = ltr5xx_device.ps_get_value();
  Serial.printf("ps value = %d\r\n", read_ps_value);
  read_als_value = ltr5xx_device.als_get_value();
  Serial.printf("als value = %d\r\n", read_als_value);

  delay(500);
}