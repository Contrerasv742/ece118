#include "BOARD.h"
#include "RC_Servo.h"
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "pwm.h"
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"

// TODO: add a section talking about the switch

// Define thresholds for LED display
#define LOW_THRESHOLD    341   // ~1/3 of 1023
#define MEDIUM_THRESHOLD 682   // ~2/3 of 1023
#define ALL_LEDS_ON      0x0F  // All LEDs in a bank

// Define pins for L298 H-Bridge control
#define PWM_MOTOR_PIN   PWM_PORTZ06  // This is correct as it's a valid PWM pin
#define ENABLE_PIN      RC_PORTY07
#define DIRECTION_PIN1  0x0100 
#define DIRECTION_PIN2  0x0200 

#define PART4
#ifdef PART4
int main(void) {
    ES_Return_t ErrorType;
    
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    LED_Init();
    PWM_Init();  
    
    /* Pin Configuration */
    // 1) UNO Pot Input
    AD_AddPins(AD_PORTV5);                  
    // 2) PWM (square wave) output for DC motor
    PWM_AddPins(PWM_MOTOR_PIN);               
    // 3) Pins for the LEDs
    LED_AddBanks(LED_BANK1|LED_BANK2|LED_BANK3);
    
    // Configure direction control pins for the H-bridge
    IO_PortsSetPortOutputs(PORTZ, DIRECTION_PIN1);
    IO_PortsSetPortOutputs(PORTZ, DIRECTION_PIN2);
    
    // Set PWM frequency to 1KHz (default)
    PWM_SetFrequency(PWM_1KHZ);
    
    while (1) {
        // Read potentiometer and switch
        unsigned int pot_value = AD_ReadADPin(AD_PORTV5);
        unsigned int switch_state = 1;
        
        // Map potentiometer value to PWM duty cycle (0-1000)
        unsigned int duty_cycle = (pot_value * 1000) / 1023;
        printf("DC Motor duty cycle = %d%%\r\n", duty_cycle/10);
        PWM_SetDutyCycle(PWM_MOTOR_PIN, duty_cycle);
        
        // Set direction based on switch state
        if (1) {
            // Direction 1
            IO_PortsWritePort(PORTZ, DIRECTION_PIN1);
            IO_PortsClearPortBits(PORTZ, DIRECTION_PIN2);
            printf("Direction: Clockwise\r\n");
        } else {
            // Direction 2
            IO_PortsClearPortBits(PORTZ, DIRECTION_PIN1);
            IO_PortsWritePort(PORTZ, DIRECTION_PIN2);
            printf("Direction: Counter-Clockwise\r\n");
        }
        
        /* LED Display for speed and direction */
        // Default: All LEDs off
        LED_SetBank(LED_BANK1, 0);
        LED_SetBank(LED_BANK2, 0);  
        LED_SetBank(LED_BANK3, 0);
        
        // Calculate how many LEDs to light (0-12 LEDs for 0-3.3V)
        unsigned int num_leds = (pot_value * 12) / 1023;
        
        if (switch_state) {
            if (num_leds <= 4) {
                LED_SetBank(LED_BANK1, (1 << num_leds) - 1);
            } else if (num_leds <= 8) {
                LED_SetBank(LED_BANK1, ALL_LEDS_ON);
                LED_SetBank(LED_BANK2, (1 << (num_leds - 4)) - 1);
            } else {
                LED_SetBank(LED_BANK1, ALL_LEDS_ON);
                LED_SetBank(LED_BANK2, ALL_LEDS_ON);
                LED_SetBank(LED_BANK3, (1 << (num_leds - 8)) - 1);
            }
        } else {
            if (num_leds <= 4) {
                LED_SetBank(LED_BANK3, (1 << (num_leds - 8)) - 1);
            } else if (num_leds <= 8) {
                LED_SetBank(LED_BANK3, ALL_LEDS_ON);
                LED_SetBank(LED_BANK2, (1 << (num_leds - 4)) - 1);
            } else {
                LED_SetBank(LED_BANK2, ALL_LEDS_ON);
                LED_SetBank(LED_BANK2, ALL_LEDS_ON);
                LED_SetBank(LED_BANK1, (1 << num_leds) - 1);
            }
        }

    }
    return 0;
}
#endif 
