# ML042 Figma Library

Library to control a Figma project using the ML042 board.

## ML042 pinout

![ML042 pinout](https://github.com/marclura/ML042_Figma_Lib/blob/main/doc/ML042_20221031_back.png "ML042 pinout")

| PIN | Analog | Other functions |
| --- | ------ | --------------- |
| G2  | yes    | -               |
| G4  | yes    | -               |
| G5  | no     | -               |
| G12 | yes    | -               |
| G13 | yes    | -               |
| G14 | yes    | -               |
| G15 | yes    | -               |
| G16 | no    | -               |
| G17 | no    | -               |
| G18 | no    | -               |
| G19 | no    | -               |
| G21 | no    | I2C (SDA)       |
| G22 | no    | I2C (SCL         |
| G25 | yes    | -               |
| G26 | yes    | -               |
| G27 | yes    | -               |
| G32 | yes    | -               |
| G33 | yes    | -               |
| G34 | yes    | -               |
| G35 | yes    | -               |


## Potentiometer addPosition() calculation

Considerations to evenly spread the position along the potentiometer range:

DAC range: int dac = 4096
Positions: int pos
Position id: int id = 1-pos

Formula: dac/pos * (1/2 + (id-1))

![ML042Figma potentiometer position values](https://github.com/marclura/ML042_Figma_Lib/blob/main/doc/ML042FIgmaLib_potentiometer_positions_calculator.png "ML042Figma potentiometer position values")

