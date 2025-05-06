// Page Information
#set page(
  paper: "a4",
  margin: (x: 2.5cm, y: 2.5cm),
)
#set text(
  font: "New Computer Modern",
  size: 10pt
)
#set par(
  justify: true,
  leading: 0.65em,
)
#align(left)[ 
  Victor Perez Contreras \
  Tae M. Huh \
  ECE 118 \
  April 26, 2025 \
]
// Main Page Info Here
#align(center)[
  #block(text(weight: "bold", size: 18pt)[Part 5 -- Actuator Analysis and Integration])
  #v(0.5em)
]

= Actuator System Design

== DC Motor for Arrow Drawing Mechanism

=== a. Free Body Diagram

#v(20em)

The free body diagram shows the forces acting on the arrow drawing mechanism:

- $F_"motor"$: Force applied by the motor through the linear actuator

- $F_"friction"$: Friction force opposing the motion

- $F_"gravity"$: Gravitational force acting on the arrow and mechanism

- $F_"spring"$: Elastic force from the bow increasing with draw distance


=== b. Force/Torque and Speed Requirements

*Assumptions:*

- Arrow draw weight: 20-30 pounds (88.9-133.4 N) for a typical target bow

- Draw length: 25-30 inches (0.635-0.762 m)

- Drawing time: 2-3 seconds for smooth operation

- Efficiency loss in mechanical linkage: 20%

*Required Force Calculation:*

- Maximum draw force: 133.4 N

- With 20% mechanical loss: 133.4 N / 0.8 = 166.75 N

*Required Speed Calculation:*

- Maximum draw distance: 0.762 m

- Minimum drawing time: 2 seconds

- Required linear speed: 0.762 m / 2 s = 0.381 m/s


*For a linear actuator with lead screw (10 mm pitch):*

- Required rotational speed: (0.381 m/s) / (0.01 m/revolution) = 38.1 revolutions/second = 2286 RPM

- Required torque: (166.75 N × 0.01 m) / (2π × 0.9) = 0.295 Nm (assuming 90% screw efficiency)

=== c. Motor Selection

Based on these requirements, I selected a geared DC motor that can provide the necessary torque and speed.

*Selected Motor: Pololu 37D Metal Gearmotor with 100:1 Gear Ratio*

Part Number: Pololu #1104

#v(20em)

*Specifications:*

- Nominal voltage: 12V

- No-load speed: 37 RPM (at 12V)

- Stall torque: 1.6 N·m (at 12V)

- Stall current: 5.6 A

- No-load current: 300 mA

- Gear ratio: 100:1

*Justification:*

The 100:1 gear ratio provides sufficient torque (1.6 N·m) to overcome the required 0.295 N·m. When used with a lead screw (10 mm pitch), the linear speed is 0.00617 m/s, giving a draw time of 123.5 seconds. This is slower than desired, so the robot will have a two-stage gearing system to optimize both torque and speed.

=== d. Motor Analysis

==== Motor Constants

From the datasheet:

- Terminal Resistance (R): 3.3 Ω

- Stall Current: 5.6 A (at 12V)

- No-load Speed: 37 RPM (at 12V)

- Stall Torque: 1.6 N·m (at 12V)

Calculating motor constants:

- $K_t$ (Torque Constant): Stall Torque / Stall Current = 1.6 N·m / 5.6 A = 0.286 N·m/A

- $K_e$ (Back EMF Constant): (12V - (5.6A × 3.3Ω)) / (37 RPM × 2π/60) = 0.286 V/(rad/s)

==== No-load Speed and Stall Torque

Using an ATX power supply (12V):

- No-load speed: 37 RPM (as per datasheet)

- Stall torque: 1.6 N·m (as per datasheet)


For 9.9V battery power:

- No-load speed: (9.9V / 12V) × 37 RPM = 30.5 RPM

- Stall torque: (9.9V / 12V) × 1.6 N·m = 1.32 N·m


==== Motor Driver

*Selected Driver: TB6612FNG Dual Motor Driver*

#v(20em)

- Max continuous current: 1.2A (3A peak) per channel

- Operating voltage: 4.5V to 13.5V logic, 15V max motor

- PWM frequency: Up to 100 kHz


*Justification:*

The TB6612FNG can handle continuous currents up to 1.2A and peak currents up to 3A. We can use the two channels in parallel to handle up to 2.4A continuous current. It supports PWM for speed control and features direction control via H-bridge configuration. For higher current requirements, we can step up to a driver like the VNH5019 which handles up to 12A continuous.

==== Gearhead Efficiency

From the Pololu datasheet, the efficiency is not directly stated. To calculate efficiency, we would need:

*Information needed:* 

- Mechanical output power at specified operating point

- Electrical input power at the same operating point

Estimating based on typical metal gearboxes:

- Expected efficiency: 70-80% for a 100:1 reduction metal gearbox
