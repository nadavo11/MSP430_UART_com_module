#include  "../header/bsp.h"    // private library - BSP layer
////UPDATE14;55
/*______________________________________
 *                                      *
 *         GPIO configuration                    *
 *______________________________________*/
void GPIOconfig(void){
    // volatile unsigned int i; // in case of while loop usage

    WDTCTL = WDTHOLD | WDTPW;		// Stop WDT

    // LCD configuration
    LCD_DATA_WRITE &= ~0xFF;
    LCD_DATA_DIR |= 0xF0;    // P1.4-P1.7 To Output('1')
    LCD_DATA_SEL &= ~0xF0;   // Bit clear P2.4-P2.7
    LCD_CTL_SEL  &= ~0xE0;   // Bit clear P2.5-P2.7

    // Buzzer Setup               // P2.4
    BuzzPortDir |= BIT4;             // P2.2 Output compare - '1'
    BuzzPortSel |= BIT4;             // P2.2 Select = '1'
    BuzzPortOut &= ~BIT4;             // P2.2 out = '0'

    //LED Setup
    LED_RGB_Dir |= 0xFF;
    LED_RGB_Port &= ~LED_W;
    LEDs_RGB_Sel  = 0;

    _BIS_SR(GIE);                     // enable interrupts globally

    // Keypad Setup
//  KeypadPortSel &= ~0xFF;
//  KeypadPortDIR = 0x0F; //10.0-10.3 output, 10.4-10.7 input
//  KeypadPortOUT = 0x00; // CLR output

  // Keypad IRQ Setup
//  KeypadIRQPortSel &= ~BIT1;
//  KeypadIRQPortDir &= ~BIT1;             // P2.1 input
//  KeypadIRQIntEdgeSel |= BIT1;         // pull-up mode  P2.1 - '1'
//  KeypadIRQIntEn |= BIT1;               // P2.1 - '1'
//  KeypadIRQIntPend &= ~0xFF;            // clear pending interrupts P2.1

  // PushButtons Setup
//  PBsArrPortSel &= ~0x0F;            //
//  PBsArrPortOut &= ~0x0F;            // Set P1Out to '0'
//  PBsArrPortDir &= ~0x0F;            // P1.0-2 - Input ('0')
//  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode   P1.0-P1.1 - '1'
//  PBsArrIntEdgeSel &= ~0x0C;         // pull-down mode  P1.2 - '0'
//  PBsArrIntEn |= 0x0F;               // P1.0-2 - '1'
//  PBsArrIntPend &= ~0xFF;            // clear pending interrupts P1.0-P1.3 all P1
//

//  // PushButton 3 Setup For Main Lab
//   PB3sArrPortSel &= ~BIT0;           //
//   PB3sArrPortOut &= ~BIT0;            // Set P2Out to '0'
//   PB3sArrPortDir &= ~BIT0;            // P2.0 - Input ('0')
//   PB3sArrIntEdgeSel &= ~BIT0;         // pull-down mode  P2.0 - '0'
//   PB3sArrIntEn |= BIT0;               // P1.0-2 - '1'
//   PB3sArrIntPend &= ~BIT0;            // clear pending interrupts P2.0

}
void TIMER0_A0_config(void){
    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
    TA0CCTL0 = CCIE;
    TACCR0 = 0xFFFF;
    TA0CTL = TASSEL_2 + MC_0 + ID_3;  //  select: 2 - SMCLK ; control: 3 - Up/Down  ; divider: 3 - /8
}
/*______________________________________
 *                                      *
 *              Timer A0                 *
 *      x*1msec configuration           *
 *______________________________________*/

//              StartTimer For Count Down

void startTimerA0(int x){
    // count to x*8

    int t = x*0x82;
    TACCR0 = t;  // Timer Cycles - max
    TA0CTL = TASSEL_2 + MC_1 + ID_3;  //  select: 2 - SMCLK ;
    TA0CCTL0 = CCIE;

    //control: 1 - Up  ;
    //divider: 3 - /8
    // no ACLCK, we use SMCLK.
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}




/*______________________________________
 *                                      *
 *          Stop Timer A0                *
 *______________________________________*/


void StopAllTimers(void){

    TACTL = MC_3; // halt timer A

}

/*______________________________________
 *                                      *
 *              Timer A1                 *
 *      x*1msec configuration           *
 *______________________________________*/
// Configure Timer A1
void startTimerA1(int freq) {
    freq*=1000;                     //KHz to Hz
    int t = (int)(1/freq)*0x820;
    TA1CCR0 = t;                   // Timer Cycles - frequency

    //control: 3 - Up/Down  ;
    //divider: 0 - /1
    TA1CTL = TASSEL_2 + MC_3 + ID_0;  //  select: 2 - SMCLK ;
    TA1CCTL0 = CCIE;


    // no ACLCK, we use SMCLK.
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}
