#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include "msp430xG46x.h"
////UPDATE14;55
#include "stdio.h"

int tones[7] = {1000,1250,1500,17500,2000,2250,2500};
int count = 0;
int tone = 0;
int c;
/*______________________________________
 *                                      *
 *          LCD API                     *
 *______________________________________*/


void lcd_reset(){
    lcd_clear();
    lcd_home();
}

int colors[12] = {0,1,0,3,0,2,0,6,0,4,0,5};
/*__________________________________________________________
 *                                                          *
 *          STATE 1 : LED blink                             *
 *__________________________________________________________*/
void LED_Blink(int t){
    c = 0;
    while (state == state1){
        enable_interrupts();
        LED_RGB_Port = colors[c];
        c = (c+1)%9;

        delay(t);

    }
    //stopTimerA0();
}

/*__________________________________________________________
 *                                                          *
 *          STATE 2 : DMA Row Swap                          *
 *__________________________________________________________*/
void LCD_count(int t){
    while (state == state2){
        lcd_reset();
        lcd_print_num(count);
        count++;
        if (count == 100){
            count = 0;
        }
        delay(t);

    }
    //stopTimerA0();
}


/*__________________________________________________________
 *                                                          *
 *          STATE 3 : Buzzer tone gen                        *
 *__________________________________________________________*/

void sing_buzz(int t){

    unsigned int i = 0;
    while (state == state3){
        startTimerA1(tones[i]);

        i = (i+1 )%7;
        delay(t);
    }
    TA1CTL = MC_0; //stop timer
}
/*__________________________________________________________
 *                                                          *
 *          STATE 5 : LDR measurement display               *
 *__________________________________________________________*/

void LDR_measurement(int t){
    while (state == state5){


        //make ADC conversion
        ADC_config();

        ADC_start();

        enable_interrupts();
        enterLPM(mode0);

        ADC10CTL0 &= ~ADC10ON;                    // Disable ADC10 interrupt

        //Display results
        lcd_reset();
        lcd_puts("LDR[mv]:");
        lcd_print_voltage(ADC10MEM * 3.4);       // Display results

        //Sleep for x msec
        delay(t);
    }
    //stopTimerA0();
}



