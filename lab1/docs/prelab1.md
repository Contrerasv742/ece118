---
title: Prelab 0
author: Victor Perez Contreras
date: \today
---

# Part 0

None.

# Part 1:

1. Split rail buffer: 

![Split Rail Buffer](imgs/split_rail_buffer.png)

What voltage do you expect the buffered rail to have?

I expect the buffer rail to have 1/2 of V_{CC} do to the voltage divider.

How much current can you draw from it? 

For this circuit it can draw 30 mA.

Where do you need to inject its output?

The output must be at V_{0}.

2. Non-inverting amplifier: 

![Non-Inverting Amplifier](imgs/non_inverting_amplifier.png)

![Peak Detector Trace](imgs/peak_detector_trace.png)

3. Peak detector: 

![Peak Detector](imgs/peak_detector.png)

Sketch an illustrative input trace and the expected output trace. 

![Peak Detector Trace](imgs/peak_detector_trace.png)

What is a suitable decay time given the input? 

The decay time depends on the beacon that is utilized. For my prelab I will assume a beacon frequency of 2.5kHz. Thus, the period would be 0.4 ms (T). For the decay to fall within the frequency, the decary $\tau$ must be below the period, T. 

$$ \tau < T $$

For a reasonably fast $\tau$ let, 

$$\tau = \frac{T}{2}$$

Then, 

$\tau = 0.2 ms$

What values of R and C achieve this?

Any values of R and C can achieve this as long as they equal $\tau$. However, a capactior larger than 40 $\mu F$ will add delay.

4. Comparator with hysteresis: 

![Sketch of Comparator w/ Hysteresis](imgs/comparator.png)

Work out the values of resistors you need to make the low threshold 1.0v and the high threshold 1.8v.

$v_{h}$ = High Thresh = 1.8V

$v_{l}$ = Low Thresh = 1.0 V

For resistor 1 and 2 their values must be determined. However, R_{3} and R_{4} can be chosen.

$$R_{1} = ?? $$

$$R_{2} = ?? $$

$$R_{3} = 1 MHz$$

$$R_{4} = 3.9 kHz$$

What are the values of the resistors?

In order to hit the thresh hold requirements, $R_{1}$ and $R_{2}$ must be determined based on $R_{3}$ and $R_{4}$.

$$\Delta V = V_{h} - V{l} $$

$$\Delta V = 1.8 - 1 $$

$$\Delta V = 1.8 - 1 $$

$$ n = \frac{\Delta V}{V_{a2}} $$

$$ R_{1} = n x R_{3} = 0.8 \Omega $$

$$ R_{2} = \frac{(R_{1} || R_{3})}{\frac{V_{CC}}{V_{a1}} - 1} $$

$$ R_{1} || R_{3}  = \frac{R_{1}*R_{3}}{R_{1} + R_{3}} $$

$$ R_{1} || R_{3}  = 444.4 $$

$$ \frac{V_{a1} - 1}{{V_{CC}}}  = 4.125 $$

$$ \frac{V_{CC}}{V_{a1}} - 1  = \frac{3.3}{1.8} - 1 $$

$$ = 0.85 $$

$$ R_{2} = \frac{444.4}{0.85} $$

$$ R_{2} = 533.333 k\Omega $$

5. LED and buffer: 

Design a circuit to take the buffered output of the comparator and throw an LED and digital signal. 

![Circuit](imgs/LED.png)

How much current do you expect the LED to draw when the input is at 3V? 

$$ V_{0} = 3V $$:

$$ I = \frac{V_{CC} - V_{o}}{R} $$

$$ I = \frac{3.3 - 3}{50} $$

$$ I = 6 mA $$

What about 0V? For each case, is the LED on or off? 

$$ V_{0} = 0V $$:

$$ I = \frac{V_{CC} - V_{o}}{R} $$

$$ I = \frac{3.3 - 0}{50} $$

$$ I = 66 mA $$

What are the shortcomings of your circuit?

TODO: Verify this is correct with the understanding

If the voltage is increased then the circuit can't produce more current. The draw back then is other components may suffer from voltage limitiation.

# Part 2: 

Draw a schematic for the circuit:

![Sketch of Comparator w/ Hysteresis](imgs/comparator.png)

# Part 3:  

![Butterworth Circuit](imgs/butterworth.png)

![Bode Plots](imgs/bode.png)

1.5kHz sine wave: v(t) = 0.05 × sin(2$pi$ × 1500 × t) + 1.65V

2kHz sine wave: v(t) = 0.05 × sin(2$pi$ × 2000 × t) + 1.65V

2.5kHz sine wave: v(t) = 0.05 × sin(2$pi$ × 2500 × t) + 1.65V

![Sine waves](imgs/sine_waves.png)
