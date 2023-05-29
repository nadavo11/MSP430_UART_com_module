#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer
#include  <stdio.h>
////UPDATE14;55
enum FSMstate state;
unsigned int KB;
enum SYSmode lpm_mode;
unsigned int i = 0;
int x = 500;
float tones[7] = {1,1.25,1.5,1.75,2,2.25,2.5};

void main(void){
   //realtime
  char my_s[100]  ="Wise machines are dramatically more valuable than machines that just store andretrieve information";
  char my_d[100];
  TIMERB_config();

  state = state4;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();     // Configure GPIO, Stop Timers, Init LCD
  lcd_data(0x43);
  while(1){

      switch(state){
	  case state0: //idle - Sleep

	      enterLPM(mode0);
	      break;

	  case state1: //PB0 recorder
          LED_Blink(x);
	    break;

	  case state2: //PB1 Audio player
	      LCD_count(x);
	      break;
		
      case state3: ; // PB2/3 For final lab
              //sing_buzz(tones,x);

          break;

      case state4:
          LDR_measurement(x);
          __bis_SR_register(LPM0_bits + GIE);       // CPU off

		break;
		
	}
  }
  
}

  
  
  
  
  
  
