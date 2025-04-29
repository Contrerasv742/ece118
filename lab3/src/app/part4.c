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
#define ALL_LEDS_ON      0x0F  // All LEDs in a bank

// Define pins for L298 H-Bridge control
#define PWM_MOTOR_PIN    PWM_PORTZ06
#define ENABLE_PIN       RC_PORTY07
#define DIRECTION_PIN    PORTZ08_BIT  // Direction control pin
#define SWITCH_PIN       PORTY09_BIT  // Direction switch input

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
    
    // Configure L298 Enable pin
    IO_PortsSetPortOutputs(PORTY, ENABLE_PIN);
    IO_PortsWritePort(PORTY, ENABLE_PIN);
    
    // Configure direction control pins for the H-bridge
    IO_PortsSetPortOutputs(PORTZ, DIRECTION_PIN);
    
    // Configure direction switch input pin with pull-up
    IO_PortsSetPortInputs(PORTY, SWITCH_PIN);
    IO_PortsSetPortPullups(PORTY, SWITCH_PIN);
    
    // Set PWM frequency to 1KHz (default)
    PWM_SetFrequency(PWM_1KHZ);
    
    while (1) {
        // Read potentiometer and switch
        unsigned int pot_value = AD_ReadADPin(AD_PORTV5);
        // TODO: Verify the logic here
        unsigned int switch_state = IO_PortsReadPort(PORTY) & SWITCH_PIN;
        
        // Map potentiometer value to PWM duty cycle (0-1000)
        unsigned int duty_cycle = (pot_value * 1000) / 1023;
        printf("DC Motor duty cycle = %d%%\r\n", duty_cycle/10);
        PWM_SetDutyCycle(PWM_MOTOR_PIN, duty_cycle);
        
        // Set direction based on switch state
        if (switch_state) {
            // Direction 1
            IO_PortsWritePort(PORTZ, DIRECTION_PIN);
            printf("Direction: Clockwise\r\n");
        } else {
            // Direction 2
            IO_PortsClearPortBits(PORTZ, DIRECTION_PIN);
            printf("Direction: Counter-Clockwise\r\n");
        }
        
        /* LED Display for speed and direction */
        // Default: All LEDs off
        LED_SetBank(LED_BANK1, 0);
        LED_SetBank(LED_BANK2, 0);  
        LED_SetBank(LED_BANK3, 0);
        
        // Calculate how many LEDs to light (0-12 LEDs for 0-3.3V)
        unsigned int num_leds = (pot_value * 12) / 1023;
        
        // Display speed on LEDs
        if (num_leds <= 4) {
            // Direction indication on top bit
            unsigned char led_pattern = (1 << num_leds) - 1;
            if (switch_state) {
                led_pattern |= 0x08;  // Set MSB for direction
            }
            LED_SetBank(LED_BANK1, led_pattern);
        } else if (num_leds <= 8) {
            // Bank 1 fully lit, light 0-4 LEDs in Bank 2
            unsigned char led_pattern = (1 << (num_leds - 4)) - 1;
            if (switch_state) {
                led_pattern |= 0x08;  // Set MSB for direction
            }
            LED_SetBank(LED_BANK1, ALL_LEDS_ON);
            LED_SetBank(LED_BANK2, led_pattern);
        } else {
            // Banks 1 & 2 fully lit, light 0-4 LEDs in Bank 3
            unsigned char led_pattern = (1 << (num_leds - 8)) - 1;
            if (switch_state) {
                led_pattern |= 0x08;  // Set MSB for direction
            }
            LED_SetBank(LED_BANK1, ALL_LEDS_ON);
            LED_SetBank(LED_BANK2, ALL_LEDS_ON);
            LED_SetBank(LED_BANK3, led_pattern);
        }
    }
    return 0;
}
#endif 
