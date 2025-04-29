#include <BOARD.h>
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "RC_Servo.h"
#include "pwm.h"
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"

// Define thresholds for LED display
#define LOW_THRESHOLD    341   // ~1/3 of 1023
#define MEDIUM_THRESHOLD 682   // ~2/3 of 1023
#define ALL_LEDS_ON      0x0F  // Added the value for all LEDs in a bank

// Define pins for DC motor control
#define PWM_MOTOR_PIN    PWM_PORTZ06  // Corrected to match the PWM pin used below
#define ENABLE_PIN       RC_PORTY07

#define PART2
#ifdef PART2
int main(void) {
    ES_Return_t ErrorType;
    
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    LED_Init();
    RC_Init();
    PWM_Init();  
    
    /* Pin Configuration */
    // 1) UNO Pot Input
    AD_AddPins(AD_PORTV5);                  
    // 2) RC-Servo Control
    RC_AddPins(RC_PORTV04);                 
    // 3) PWM (square wave) output for DC motor
    PWM_AddPins(PWM_MOTOR_PIN);               
    // 4) Pins for the LEDs
    LED_AddBanks(LED_BANK1|LED_BANK2|LED_BANK3);
    
    // Configure DS3658 enable pin as output and set high to enable
    IO_PortsSetPortOutputs(PORTY, ENABLE_PIN);
    IO_PortsWritePort(PORTY, ENABLE_PIN);
    
    // Set PWM frequency to 1KHz (default)
    PWM_SetFrequency(PWM_1KHZ);
    
    while (1) {
        // Read potentiometer
        unsigned int pot_value = AD_ReadADPin(AD_PORTV5);
        
        // PART 1: RC SERVO CONTROL
        // Set the Servo Position
        unsigned int pulse_time = 1000 + (pot_value * 1000) / 1023;
        printf("Servo pulse time = %d\r\n", pulse_time);
        RC_SetPulseTime(RC_PORTV04, pulse_time);
        
        // PART 2: DC MOTOR CONTROL
        // Map potentiometer value to PWM duty cycle (0-1000)
        unsigned int duty_cycle = (pot_value * 1000) / 1023;
        printf("DC Motor duty cycle = %d%%\r\n", duty_cycle/10);
        PWM_SetDutyCycle(PWM_MOTOR_PIN, duty_cycle);
        
        /* LED Display Stuff */
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
