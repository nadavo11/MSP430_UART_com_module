//MSP430_UART_com_module

#include <msp430.h>

#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1

const char string1[] = { "Hello World\r\n" };
unsigned int i;


int main(void)
{

    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

    if (CALBC1_1MHZ==0xFF)					// If calibration constant erased
    {
        while(1);                               // do not load, trap CPU!!
    }

    /** _______________________________________________________________________________________________*
     *                                                                                                 *
     *                                DCO config                                                       *
     *                                                                                                 *
     *  -----------------------------------------------------------------------------------------------*
     * sets the clock frequency of the microcontroller to                                              *
     * 1 MHz using the DCO (Digitally Controlled Oscillator).                                          *
     *                                                                                                 *
     * ________________________________________________________________________________________________*/
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings

    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO Frequency Range
    DCOCTL = CALDCO_1MHZ;                      // Set DCO specific frequency within the range



    P2DIR = 0xFF;                             // All P2.x outputs
    P2OUT = 0;                                // All P2.x reset
    P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1DIR |= RXLED + TXLED;
    P1OUT &= 0x00;

    /** _______________________________________________________________________________________________*
     *                                                                                                 *
     *                                      UART init                                                  *
     *                                                                                                 *
     *  -----------------------------------------------------------------------------------------------*
     * initializes the UART communication module (USCI) for serial communication.                      *
     *  - UART CLK  - SMCLK                                                                            *
     * ________________________________________________________________________________________________*/


    UCA0CTL1 |= UCSSEL_2;                     // UART CLK <- SMCLK

    // configure the transmission rate to 9600 baud
    UCA0BR0 = 104;                           // UART Baud Rate Control registers
    UCA0BR1 = 0x00;                           // 1MHz 9600
    UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM3 w/ int until Byte RXed
}

/** _______________________________________________________________________________________________*
 *                                                                                                 *
 *                                      TX ISR                                                     *
 *                                                                                                 *
 *  -----------------------------------------------------------------------------------------------*
 * initializes the UART communication module (USCI) for serial communication.                      *
 *  - UART CLK  - SMCLK                                                                            *
 * ________________________________________________________________________________________________*/
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCI0TX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    UCA0TXBUF = string1[i++];                 // TX next character

    if (i == sizeof string1 - 1)              // TX over?
        IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}

/** _______________________________________________________________________________________________*
 *                                                                                                 *
 *                                      RX ISR                                                     *
 *                                                                                                 *
 *  -----------------------------------------------------------------------------------------------*
 * initializes the UART communication module (USCI) for serial communication.                      *
 *  - UART CLK  - SMCLK                                                                            *
 * ________________________________________________________________________________________________*/

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    if (UCA0RXBUF == 'u')                     // 'u' received?
    {
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = string1[i++];
    }
}
