#ifndef Stepper_H
#define Stepper_H

#include <BOARD.h>

/*******************************************************************************
 * STEPPER MODE #DEFINES                                                       *
 ******************************************************************************/

#if defined FULL_STEP_DRIVE && ( defined HALF_STEP_DRIVE || defined WAVE_DRIVE || defined DRV8811_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

#if defined HALF_STEP_DRIVE && ( defined FULL_STEP_DRIVE || defined WAVE_DRIVE || defined DRV8811_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

#if defined WAVE_DRIVE && ( defined HALF_STEP_DRIVE || defined FULL_STEP_DRIVE || defined DRV8811_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

#if defined DRV8811_DRIVE && ( defined HALF_STEP_DRIVE || defined FULL_STEP_DRIVE || defined WAVE_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define FORWARD 1
#define REVERSE 0

// Coil Enables
#define TRIS_COIL_A_ENABLE TRISFbits.TRISF1     	//PORTZ_04
#define TRIS_COIL_B_ENABLE TRISDbits.TRISD8     	//PORTZ_08

// Coils (A and B)
#define TRIS_COIL_A_DIRECTION TRISEbits.TRISE4  	//PORTZ_03
#define TRIS_COIL_A_DIRECTION_INV TRISEbits.TRISE3	//PORTZ_05
#define TRIS_COIL_B_DIRECTION TRISEbits.TRISE2  	//PORTZ_07
#define TRIS_COIL_B_DIRECTION_INV TRISEbits.TRISE1  //PORTZ_09

#define COIL_A_ENABLE LATFbits.LATF1
#define COIL_A_DIRECTION LATEbits.LATE4
#define COIL_A_DIRECTION_INV LATEbits.LATE3
#define COIL_B_ENABLE LATDbits.LATD8
#define COIL_B_DIRECTION LATEbits.LATE2
#define COIL_B_DIRECTION_INV LATEbits.LATE1


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function: Stepper_Init(void);
 * @param none
 * @return SUCCESS or ERROR
 * @brief Initializes the Stepper Module, sets up the stepper on PORTZ
 * @note Defaults to a stepping rate of MED_HZ_RATE
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_Init(void);

/**
 * @Function Stepper_SetRate(unsigned short int rate);
 * @param rate, steps per second, 0 is a special case of 0.5Hz
 * @return SUCCESS or ERROR
 * @brief Sets the stepping rate in steps per second
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_SetRate(uint16_t rate);

/**
 * @Function Stepper_GetRate(void);
 * @param none
 * @return rate in steps per second
 * @brief Gets the stepping rate in steps per second
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
uint16_t Stepper_GetRate(void);

/**
 * @Function: Stepper_SetSteps(char direction, unsigned int steps);
 * @param direction - stepper direction (FORWARD or REVERSE)
 * @param steps - number of steps to take
 * @return SUCCESS or ERROR
 * @brief Sets the number of steps and direction for the stepper drive. Wipes
 *        out any previous values, does NOT start stepping. If the stepper is
 *        already stepping, then the stepper will continue stepping.
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_SetSteps(uint8_t direction, int32_t steps);

/**
 * @Function: Stepper_InitSteps(char direction, unsigned int steps);
 * @param direction - stepper direction (FORWARD or REVERSE)
 * @param steps - number of steps to take
 * @return SUCCESS or ERROR
 * @brief Sets the number of steps and direction for the stepper drive. Wipes
 *        out any previous stepper command and starts stepping.
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_InitSteps(uint8_t direction, int32_t steps);

/**
 * @Function: Stepper_StartSteps(void);
 * @param none
 * @return SUCCESS or ERROR
 * @brief Starts the stepper motor stepping
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_StartSteps(void);

/**
 * @Function: Stepper_StopSteps(void);
 * @param none
 * @return SUCCESS or ERROR
 * @brief Stops the stepper motor stepping
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_StopsSteps(void);

/**
 * @Function: Stepper_GetRemainingSteps(void);
 * @return number of remaining steps
 * @brief Returns the number of remaining steps
 * @author Gabriel Hugh Elkaim, 2012.01.28 23:21 */
int32_t Stepper_GetRemainingSteps(void);

/**
 * @Function: Stepper_GetDirection(void);
 * @return FORWARD or REVERSE
 * @brief Returns the current direction (or previous if stopped)
 * @author Gabriel Hugh Elkaim, 2012.01.28 23:21 */
int8_t Stepper_GetDirection(void);

/**
 * @Function: Stepper_IsStepping(void);
 * @return TRUE or FALSE
 * @brief Returns TRUE if the stepper is currently stepping, FALSE otherwise
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_IsStepping(void);

/**
 * @Function: Stepper_End(void);
 * @return SUCCESS or ERROR
 * @brief Shuts down the stepper driver software module. Module can be re-enabled
 *        using a stepper init.
 * @author Gabriel Hugh Elkaim, 2012.01.28 23:21 */
int8_t Stepper_End(void);

/**
 * @Function: WaveDrive(void)
 * @param none
 * @return none
 * @remark Implements the wave drive state machine in terms of switching
 *         the coils in the right sequence.
 * @author [Your Name]
 * @date [Current Date] */
static void WaveDrive(void);

/**
 * @Function: HalfStepDrive(void)
 * @param none
 * @return none
 * @remark Implements the half step drive state machine in terms of switching
 *         the coils in the right sequence.
 * @author [Your Name]
 * @date [Current Date] */
static void HalfStepDrive(void);

/**
 * @Function: DRV8811Drive(void)
 * @param none
 * @return none
 * @remark Implements the control for a DRV8811 driver by generating
 *         appropriate STEP and DIR signals.
 * @author [Your Name]
 * @date [Current Date] */
static void DRV8811Drive(void);

// Function prototypes for the new stepper functions
int8_t Stepper_SetDriveMode(uint8_t mode);

uint16_t Stepper_GetMaxStepRate(void);

int8_t Stepper_Enable(void);

int8_t Stepper_Disable(void);

int8_t Stepper_Step(uint8_t direction);

#endif
