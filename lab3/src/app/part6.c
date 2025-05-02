#include <BOARD.h>
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "Stepper.h"
#include "Stepper_Extension.h"  // Include the extension header
#include "timers.h"
#include <stdio.h>
#include <xc.h>

// Define constants
#define SWITCH_PIN       PORTY09_BIT  // Direction switch input
#define ALL_LEDS_ON      0x0F         // All LEDs in a bank
#define STEPPER_STEPS    200          // Steps per revolution

// For DRV8811 driver, use the dedicated driver mode
#define DRIVE_MODE       DRV8811_MODE

#define PART6
#ifdef PART6
int main(void) {
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    LED_Init();
    TIMERS_Init();
    
    // Initialize stepper motor control
    Stepper_Init();
    
    // Set the appropriate drive mode for DRV8811
    Stepper_SetDriveMode(DRIVE_MODE);
    
    /* Pin Configuration */
    // 1) UNO Pot Input for controlling speed
    AD_AddPins(AD_PORTV5);
    // 2) Pins for the LEDs to display status
    LED_AddBanks(LED_BANK1 | LED_BANK2 | LED_BANK3);
    
    printf("Part 6 - Stepper Motor Control using DRV8811 Driver\r\n");
    
    // Variables for step timing
    uint16_t stepDelay = 100;  // Initial step delay in milliseconds
    uint16_t stepCounter = 0;
    uint32_t lastStepTime = 0;
    uint16_t maxStepRate = Stepper_GetMaxStepRate();
    
    // Enable the stepper motor
    Stepper_Enable();
    
    // Print initial settings
    printf("Maximum step rate: %d steps/second\r\n", maxStepRate);
    printf("Initial step delay: %d ms\r\n", stepDelay);
    printf("Using DRV8811 driver mode\r\n");
    printf("Rotating stepper motor...\r\n");
    
    while (1) {
        // Read potentiometer and switch
        uint16_t pot_value = AD_ReadADPin(AD_PORTV5);
        uint8_t switch_state = (IO_PortsReadPort(PORTY) & SWITCH_PIN) ? 1 : 0;
        
        // Map potentiometer value to step delay (faster when pot is high)
        // Minimum delay is 1000/maxStepRate ms, maximum is 100ms
        uint16_t min_delay = 1000 / maxStepRate;
        uint16_t max_delay = 100;
        stepDelay = max_delay - ((pot_value * (max_delay - min_delay)) / 1023);
        if (stepDelay < min_delay) stepDelay = min_delay;
        
        // Check if it's time to take a step
        if (TIMERS_GetTime() - lastStepTime >= stepDelay) {
            lastStepTime = TIMERS_GetTime();
            
            // Take a step in the direction determined by switch
            Stepper_Step(switch_state);
            
            // Increment step counter
            stepCounter++;
            if (stepCounter >= STEPPER_STEPS) {
                stepCounter = 0;
                printf("Completed full revolution, current step delay: %d ms\r\n", stepDelay);
            }
        }
        
        /* LED Display for speed and direction */
        // Default: All LEDs off
        LED_SetBank(LED_BANK1, 0);
        LED_SetBank(LED_BANK2, 0);  
        LED_SetBank(LED_BANK3, 0);
        
        // Calculate how many LEDs to light based on speed (0-12 LEDs)
        uint8_t speed_percentage = (pot_value * 100) / 1023;
        uint8_t num_leds = (speed_percentage * 12) / 100;
        
        // Display speed on LEDs
        if (num_leds <= 4) {
            // Direction indication on top bit
            uint8_t led_pattern = (1 << num_leds) - 1;
            if (switch_state) {
                led_pattern |= 0x08;  // Set MSB for direction
            }
            LED_SetBank(LED_BANK1, led_pattern);
        } else if (num_leds <= 8) {
            // Bank 1 fully lit, light 0-4 LEDs in Bank 2
            uint8_t led_pattern = (1 << (num_leds - 4)) - 1;
            if (switch_state) {
                led_pattern |= 0x08;  // Set MSB for direction
            }
            LED_SetBank(LED_BANK1, ALL_LEDS_ON);
            LED_SetBank(LED_BANK2, led_pattern);
        } else {
            // Banks 1 & 2 fully lit, light 0-4 LEDs in Bank 3
            uint8_t led_pattern = (1 << (num_leds - 8)) - 1;
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

// Optional: You can uncomment one of these test functions to include in your main() function
// for testing the maximum step rate or the bidirectional accuracy

/*
// Function to test the maximum reliable step rate
void TestMaximumStepRate(void) {
    printf("Starting Maximum Step Rate Test\r\n");
    printf("-------------------------------\r\n");
    
    uint16_t current_rate = 100;       // Start at 100 steps/second
    uint16_t max_rate = 2000;          // Maximum rate to test
    uint16_t step_increment = 100;     // Increment by 100 steps/second
    uint32_t test_duration = 5000;     // Test each rate for 5 seconds
    
    // Enable the stepper motor
    Stepper_Enable();
    
    // Test loop - increment rates until max_rate
    while (current_rate <= max_rate) {
        printf("Testing step rate: %d steps/second...\r\n", current_rate);
        
        // Calculate step delay in milliseconds
        uint16_t step_delay = 1000 / current_rate;
        
        // Start timing
        uint32_t start_time = TIMERS_GetTime();
        uint32_t last_step_time = start_time;
        uint16_t step_counter = 0;
        
        // Run the test for the specified duration
        while (TIMERS_GetTime() - start_time < test_duration) {
            // Check if it's time to take a step
            if (TIMERS_GetTime() - last_step_time >= step_delay) {
                last_step_time = TIMERS_GetTime();
                
                // Take a step forward
                Stepper_Step(FORWARD);
                
                // Count steps
                step_counter++;
                
                // Display progress on LEDs
                LED_SetBank(LED_BANK1, step_counter & 0x0F);
            }
        }
        
        // Report results
        printf("Completed %d steps at %d steps/second\r\n", step_counter, current_rate);
        uint32_t theoretical_steps = test_duration / step_delay;
        printf("Theoretical steps for %d ms: %d\r\n", test_duration, theoretical_steps);
        printf("-------------------------------\r\n");
        
        // Increment the rate for next test
        current_rate += step_increment;
        
        // Short pause between tests
        uint32_t pause_start = TIMERS_GetTime();
        while (TIMERS_GetTime() - pause_start < 1000) {
            // Wait 1 second
        }
    }
    
    printf("Test complete. Please check for any missed steps.\r\n");
    
    // Disable the stepper motor
    Stepper_Disable();
}
*/

/*
// Function to test if the stepper maintains position during bidirectional movement
void TestBidirectionalAccuracy(void) {
    printf("Starting Bidirectional Accuracy Test\r\n");
    printf("------------------------------------\r\n");
    
    uint16_t test_rate = 500;          // Test rate in steps/second
    uint16_t step_delay = 1000 / test_rate;
    uint16_t cycles = 10;              // Number of forward/backward cycles
    uint16_t steps_per_cycle = STEPPER_STEPS; // One full revolution
    
    printf("Testing with %d steps/second\r\n", test_rate);
    printf("Running %d cycles of %d steps each\r\n", cycles, steps_per_cycle);
    
    // Enable the stepper motor
    Stepper_Enable();
    
    // Run the test cycles
    for (uint16_t cycle = 0; cycle < cycles; cycle++) {
        printf("Cycle %d of %d: Forward...\r\n", cycle + 1, cycles);
        
        // Forward movement
        uint32_t last_step_time = TIMERS_GetTime();
        for (uint16_t step = 0; step < steps_per_cycle; step++) {
            // Wait for step delay
            while (TIMERS_GetTime() - last_step_time < step_delay) {
                // Wait
            }
            
            // Take a step forward
            Stepper_Step(FORWARD);
            last_step_time = TIMERS_GetTime();
            
            // Show progress on LEDs
            LED_SetBank(LED_BANK1, (step & 0x0F));
        }
        
        // Short pause between directions
        uint32_t pause_start = TIMERS_GetTime();
        while (TIMERS_GetTime() - pause_start < 500) {
            // Wait 500ms
        }
        
        printf("Cycle %d of %d: Backward...\r\n", cycle + 1, cycles);
        
        // Backward movement
        last_step_time = TIMERS_GetTime();
        for (uint16_t step = 0; step < steps_per_cycle; step++) {
            // Wait for step delay
            while (TIMERS_GetTime() - last_step_time < step_delay) {
                // Wait
            }
            
            // Take a step backward
            Stepper_Step(REVERSE);
            last_step_time = TIMERS_GetTime();
            
            // Show progress on LEDs
            LED_SetBank(LED_BANK1, (step & 0x0F));
        }
        
        // Short pause between cycles
        pause_start = TIMERS_GetTime();
        while (TIMERS_GetTime() - pause_start < 1000) {
            // Wait 1 second
        }
    }
    
    printf("Test complete. Check if the stepper returned to its starting position.\r\n");
    
    // Disable the stepper motor
    Stepper_Disable();
}
*/
