#include "BOARD.h"
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "RC_Servo.h"
#include "xc.h"
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"

#define LOW_THRESHOLD    341   // ~1/3 of 1023
#define MEDIUM_THRESHOLD 682   // ~2/3 of 1023

#define PART1
#ifdef PART1
void main(void) {
    ES_Return_t ErrorType;
    
    // Initialization Section
    BOARD_Init();
    AD_Init();
    LED_Init();
    RC_Init();

    // Pin Configuration
    AD_AddPins(AD_PORTV5);
    RC_AddPins(RC_PORTV04);
    LED_AddBanks(LED_BANK1|LED_BANK2|LED_BANK3);

    while (1) {
        // Read potentiometer
        unsigned int pot_value = AD_ReadADPin(AD_PORTV5);  

        // Set the Servo Position
        unsigned int pulse_time = 1000 + (pot_value * 1000) / 1023;
        printf("Pulse time = %d\r\n", pulse_time);

        // Set the Servo Pulse Time
        RC_SetPulseTime(RC_PORTV04, pulse_time);
        RC_GetPulseTime(RC_PORTV04);

        // Default: All LEDs off
        LED_SetBank(LED_BANK1, 0);
        LED_SetBank(LED_BANK2, 0);  
        LED_SetBank(LED_BANK3, 0);

        // Decide which bank of LEDs to light up
        if (pot_value < LOW_THRESHOLD) {
            // Turn ON all LEDs in Bank 1
            LED_SetBank(LED_BANK1, 0x0F);  
        } else if (pot_value < MEDIUM_THRESHOLD) {
            // Turn ON all LEDs in Bank 2
            LED_SetBank(LED_BANK2, 0x0F);  
        } else {
            // Turn ON all LEDs in Bank 3
            LED_SetBank(LED_BANK3, 0x0F);  
        }
    }
}
#endif
