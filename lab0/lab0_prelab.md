---
title="Lab 0 Prelab"
author="Victor Perez Contreras"
date=\today
---

# Part 1 - PCB Assembly and Soldering

1. Watch Videos

2. The iron should be set to either 360 or 420 degrees farenheit depending on if the material is lead or lead-free respectively.

3. The temperature has to be set accordingly as referenced above.

4. A hot weld will lead to discoleration of the material and bad spread of material at the joint. A cold weld will be weak and have very little discoleration.

5. Black in the weld means the heat was excessive leading to burning in the materials.

# Part 2 - "Hello World!" on a roach

None.

# Part 3 - Running the Roach Test Harness

None.

# Part 4 - Roach Hardware Exploration

1. Read

2. Test Harness

 - FLEFT_BUMP_MASK: Outputs and checks the current voltage level of the battery.

 - FRIGHT_BUMP_MASK: Checks the roach's light sensors.

 - RLEFT_BUMP_MASK: Cheks the left motor 

 - RRIGHT_BUMP_MASK: Cheks the right motor 

3. Psuedocode for additional test harness:

```c
// Note: Keyboard presses can be masked together allowing for various input recognition and complex movement recognition (i.e. pivot turn = )

void Motor_Test(void) {
    switch(keyboard_input) {
        case (w):
            // Move the roach forward
            break;
        case (a):
            // Move the roach to the left 
            break;
        case (s):
            // Move the roach backwards
            break;
        case (d):
            // Move the roach to the right
            break;
        case (q):
            // Stop the test
            return;
    }
}
```

# Part 5 - Event Detection

1. Pseudocode prototype of event checkers for the bump sensors and the light sensor.

```c
#define deviation 10
#define BUMP_SENSOR_THRESH 175

#define LOW_THRESH  BUMP_SESONR_THRESH - 10 
#define HIGH_THRESH BUMP_SESONR_THRESH + 10 

void Bump_Sensor_Test(int prev_roach_bumper) {
    int curr_roach_bumper = Roach_ReadBumpers();
    int roach_bumper = 

    switch (roach_bumper) {
        case(FLEFT_BUMP_MASK):
            // Outputs and checks the current voltage level of the battery.
        case(FRIGHT_BUMP_MASK):
            // Checks the roach's light sensors.
        case(RLEFT_BUMP_MASK):
            // Cheks the left motor 
        case(RRIGHT_BUMP_MASK):
            // Cheks the right motor 
        default:
            break;
    }
}
```

2. Include a description of the modifications to ES Configure.h so that the test harness will run your event checkers.

# Part 6 - Better Event Detection

1. Pseudocode prototype for “better” event checkers for the bump sensors and the light sensor with debounce and hysteresis bounds. 

```c

```

2. Include a description of the modifications to ES Configure.h so that the test harness will run your event checkers.


# Part 7 - Finite State Machine (FSM)

1. Spend time to discuss your state machine with your partner. A well-named and labeled state machine diagram will save you hours of lab time. Test it out with your partner by imagining events and inputs and seeing what happens—before you code.

2. Create a good drawing of your FSM with all states and transitions labeled. A neat hand drawing or a program like Draw.io should work.

3. Create a list of the helper functions you think you will need, with a brief explanation of what they do (refer to Roach.h for examples).

# Part 8 - Hierarchial State Machine (HSM)

1. Spend time to discuss your HSM4 with your partner. A well-named and labeled state machine diagram will save you hours of lab time. Test it out with your partner by imagining events and inputs and seeing what happens—before you code.

2. Create a good drawing of your HSM with all states (including sub-states) and transitions labeled. A neat hand drawing or a program like Draw.io should work
