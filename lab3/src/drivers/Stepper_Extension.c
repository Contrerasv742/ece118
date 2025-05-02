/**
 * @file Stepper_Extension.c
 * @brief Additional functions for stepper motor control that don't depend on external definitions
 * @author Your Name
 * @date Current Date
 */

#include <xc.h>
#include "Stepper.h"
#include "Stepper_Extension.h"
#include <stdio.h>

/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

// Current drive mode
static uint8_t currentDriveMode = FULL_STEP_MODE;

// Step direction for self-contained implementation
static uint8_t localStepDir = FORWARD;

// Implementation of the step functions
static void localFullStepDrive(void) {
    static enum {
        step_one, step_two, step_three, step_four,
    } coilState = step_one;

    switch (coilState) {
        case step_one:
            // coil drive both forward
            COIL_A_DIRECTION = 1;
            COIL_A_DIRECTION_INV = 0;
            COIL_B_DIRECTION = 1;
            COIL_B_DIRECTION_INV = 0;
            if (localStepDir == FORWARD) {
                coilState = step_two;
            } else {
                coilState = step_four;
            }
            break;

        case step_two:
            // coil drive A forward, B reverse
            COIL_A_DIRECTION = 1;
            COIL_A_DIRECTION_INV = 0;
            COIL_B_DIRECTION = 0;
            COIL_B_DIRECTION_INV = 1;
            if (localStepDir == FORWARD) {
                coilState = step_three;
            } else {
                coilState = step_one;
            }
            break;

        case step_three:
            // coil drive both reverse
            COIL_A_DIRECTION = 0;
            COIL_A_DIRECTION_INV = 1;
            COIL_B_DIRECTION = 0;
            COIL_B_DIRECTION_INV = 1;
            if (localStepDir == FORWARD) {
                coilState = step_four;
            } else {
                coilState = step_two;
            }
            break;

        case step_four:
            // coil drive A reverse, B forward
            COIL_A_DIRECTION = 0;
            COIL_A_DIRECTION_INV = 1;
            COIL_B_DIRECTION = 1;
            COIL_B_DIRECTION_INV = 0;
            if (localStepDir == FORWARD) {
                coilState = step_one;
            } else {
                coilState = step_three;
            }
            break;
    }
}

static void localHalfStepDrive(void) {
    static enum {
        half_step_one, half_step_two, half_step_three, half_step_four,
        half_step_five, half_step_six, half_step_seven, half_step_eight
    } halfStepState = half_step_one;
    
    switch (halfStepState) {
    case half_step_one:
        // Only coil A forward
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_two;
        } else {
            halfStepState = half_step_eight;
        }
        break;

    case half_step_two:
        // Coil A forward, coil B forward
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_three;
        } else {
            halfStepState = half_step_one;
        }
        break;

    case half_step_three:
        // Only coil B forward
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_four;
        } else {
            halfStepState = half_step_two;
        }
        break;

    case half_step_four:
        // Coil A reverse, coil B forward
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_five;
        } else {
            halfStepState = half_step_three;
        }
        break;

    case half_step_five:
        // Only coil A reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_six;
        } else {
            halfStepState = half_step_four;
        }
        break;

    case half_step_six:
        // Coil A reverse, coil B reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_seven;
        } else {
            halfStepState = half_step_five;
        }
        break;

    case half_step_seven:
        // Only coil B reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_eight;
        } else {
            halfStepState = half_step_six;
        }
        break;

    case half_step_eight:
        // Coil A forward, coil B reverse
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (localStepDir == FORWARD) {
            halfStepState = half_step_one;
        } else {
            halfStepState = half_step_seven;
        }
        break;
    }
}

static void localWaveDrive(void) {
    static enum {
        step_one, step_two, step_three, step_four,
    } coilState = step_one;

    switch (coilState) {
    case step_one:
        // Only coil A forward
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            coilState = step_two;
        } else {
            coilState = step_four;
        }
        break;

    case step_two:
        // Only coil B forward
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            coilState = step_three;
        } else {
            coilState = step_one;
        }
        break;

    case step_three:
        // Only coil A reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (localStepDir == FORWARD) {
            coilState = step_four;
        } else {
            coilState = step_two;
        }
        break;

    case step_four:
        // Only coil B reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (localStepDir == FORWARD) {
            coilState = step_one;
        } else {
            coilState = step_three;
        }
        break;
    }
}

static void localDRV8811Drive(void) {
    // Set direction pin based on stepDir
    // Use COIL_A_DIRECTION as DIR pin
    if (localStepDir == FORWARD) {
        COIL_A_DIRECTION = 1;
    } else {
        COIL_A_DIRECTION = 0;
    }
    
    // Generate step pulse (active high)
    // Use COIL_B_DIRECTION as STEP pin
    COIL_B_DIRECTION = 1;
    
    // Short delay for pulse width (typically 1-2 microseconds for DRV8811)
    // This is a simple busy-wait loop to create a delay
    // Adjust the count based on your MCU clock speed to get around 2μs
    int i;
    for (i = 0; i < 10; i++) {
        __asm("nop");  // No-operation instruction for a short delay
    }
    
    // Complete the step pulse
    COIL_B_DIRECTION = 0;
    
    // DRV8811 needs some minimum time between steps (≥ 1.9μs)
    // Add another small delay if stepping at very high rates
    for (i = 0; i < 5; i++) {
        __asm("nop");
    }
}

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function Stepper_SetDriveMode
 * @param mode - The drive mode to use (FULL_STEP_MODE, HALF_STEP_MODE, etc.)
 * @return SUCCESS or ERROR
 * @brief Sets the stepper driving mode
 */
int8_t Stepper_SetDriveMode(uint8_t mode) {
    // Validate the drive mode
    if (mode > DRV8811_MODE) {
        return ERROR;
    }
    
    // Set the current drive mode
    currentDriveMode = mode;
    
    return SUCCESS;
}

/**
 * @Function Stepper_GetMaxStepRate
 * @return Maximum supported step rate in steps per second
 * @brief Returns the maximum step rate supported by the hardware
 */
uint16_t Stepper_GetMaxStepRate(void) {
    return MAX_STEP_RATE;
}

/**
 * @Function Stepper_Enable
 * @return SUCCESS or ERROR
 * @brief Enables power to the stepper motor
 */
int8_t Stepper_Enable(void) {
    // Turn on both coils
    COIL_A_ENABLE = 1;
    COIL_B_ENABLE = 1;
    
    return SUCCESS;
}

/**
 * @Function Stepper_Disable
 * @return SUCCESS or ERROR
 * @brief Disables power to the stepper motor
 */
int8_t Stepper_Disable(void) {
    // Turn off both coils
    COIL_A_ENABLE = 0;
    COIL_B_ENABLE = 0;
    
    return SUCCESS;
}

/**
 * @Function Stepper_Step
 * @param direction - FORWARD or REVERSE
 * @return SUCCESS or ERROR
 * @brief Takes a single step in the specified direction
 */
int8_t Stepper_Step(uint8_t direction) {
    // Set direction
    localStepDir = direction;
    
    // Turn on drive
    COIL_A_ENABLE = 1;
    COIL_B_ENABLE = 1;
    
    // Execute the appropriate drive function based on mode
    switch (currentDriveMode) {
        case FULL_STEP_MODE:
            localFullStepDrive();
            break;
        case HALF_STEP_MODE:
            localHalfStepDrive();
            break;
        case WAVE_DRIVE_MODE:
            localWaveDrive();
            break;
        case DRV8811_MODE:
            localDRV8811Drive();
            break;
        default:
            // Default to full step if mode is invalid
            localFullStepDrive();
            break;
    }
    
    return SUCCESS;
}
