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
  #block(text(weight: "bold", size: 18pt)[Prelab 3])
  #v(0.5em)
]

// Add vertical space after the title block
#v(2em) 

// Information
== Part 0 -- Preparation for the Lab

1. What one thing and one thing only will you stick into the 14-pin connectors on the boards?

#h(1cm) I will ribbon cables only to the 14-pin connectors on the board.

2. Draw a detailed state diagram for a hypothetical software PWM driver. Include an example plot of the expected output signal for a given frequency and duty cycle.

#align(center, figure(
  image("../imgs/Part0.png", width: 80%),
  caption: [],
  )
)

== Part 1 -- Driving an RC Servo

#align(center, figure(
  image("../imgs/Part1.png", width: 80%),
  caption: [],
  )
)

== Part 2 -- Unidirectional Drive of a DC Motor

#align(center, figure(
  image("../imgs/Part2.png", width: 80%),
  caption: [],
  )
)

```c
int main() {
  // ... 

  // Initialization Section
  AD_Init();
  PWM_Init();
  RC_Init();

  // Specify Pin Usage:
  AD_AddPins(AD_PORTV3|AD_PORTV4);
  RC_AddPins(RC_PORTX03|RC_PORTX04);

  // ... 
}
```

== Part 3 -- Snubbing the Inductive Kickback


#align(center, figure(
  image("../imgs/Part3.png", width: 80%),
  caption: [],
  )
)

== Part 4 -- Bidirectional Control of a DC Motor


#align(center, figure(
  image("../imgs/Part4.png", width: 80%),
  caption: [],
  )
)


```c
int main() {
  // ... 

  // Initialization Section
  AD_Init();
  PWM_Init();
  RC_Init();

  // Specify Pin Usage:
  AD_AddPins(AD_PORTV3|AD_PORTV4);
  RC_AddPins(RC_PORTX04|RC_PORTX05);

  // ... 
}
```

== Part 5 -- Control of a Stepper Motor

#h(1cm)*Note*: The Arrows are determined by the step which is either counter-clockwise or clockwise

#align(center, figure(
  image("../imgs/Part5.png", width: 80%),
  caption: [],
  )
)

#align(center, figure(
  image("../imgs/Full_Step.png", width: 80%),
  caption: [],
  )
)

#align(center, figure(
  image("../imgs/Half_Step.png", width: 80%),
  caption: [],
  )
)

#align(center, figure(
  image("../imgs/Wave.png", width: 80%),
  caption: [],
  )
)

#align(center, table(
  columns: (auto, auto),
  inset: 8pt,
  align: center,
  [*Coil Polarity*], [*Binary Value*],
  [A+ (positive)], [10],
  [A0 (not energized)], [00],
  [A- (negative)], [01],
  [B+ (positive)], [10],
  [B0 (not energized)], [00],
  [B- (negative)], [01],
))

```c
int main() {
  // ... 

  // Initialization Section
  AD_Init();
  LED_Init();
  PWM_Init();
  RC_Init();
  
  // Specify Pin Usage:
  AD_AddPins(AD_PORTV3|AD_PORTV4);
  RC_AddPins(RC_PORTX03|RC_PORTX04|RC_PORTX05);

  // ... 
}
```

== Part 6 -- Stepper Motor using Dedicated Board

#align(center, figure(
  image("../imgs/Part5.png", width: 80%),
  caption: [],
  )
)

```c
int main() {
  // ... 

  // Initialization Section
  AD_Init();
  LED_Init();
  PWM_Init();
  RC_Init();
  HSM_Init();
  
  // Specify Pin Usage:
  AD_AddPins(AD_PORTV3|AD_PORTV4);
  RC_AddPins(RC_PORTX03|RC_PORTX04|RC_PORTX05);

  // ... 
}
```
