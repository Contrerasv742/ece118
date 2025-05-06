#include <BOARD.h>
#include "RC_Servo.h"
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "pwm.h"
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"

// Define thresholds for LED display
#define LOW_THRESHOLD    341   // ~1/3 of 1023
#define MEDIUM_THRESHOLD 682   // ~2/3 of 1023
#define ALL_LEDS_ON      0x0F  

// Define pins for DC motor control
#define PWM_MOTOR_PIN    PWM_PORTZ06  // This is correct as it's a valid PWM pin

#define PART2
#ifdef PART2
int main(void) {
    ES_Return_t ErrorType;
    
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    LED_Init();
    PWM_Init();  
    
    /* Pin Configuration */
    // 1) UNO Pot Input
    if (AD_AddPins(AD_PORTV5) != SUCCESS) {
        printf("Failed to add pins");
        return -1;
    }

    // 3) PWM (square wave) output for DC motor
    // PWM pin setup for motor control
    if (PWM_AddPins(PWM_MOTOR_PIN) != SUCCESS) {
        printf("Failed to add PWM pins\r\n");
        return -1;
    }

    // 4) Pins for the LEDs
    if (LED_AddBanks(LED_BANK1|LED_BANK2|LED_BANK3) != SUCCESS) {
        printf("Failed to add pins");
        return -1;
    }
    
    // Set PWM frequency to 1KHz (default)
    PWM_SetFrequency(PWM_1KHZ);
    
    while (1) {
        // Read potentiometer
        unsigned int pot_value = AD_ReadADPin(AD_PORTV5);
        
        // Map potentiometer value to PWM duty cycle (0-1000)
        unsigned int duty_cycle = (pot_value * 1000) / 1023;
        printf("DC Motor duty cycle = %d%%\r\n", duty_cycle/10);
        PWM_SetDutyCycle(PWM_MOTOR_PIN, duty_cycle);
        
        // Default: All LEDs off
        LED_SetBank(LED_BANK1, 0);
        LED_SetBank(LED_BANK2, 0);  
        LED_SetBank(LED_BANK3, 0);
        
        // Calculate how many LEDs to light (0-12 LEDs for 0-3.3V)
        unsigned int num_leds = (pot_value * 12) / 1023;
        
        // Display LEDs across all three banks
        if (num_leds <= 4) {
            // Light 0-4 LEDs in Bank 1 
            LED_SetBank(LED_BANK1, (1 << num_leds) - 1);
        } else if (num_leds <= 8) {
            // Bank 1 fully lit, light 0-4 LEDs in Bank 2
            LED_SetBank(LED_BANK1, ALL_LEDS_ON);
            LED_SetBank(LED_BANK2, (1 << (num_leds - 4)) - 1);
        } else {
            // Banks 1 & 2 fully lit, light 0-4 LEDs in Bank 3
            LED_SetBank(LED_BANK1, ALL_LEDS_ON);
            LED_SetBank(LED_BANK2, ALL_LEDS_ON);
            LED_SetBank(LED_BANK3, (1 << (num_leds - 8)) - 1);
        }
    }

    return 0;
}
#endif
