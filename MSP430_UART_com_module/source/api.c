#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include "msp430xG46x.h"
////UPDATE14;55
#include "stdio.h"

int count = 0;
/*______________________________________
 *                                      *
 *          LCD API                     *
 *______________________________________*/


void lcd_reset(){
    lcd_clear();
    lcd_home();
}

/*__________________________________________________________
 *                                                          *
 *          STATE 1 : LED blink                             *
 *__________________________________________________________*/
void LED_Blink(int delay){
    while (state = state1){
        enable_interrupts();
        LED_RGB_Port ^= LED_R;
        startTimerA0(delay);
    }
    //stopTimerA0();
}

/*__________________________________________________________
 *                                                          *
 *          STATE 2 : DMA Row Swap                          *
 *__________________________________________________________*/
void LCD_count(int delay){
    while (state = state2){
        lcd_reset();
        lcd_print_num(count);
        count++;
        if (count == 100){
            count = 0;
        }
        startTimerA0(delay);
    }
    //stopTimerA0();
}


/*__________________________________________________________
 *                                                          *
 *          STATE 3 : DMA Led Shift                          *
 *__________________________________________________________*/

void Buzz_pwm(int freq){
    while (state = state3){

        BuzzPortOut ^= BuzzPin;
        enable_interrupts();
        startTimerA1(freq);
    }
    //stopTimerA0();
}


/*__________________________________________________________
 *                                                          *
 *          STATE 3 : str Swap                              *
 *__________________________________________________________*/





