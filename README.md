# CH32V003 Analog Read + PWM Write with LCD

A practical embedded project for the **CH32V003F4P6** that reads an analog voltage from a **variable resistor (potentiometer)** using the internal **ADC**, uses that value to control **PWM duty cycle** for LED dimming, and shows the live ADC / voltage / PWM values on an **ST7567 LCD**.

This repository is a combined-peripheral learning project built in **MounRiver Studio**. The repo description is: **"dimming LED with ADC and showing details in a LCD"**.

## Features

- Reads analog input using the CH32V003 ADC
- Generates PWM using TIM1
- Changes LED brightness based on potentiometer position
- Displays live values on an ST7567 LCD
- Organized into reusable modules:
  - `adc_read.c/.h`
  - `pwm_write.c/.h`
  - `st7567.c/.h`
  - `font6x8.c/.h`
  - `main.c`

## Hardware Used

- **MCU:** CH32V003F4P6
- **IDE:** MounRiver Studio
- **Display:** ST7567 LCD
- **Input:** Variable resistor / potentiometer
- **Output:** PWM LED dimming
- Breadboard + jumper wires

## Project Overview

This project combines three peripherals into one working demo:

```text
Variable resistor -> ADC -> PWM duty update -> LED brightness
                         \
                          -> LCD display
```

## LCD Connections

The LCD is connected to **PORTC** like this:

| LCD Pin | Function | CH32V003 Pin |
|---|---|---|
| 1 | CS    | PC2 |
| 2 | RESET | PC0 |
| 3 | RS    | PC1 |
| 4 | SCK   | PC4 |
| 5 | SDA   | PC5 |

## ADC Connection

| Signal | CH32V003 Pin |
|---|---|
| Potentiometer wiper | PD2 |
| Potentiometer end 1 | VDD |
| Potentiometer end 2 | GND |

- `PD2` is used as the ADC input.
- ADC channel used in code: **Channel 3**.

## PWM Output

| Signal | CH32V003 Pin |
|---|---|
| PWM LED output | PC3 |

- PWM is generated using **TIM1 Channel 3**.
- Duty cycle is updated from the ADC reading.

## How It Works

1. The potentiometer produces a variable analog voltage.
2. The ADC converts that voltage to a digital value.
3. The firmware maps the ADC value to the PWM range.
4. TIM1 updates the PWM duty cycle on `PC3`.
5. The LCD displays:
   - raw ADC value
   - calculated millivolts
   - PWM value

## Example LCD Output

```text
ADC_val = 737
Milli volt = 2377
PWM_val = 712
```

## Source Files

- `main.c` - main application logic
- `adc_read.c` / `adc_read.h` - ADC initialization and read functions
- `pwm_write.c` / `pwm_write.h` - TIM1 PWM setup
- `st7567.c` / `st7567.h` - LCD driver (bit-banged interface)
- `font6x8.c` / `font6x8.h` - 6x8 font table

## ADC Notes

ADC is configured for:

- single-channel conversion
- software trigger
- right-aligned data
- calibration before use

Key read sequence:

```c
ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_15Cycles);
ADC_SoftwareStartConvCmd(ADC1, ENABLE);
while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
return ADC_GetConversionValue(ADC1);
```

## PWM Notes

PWM is generated using **TIM1 CH3 on PC3**.

Important timer settings used in this project:

```c
TIM_TimeBaseInitStructure.TIM_Prescaler = 24 - 1;
TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
```

Duty cycle is updated using:

```c
TIM_SetCompare3(TIM1, pwm_value);
```

## LCD Driver Notes

The ST7567 LCD is driven using **software bit-banging** on GPIO pins.

Important fixes during the CH32V003 port:

- corrected SCK pin handling
- configured CS properly
- used normal output mode for bit-banged LCD pins
- fixed pin mapping for CH32V003 PORTC usage

## Build Environment

- **IDE:** MounRiver Studio
- **Language:** C
- **MCU:** CH32V003F4P6

## Why This Project Is Useful

This project is a strong reference example because it combines:

- ADC input
- PWM output
- LCD display
- modular code structure

It can be used later as a base for:

- sensor-based control
- fan speed control
- motor speed control
- embedded UI experiments
- ADC-to-output projects

## Future Improvements

- display voltage as `x.xxx V`
- add ADC averaging / filtering
- smooth PWM response
- create a framebuffer LCD version
- add menu pages or bar-graph display

## Repository

GitHub repository:

`chamindahettiarachchi/CH32v003_Analog_Read_PWM_write_with_LCD`

## Author

**Chaminda Hettiarachchi**

## License

Open for learning, experimentation, and improvement.
