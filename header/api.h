#ifndef _api_H_
#define _api_H_
////UPDATE14;55
#include  "../header/halGPIO.h"     // private library - HAL layer


//       SMCLK/(2*freq)
#define     note0   501
#define     note1   473
#define     note2   447
#define     note3   421
#define     note4   398
#define     note5   375
#define     note6   354
#define     note7   334
#define     note8   316
#define     note9   298
#define     note10  281
#define     note11  265
#define     note12  250


extern void lcd_reset();
extern void LED_Blink(int delay);
extern void LCD_count(int delay);
extern void Buzz_pwm(int freq);
extern void sing_buzz(int delay);
void LDR_measurement(int delay);
void print_mat();
#endif







