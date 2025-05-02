/**
 * @file Stepper_Extension.h
 * @brief Extension to the Stepper module providing additional functionality
 * @author Your Name
 * @date Current Date
 */

#ifndef STEPPER_EXTENSION_H
#define STEPPER_EXTENSION_H

#include <BOARD.h>
#include <stdint.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/

// Drive mode constants
#define FULL_STEP_MODE   0
#define HALF_STEP_MODE   1
#define WAVE_DRIVE_MODE  2
#define DRV8811_MODE     3

// Maximum step rate for the stepper motor (steps per second)
#define MAX_STEP_RATE 2000

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function Stepper_SetDriveMode(uint8_t mode)
 * @param mode - One of the drive mode defines (FULL_STEP_MODE, HALF_STEP_MODE, etc.)
 * @return SUCCESS or ERROR
 * @brief Sets the stepper driving mode
 */
int8_t Stepper_SetDriveMode(uint8_t mode);

/**
 * @Function Stepper_GetMaxStepRate(void)
 * @param none
 * @return Maximum supported step rate in steps per second
 * @brief Returns the maximum supported step rate
 */
uint16_t Stepper_GetMaxStepRate(void);

/**
 * @Function Stepper_Enable(void)
 * @param none
 * @return SUCCESS or ERROR
 * @brief Enables power to the stepper motor
 */
int8_t Stepper_Enable(void);

/**
 * @Function Stepper_Disable(void)
 * @param none
 * @return SUCCESS or ERROR
 * @brief Disables power to the stepper motor
 */
int8_t Stepper_Disable(void);

/**
 * @Function Stepper_Step(uint8_t direction)
 * @param direction - FORWARD or REVERSE
 * @return SUCCESS or ERROR
 * @brief Takes a single step in the specified direction
 */
int8_t Stepper_Step(uint8_t direction);

#endif /* STEPPER_EXTENSION_H */
