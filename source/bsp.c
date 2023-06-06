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
    BuzzPortDir &= ~BIT4;             // P2.4 Output compare - '1'
    BuzzPortSel |= BIT4;             // P2.4 Select = '1'
    BuzzPortOut &= ~BIT4;             // P2.4 out = '0'

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


    TACCR0 = x;  // Timer Cycles - max
    TA0CTL = TASSEL_2 + MC_1 + ID_3;  //  select: 2 - SMCLK ;
    TA0CCTL0 = CCIE;

    //control: 1 - Up  ;
    //divider: 3 - /8
    // no ACLCK, we use SMCLK.
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
 *             Timer A1                 *
 *      x*1msec configuration           *
 *______________________________________*/
// Configure Timer A1
void startTimerA1(int t) {
    TA1CCR0 = t;                   // Timer Cycles - frequency
    TA1CCR1 = (int)t/2;                 // Timer Cycles - duty cycle
    //control: 3 - Up/Down  ;
    //divider: 0 - /1
    TA1CTL = TASSEL_2 + MC_1;  //  select: 2 - SMCLK ;
    TA1CCTL2 = OUTMOD_7;           // TACCR2 toggle

    // no ACLCK, we use SMCLK.
}
//-------------------------------------------------------------------------------------
//            Timer A1 PWM configuration
//-------------------------------------------------------------------------------------
void TIMERB_config(void){
       //FLL_CTL0 |= XCAP14PF;         // Configure load caps remove later
    TA1CCTL1 = OUTMOD_4;         // TACCR1 toggle
    TA1CCR0 = 1000;
    TA1CTL = TASSEL_2 + MC_1;   //SMCLK, up-mode
}


void ADC_config(){
    ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;             // ADC10ON, interrupt enabled
    ADC10CTL1 = INCH_3 + ADC10SSEL_3;                       // input A3 and SMCL // ADC10CLK/8
    ADC10AE0 |= BIT3;                                       // P1.3 ADC option select
}

void ADC_start(){
    ADC10CTL0 |= ENC + ADC10SC;                             // Sampling and conversion start
}




/** _______________________________________________________________________________________________*
 *                                                                                                 *
 *                                DCO config                                                       *
 *                                                                                                 *
 *  -----------------------------------------------------------------------------------------------*
 * sets the clock frequency of the microcontroller to                                              *
 * 1 MHz using the DCO (Digitally Controlled Oscillator).                                          *
 *                                                                                                 *
 *_________________________________________________________________________________________________*/

void DCO_config() {

    if (CALBC1_1MHZ==0xFF)                  // If calibration constant erased
        while(1);                               // do not load, trap CPU!!


    DCOCTL = 0;                               // Select lowest DCOx and MODx settings

    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO Frequency Range
    DCOCTL = CALDCO_1MHZ;                      // Set DCO specific frequency within the range



    P2DIR = 0xFF;                             // All uuu.x outputs
    P2OUT = 0;                                // All P2.x reset
    P1SEL = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
    P1DIR |= RXLED + TXLED;
    P1OUT &= 0x00;
}
/** _______________________________________________________________________________________________*
 *                                                                                                 *
 *                                      UART init                                                  *
 *                                                                                                 *
 *  -----------------------------------------------------------------------------------------------*
 * initializes the UART communication module (USCI) for serial communication.                      *
 *  - UART CLK  - SMCLK                                                                            *
 *_________________________________________________________________________________________________*/
void UART_init() {
    UCA0CTL1 |= UCSSEL_2;                     // UART CLK <- SMCLK

    // configure the transmission rate to 9600 baud
    UCA0BR0 = 104;                           // UART Baud Rate Control registers
    UCA0BR1 = 0x00;                           // 1MHz 9600
    UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
   // __bis_SR_register(LPM0_bits + GIE);       // Enter LPM3 w/ int until Byte RXed
}
