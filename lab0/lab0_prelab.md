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

 - FLEFT_BUMP_MASK: Outputs and checks the battery level of the roach

 - FRIGHT_BUMP_MASK: Checks the roach's light sensors.

 - RLEFT_BUMP_MASK: Cheks the left motor 

 - RRIGHT_BUMP_MASK: Cheks the right motor 

3. Psuedocode for additional test harness:

```c
switch(controller_event):

    case (forward):
        Check both front tires active to go forward.

    case (backward):

    case (pivot_turn):

    case (final_turn):
```

# Part 5 - Event Detection

1. Create a pseudocode prototype of your event checkers for the bump sensors and the light sensor.

2. Include a description of the modifications to ES Configure.h so that the test harness will run your event checkers.

# Part 6 - Better Event Detection

1. Create a pseudocode prototype of your “better” event checkers for the bump sensors and the light sensor with debounce and hysteresis bounds. 

2. Include a description of the modifications to ES Configure.h so that the test harness will run your event checkers.

# Part 7 - Finite State Machine (FSM)

1. Spend time to discuss your state machine with your partner. A well-named and labeled state machine diagram will save you hours of lab time. Test it out with your partner by imagining events and inputs and seeing what happens—before you code.

2. Create a good drawing of your FSM with all states and transitions labeled. A neat hand drawing or a program like Draw.io should work.

3. Create a list of the helper functions you think you will need, with a brief explanation of what they do (refer to Roach.h for examples).

# Part 8 - Hierarchial State Machine (HSM)

1. Spend time to discuss your HSM4 with your partner. A well-named and labeled state machine diagram will save you hours of lab time. Test it out with your partner by imagining events and inputs and seeing what happens—before you code.

2. Create a good drawing of your HSM with all states (including sub-states) and transitions labeled. A neat hand drawing or a program like Draw.io should work
