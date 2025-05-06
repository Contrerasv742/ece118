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
  #block(text(weight: "bold", size: 18pt)[Part 1 -- Concept Evaluation])
  #v(0.5em)
]
// Information
= Archery Robot

== Function and purpose:

#v(1em)
 
Designed to shoot arrows at a target. The target can move and the robot will calculate the angle, distance, and power needed to hit the target.
#v(1em)
 
== Intended Environment: 

#v(1em)
 
The robot will stay in indoor environments, removing conditions such as wind from affecting the trajectory of arrows.
#v(1em)
 
== Robot-Environment Interaction and Performance:

#v(1em)
 
+ Target locating and aiming: accuracy and precision will be used to determine the performance.
+ Projectile Launching: how consistent the projectile velocity is.
+ Environmental adaptation: how well the robot responds to different target shapes and possibly lighting.
#v(1em)
 
== Sensors and Actuators:

#v(1em)
 
+ Sensors
  - Camera for target recognition and aiming
  - Distance Sensors to find the target's distance
  - Force sensor to determine the force in each arrow draw
+ Actuators
  - Servo motor for aiming at the target (tilting mechanism)
  - Linear actuator for drawing back the projectile
= Plant Care Robot

== Function and purpose:

#v(1em)
 
A moving robot intended to take care of plants depending on their individual needs. Will be able to monitor the soil moisture, light conditions, and provide basic functionality such as watering.
#v(1em)
 
== Intended Environment: 

#v(1em)
 
The robot will be in indoor spaces. In order to limit the robot's monitoring station, QR codes will be attached, used to identify a plant as part of the robot's care and specify minimal plant information to aid the robot (i.e. life span, type, water level, etc.).
#v(1em)
 
== Robot-Environment Interaction and Performance:

#v(1em)
 
+ Plant Condition monitoring: accuracy in monitoring the moisture and light readings.
+ Watering Precision: Measured in how much water is actually released from the robot.
+ Navigation between plants: the robot will need some mechanism to move around plants. 
#v(1em)
 
== Sensors and Actuators:

#v(1em)
 
+ Sensors
  - Soil moisture sensor that can be inserted into the soil of each plant
  - Light sensor for ensuring each plant gets sufficient lighting
+ Actuators
  - Water pump for distributing water to the plants
  - Wheel motors for driving the robot navigation system
= Follow-Me Robot

== Function and purpose:

#v(1em)
 
A robot intended to help users carry items around. This robot will help carry items such as groceries, tools, and other relatively small objects. The robot will follow the user by following a user emitted signal.
#v(1em)
 
== Intended Environment: 

#v(1em)
 
The robot is intended to traverse on paved environments. It can do moderate traversal and some terrain adjustment: changes in elevation and varying gripped surfaces.
#v(1em)
 
== Robot-Environment Interaction and Performance:

#v(1em)
 
User following: How well the robot can follow a user
Obstacle avoidance: how well the robot can respond to changes in terrain without aid.
Load carrying: how much and how well (not displaced) the cargo is.
#v(1em)
 
== Sensors and Actuators:

#v(1em)
 
+ Sensors
  - Transceiver for detecting and following a target
  - Camera for aiding in locating the user and avoiding obstacles
+ Actuators
  - A motor for moving the robot around
  - Cargo platform actuators to move the platform up and down
