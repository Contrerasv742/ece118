# Part 0

None.

# Part 1:

1. Split rail buffer: What voltage do you expect the buffered rail to have? How much current can you draw from it? (Assume this is an MCP6004 op-amp, like the ones in your lab kit). Where do you need to inject its output?

2. Non-inverting amplifier: For the amplifier, sketch an illustrative input trace and the expected output trace. You’ll need to pick resistor values. Make sure this is for single-ended (0-3.3V) power.

3. Peak detector: Sketch an illustrative input trace and the expected output trace. What is a suitable decay time given the input? What values of R and C achieve this?

4. Comparator with hysteresis: Work out the values of resistors you need to make the low threshold 1.0v and the high threshold 1.8v.

High Thresh:

$$\frac{R_{2}V_{R} + R_{1}V{P}}{R_{1} + R_{2}}$$

Low Thresh: 

$$\frac{R_{2}V_{R} + R_{1}V{N}}{R_{1} + R_{2}}$$

Expected Values:

High Thresh = 1.8V

Low Thresh = 1.0 V

What are the values of the resistors?

5. LED and buffer: Design a circuit to take the buffered output of the comparator and throw an LED and digital signal. How much current do you expect the LED to draw when the input is at 3V? What about 0V? For each case, is the LED on or off? What are the shortcomings of your circuit?

# Part 2: 

Draw a schematic for the circuit:

![Circuit](imgs/circuit.png)
