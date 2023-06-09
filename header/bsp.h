#ifndef _bsp_H_
#define _bsp_H_
////UPDATE14;55
#include  <msp430g2553.h>          // MSP430x2xx
//#include  <msp430xG46x.h>  // MSP430x4xx


#define   debounceVal           10000
//#define   LEDs_SHOW_RATE      0xFFFF  // 62_5ms

// RGB abstraction
//#define RGBArrPortOut         P2OUT

// LEDs abstraction
#define LED_RGB_Port            P2OUT
#define LED_RGB_Dir             P2DIR
#define LEDs_RGB_Sel            P2SEL
#define LED_R                0x01   // P1.0
#define LED_G                0x02  // P1.1
#define LED_B                0x04  // P1.2
#define LED_W         0x07  // P1.0-P1.2

// LCDs abstraction
#define LCD_DATA_WRITE          P1OUT
#define LCD_DATA_DIR            P1DIR
#define LCD_DATA_READ           P1IN
#define LCD_DATA_SEL            P1SEL
#define LCD_CTL_SEL             P2SEL

////   Generator abstraction
//#define GenPort               P2IN
//#define GenPortSel            P2SEL
//#define GenPortDir            P2DIR
//#define GenPortOut            P2OUT

//   Buzzer abstraction       //P2.4
#define BuzzPortSel             P2SEL
#define BuzzPortDir             P2DIR
#define BuzzPortOut             P2OUT
#define BuzzPin                 BIT4


//uart abstraction
#define TXLED                   BIT0
#define RXLED                   BIT6
#define TXD                     BIT2
#define RXD                     BIT1

//  Keypad abstraction
#define KeypadPortSel         P10SEL
#define KeypadPortDIR         P10DIR
#define KeypadPortOUT         P10OUT
#define KeypadPortIN         P10IN
#define KeypadIRQPort         P2IN
#define KeypadIRQIntPend      P2IFG
#define KeypadIRQIntEn        P2IE
#define KeypadIRQIntEdgeSel   P2IES
#define KeypadIRQPortSel      P2SEL
#define KeypadIRQPortDir      P2DIR
#define KeypadIRQPortOut      P2OUT


//// PushButton 3 abstraction for Main Lab
//#define PB3sArrPort         P2IN
//#define PB3sArrIntPend      P2IFG
//#define PB3sArrIntEn        P2IE
//#define PB3sArrIntEdgeSel   P2IES
//#define PB3sArrPortSel      P2SEL
//#define PB3sArrPortDir      P2DIR
//#define PB3sArrPortOut      P2OUT

// PushButtons abstraction
//#define PBsArrPort	       P1IN
//#define PBsArrIntPend	   P1IFG
//#define PBsArrIntEn	       P1IE
//#define PBsArrIntEdgeSel   P1IES
//#define PBsArrPortSel      P1SEL
//#define PBsArrPortDir      P1DIR
//#define PBsArrPortOut      P1OUT
//#define PB0                0x01   // P1.0
//#define PB1                0x02  // P1.1
//#define PB2                0x04  // P1.2
//#define PB3                0x10  // P2.0

//TIMERA0
extern void startTimerA0(int x);
extern void stopTimerA0(void);
extern void startTimerA1(int freq);
extern void stopTimerA1(void);
extern void startTimerB(int freq);
extern void GPIOconfig(void);
extern void TIMER_A0_config(void);
extern void TIMERB_config(void);
extern void StopAllTimers(void);
extern void confDMA3(void);

// DMA config
extern void DMA_sw_trigger();
extern void DMA_DATA(void);
extern void DMA_config1();
extern void DMA_set_adresses(char src[],char dst[], int size);
extern void DMA_config3();

extern void ADC_config();
extern void ADC_start();

extern void UART_init();
extern void DCO_config();

#endif


