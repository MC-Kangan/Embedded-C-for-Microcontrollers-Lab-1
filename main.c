/************************************
 * #pragma directives...
************************************/
#pragma config FEXTOSC = HS
#pragma config RSTOSC = EXTOSC_4PLL 
#pragma config WDTE = OFF        

/************************************
 * #include directives...
 ************************************/
#include <xc.h>

/************************************
 * #define directives...
 ************************************/
#define _XTAL_FREQ 64000000 

/************************************
/ main function
 * ...
************************************/
void main(void) {    
    // setup pin for output (connected to LED1 - RD7)
    LATDbits.LATD7=0;   //set initial output state - LATx registers (output latch); light on (1); light off (0)
    TRISDbits.TRISD7=0; //set TRIS value for pin (output) - TRISx registers (data direction); Tris determines either output(0) of input(1)
    
     // setup pin for output (connected to LED2 - RH3)
    LATHbits.LATH3=0;   //set initial output state - LATx registers (output latch)
    TRISHbits.TRISH3=0; //set TRIS value for pin (output) - TRISx registers (data direction)
    
    // setup pin for input (connected to button1 - RF2)
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin  
    
    // setup pin for input (connected to button2 - RF3)
    TRISFbits.TRISF3=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF3=0; //turn off analogue input on pin  
    
    
    while (1) { //infinite while loop - repeat forever
      
        // PORT == 1 (by default), when both (AND condition) buttons are not pressed, voltage = high, trap in the loop
        while (PORTFbits.RF2 && PORTFbits.RF3); //empty while loop (wait for button press)
      
        // PORT == 0, when button RF2 is pressed, power cut off , voltage = low
        if (!PORTFbits.RF2){
            LATDbits.LATD7 = !LATDbits.LATD7;//toggle LED 1
        }
        // PORT == 0, when button RF3 is pressed, power cut off , voltage = low
         if (!PORTFbits.RF3){
           LATHbits.LATH3 = !LATHbits.LATH3;//toggle LED 2
        }
         
        // Time delay between each iteration of the while(1) loop; The difference between long press and short press is 
        __delay_ms(200); // call built in delay function 
    }
}



        