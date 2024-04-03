# 4-20mA loop PIC18F - 2013 Student Project

## What is this ?

This is a student project from 2013, targeting a PIC18F, schematics are available but i don't have the software (proteus suite) to open them anymore, chip was programmed using an [MPLAB ICD2](https://www.microchip.com/en-us/development-tool/MPLAB-ICD-2) with an old MPLAB IDE version, good luck running this in 2024.

The microcontroller fetches 2 wires 4-20mA data from foreign sensor, 6 sensors on the board then a raspberry pi reading gpio pins from i2c data (iirc plagued with a bug sending 0xFFFFFF values from the code).

The project is as it was in the final presentation, except for a few changes in formatting and encoding.

### Ressources

* Not 100% sure for the Datasheet : https://ww1.microchip.com/downloads/en/devicedoc/39632e.pdf
* https://www.electricalclassroom.com/4-20ma-current-loop-concept/

## Why ?

I'm unearthing old projects for fun, that kind of stuff is interesting but my career took another path towards web/api devel


However I still have a dormant interest for the field and hope i will have opportunities to mix electronics & low level code later, [you can email me about that here](mailto:guillaume@nuaj.eu)
