#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
#include "msp430xG46x.h"
////UPDATE14;55
#include "stdio.h"

int count = 0;
int tone = 0;
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
void LED_Blink(int t){
    while (state == state1){
        enable_interrupts();
        LED_RGB_Port ^= LED_R;
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
 *          STATE 3 : DMA Led Shift                          *
 *__________________________________________________________*/
void audio_player(){
    disable_interrupts();
    StopAllTimers(); // Stop All Timers(A,B,DMA)

    //Init Timer A and Timer B
    TIMER_A0_config(); // For delay
    TIMERB_config();  // For PWM

    //Choose Selected Song according to the keypad number that was pressed

    //lcd_reset(); DMA0SA = (void(*)()) &tones; DMA0SZ = Song1Size; DMA_config(); lcd_puts("Playing tones"); break;

    enable_interrupts();
}



void Buzz_pwm(int freq){
    while (tone == freq){

        BuzzPortOut ^= BuzzPin;
        int t = (int)(0x1820/freq);
        enable_interrupts();
        //startTimerA0(delay);
        startTimerA1(t);

    }
    //stopTimerA0();
}

void sing_buzz(float tones[],int delay){
    while (state == state3){
        startTimerA0(delay);
        Buzz_pwm(tones[tone]);
        enable_interrupts();
        tone++;
        if (i == 7){
            i = 0;
        }
    }

}
    //stopTimerA0();
/*__________________________________________________________
 *                                                          *
 *          STATE 4 : LDR measurement display               *
 *__________________________________________________________*/

void LDR_measurement(int t){
    while (state == state4){


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



