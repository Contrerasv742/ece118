#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "Stepper.h"
#include "timers.h"
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"

// Define for all LEDs in a bank
#define ALL_LEDS_ON     0x0F

// Define DRV8811_DRIVE to use that drive mode in the Stepper module
#define DRV8811_DRIVE

// Define constants for stepper testing
#define STEPPER_STEPS 200
#define MAX_STEP_RATE_TEST 5000  
#define STEP_RATE_INCREMENT 50

// Defines for the Stepper Driver
#define ENABLE_PIN      PORTZ09_LAT
#define DIRECTION_PIN   PORTZ05_LAT
#define STEP_PIN        PORTZ07_LAT

#define ENABLE_TRIS     PORTZ09_TRIS
#define DIRECTION_TRIS  PORTZ05_TRIS
#define STEP_TRIS       PORTZ07_TRIS

void runManualMode(uint16_t *stepCounter, uint32_t *lastStepTime, uint8_t *switch_state); 
void runStepRateTest(uint32_t *lastStepTime, uint16_t *currentStepRate, 
                    uint16_t *maxStepRate, uint8_t *operationMode);
void runRotationTest(uint8_t *rotation_test_active, int32_t *rotation_steps_remaining, 
                    uint8_t *switch_state);
void updateLEDDisplay(uint8_t num_leds);

#define PART6
#ifdef PART6
// Part 6 - Stepper Motor Control using DRV8811 Driver
int main(void) {
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    LED_Init();
    TIMERS_Init();  // Initialize the timers module
    
    /* Pin Configuration */
    // 1) UNO Pot Input for controlling stepper speed
    AD_AddPins(AD_PORTV5);
    
    // 2) Pins for the LEDs to display step count
    LED_AddBanks(LED_BANK1|LED_BANK2|LED_BANK3);
    
    // 3) Initialize the Stepper module (this will configure all necessary pins)
    if (Stepper_Init() != SUCCESS) {
        printf("Error initializing stepper module\r\n");
        while(1); // Halt on error
    }
    
    // 4) Enable the stepper motor
    Stepper_Enable();
    
    // Get the maximum step rate (this is a theoretical maximum from the module)
    printf("Theoretical maximum step rate: %d steps/sec\r\n", Stepper_GetMaxStepRate());
    
    printf("Stepper Motor Control (DRV8811) initialized\r\n");
    
    // HARDCODED VARIABLES - Configure these to control the program
    uint8_t operationMode = 0;  // 0 = Manual, 1 = Test Step Rate, 2 = 360 Test
    static uint16_t stepCounter = 0;
    static uint32_t lastStepTime = 0;
    static uint8_t switch_state = FORWARD;
    static uint16_t currentStepRate = 100;
    static uint16_t maxStepRate = 0;
    static uint8_t rotation_test_active = FALSE;
    static int32_t rotation_steps_remaining = 0;
    
    // Initialize based on hardcoded operation mode
    if (operationMode == 1) {
        // Step Rate Test Mode initialization
        currentStepRate = 100;  // Start at a low rate
        Stepper_SetRate(currentStepRate);
        printf("Step rate test mode active\r\n");
    } else if (operationMode == 2) {
        // Rotation Test Mode initialization
        rotation_test_active = TRUE;
        rotation_steps_remaining = STEPPER_STEPS;  // One full revolution
        switch_state = FORWARD;
        Stepper_SetRate(500);  // Use moderate speed for rotation test
        printf("Rotation test active - forward 360 degrees\r\n");
    } else {
        // Manual Mode initialization
        printf("Manual mode active\r\n");
    }
    
    while (1) {
        switch (operationMode) {
            case 0:  // Manual Mode
                runManualMode(&stepCounter, &lastStepTime, &switch_state);
                break;
                
            case 1:  // Step Rate Test Mode
                runStepRateTest(&lastStepTime, &currentStepRate, &maxStepRate, &operationMode);
                break;
                
            case 2:  // Rotation Test Mode (360 degree forward/backward test)
                runRotationTest(&rotation_test_active, &rotation_steps_remaining, &switch_state);
                break;
        }
    }
    
    return 0;
}

// Function to run manual mode operation
void runManualMode(uint16_t *stepCounter, uint32_t *lastStepTime, uint8_t *switch_state) {
    // Read potentiometer for speed control
    uint16_t pot_value = AD_ReadADPin(AD_PORTV5);
    
    // Use potentiometer to control step rate
    uint16_t manual_rate = 50 + ((pot_value * 950) / 1023);  // Range: 50-1000 steps/sec
    Stepper_SetRate(manual_rate);
    Stepper_SetSteps(FORWARD, manual_rate)
    
    // Check if it's time to take a step (using non-blocking delay)
    if (TIMERS_GetTime() - *lastStepTime >= (1000 / manual_rate)) {
        *lastStepTime = TIMERS_GetTime();
        
        // Take a step in the current direction
        Stepper_Step(*switch_state);
        
        // Toggle direction every 100 steps
        (*stepCounter)++;
        if (*stepCounter >= 100) {
            *stepCounter = 0;
            *switch_state = !(*switch_state);
            printf("Direction changed to: %s\r\n", *switch_state ? "FORWARD" : "REVERSE");
        }
    }
    
    // LED Display calculation
    uint8_t num_leds = (manual_rate * 12) / 1000;
    
    // Update the LED display
    updateLEDDisplay(num_leds);
}

// Function to run step rate test mode
void runStepRateTest(uint32_t *lastStepTime, uint16_t *currentStepRate, 
                    uint16_t *maxStepRate, uint8_t *operationMode) {
    // Incrementally increase step rate to find maximum
    if (TIMERS_GetTime() - *lastStepTime >= 2000) {  // Test each rate for 2 seconds
        *lastStepTime = TIMERS_GetTime();
        
        // Increment the step rate
        *currentStepRate += STEP_RATE_INCREMENT;
        if (*currentStepRate > MAX_STEP_RATE_TEST) {
            // Test complete
            printf("Step rate test complete. Maximum achieved rate: %d steps/sec\r\n", *maxStepRate);
            *operationMode = 0;  // Return to manual mode
            Stepper_SetRate(500);  // Set to moderate speed
        } else {
            // Set the new rate and report it
            Stepper_SetRate(*currentStepRate);
            printf("Testing step rate: %d steps/sec\r\n", *currentStepRate);
            
            // Take a known number of steps and verify completion
            Stepper_InitSteps(FORWARD, 100);  // Take 100 steps
            
            // If successful, update max rate
            if (Stepper_GetRemainingSteps() == 0) {
                *maxStepRate = *currentStepRate;
            }
        }
    }
    
    // LED Display calculation
    uint8_t num_leds = (*currentStepRate * 12) / MAX_STEP_RATE_TEST;
    
    // Update the LED display
    updateLEDDisplay(num_leds);
}

// Function to run rotation test mode
void runRotationTest(uint8_t *rotation_test_active, int32_t *rotation_steps_remaining, 
                    uint8_t *switch_state) {
    if (*rotation_test_active) {
        // If we have steps remaining in this direction
        if (*rotation_steps_remaining > 0) {
            // Take a step in the current direction
            Stepper_Step(*switch_state);
            (*rotation_steps_remaining)--;
            
            // We've completed this direction
            if (*rotation_steps_remaining == 0) {
                printf("Completed %s rotation\r\n", *switch_state ? "FORWARD" : "REVERSE");
                
                // If we just did FORWARD, now do REVERSE
                if (*switch_state == FORWARD) {
                    *switch_state = REVERSE;
                    *rotation_steps_remaining = STEPPER_STEPS;
                    printf("Starting REVERSE rotation\r\n");
                } else {
                    // We've completed both directions
                    printf("Rotation test complete. Check marker position for creep.\r\n");
                    *rotation_test_active = FALSE;
                }
            }
        }
    }
    
    // LED Display calculation
    uint8_t num_leds = (STEPPER_STEPS - *rotation_steps_remaining) * 12 / STEPPER_STEPS;
    
    // Update the LED display
    updateLEDDisplay(num_leds);
}

// Common function to update LED display
void updateLEDDisplay(uint8_t num_leds) {
    // Clear all LED banks
    LED_SetBank(LED_BANK1, 0);
    LED_SetBank(LED_BANK2, 0);  
    LED_SetBank(LED_BANK3, 0);
    
    // Set LED banks based on number of LEDs to light
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
}
#endif
