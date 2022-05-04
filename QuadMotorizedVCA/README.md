# Quad Motorized Voltage Controlled Amplifier


## Abstract
This project aims to create a voltage controlled amplifier that has a preset memory per VCA channel.
The saving of the setting of an individual channel of the four channels of the VCA are accomplished by using a microcontroller 
to read the setting of the wiper of motorized pottentiometer, then scaling that value to a storable value that can be saved to
the microcontroller units onboard EEPROM. Generally, Microcontrollers have a limited number of writes to EEPROM that can be done
before the EEPROM fails. Usually this is around 100,000 writes. This is more than enough write cycles to establish a proof of concept
without having to implement an external EEPROM, or external flash storage. The saving action is initiated by the user long pressing 
the corresponding button per channel. When the user wishes to recall that setting from the EEPROM a button coresponding to each of 
the four channels is short pressed. The stored possition value is recalled and then actuated via the dc motor.

## Hardware
### Principal Design Phase
The initial portion of the design phase for this project was completed using a standard electronics prototyping
breadboard, and a teensy 3.2 development board.

### Revision 1
The first permanent impementation of the motor driver board utilized stripboard, which is a general purpose prototyping
medium for quickly laying out and soldering a circuit. It also transitioned away from using the Teensy 3.2 platform.

### Revision 1.2
This implementation of the motor driver board utilized a home circuit board fabrication method known as
the toner-transfer method, where a circuit PCB layout is rendered using an electronics design automation software such as kiCAD, EagleCAD, or EasyEDA
then exported in a scaled format to a medium that a toner based printer may print on, usually photo paper or glossy magazine paper. The toner is then
transfered to a copper clad plate via exposure to heat under preasure. When the copper plate has had toner sucessfully transfered, it is then put into an etchent
solution. Either Ferric chloride, or a hydrogen-peroxide/Murriatic acid solution to etch the copper that is not screened by the toner.
The board is then processed and components are soldered to it to complete the circuit.

This version was designed to explicitly utilize the Arduino Due platform and it's hardware pin footprint.

### Revision 2
The second revision utilized a more modular approach, which simplified the complexity of the PCB layout, and resultingly the software as well. Still using
the toner transfer fabrication method the modularized circuit allows for any microcontroller to be used via handwiring it directly to the PCB and the 
designated pins declared in the projects code. In the interest of finishing the projected in a timely manner this approach proved successful in light of
the total of five embedded development boards that were damaged beyond use due to wiring errors in testing.

Using this modular hardware design allows for one microcontroller unit to be used per channel. This hardware choice possitively impacted two aspects of the
software implementaion: The total number of EEPROM writes per channel is now 100,000 writes instead of 100,000 writes divided by four channels, and the 
implementaion of software interupts needed for simultaneous function of all four channels memory saving, memory recall and motor functions are no longer an issue.
The motor driver PCB boards hold up to two motor driver channels, and two capacitive touch channels.

### The VCA
The voltage controlled amplifier, or VCA was intended to be based upon the open-source 'Veils' VCA designed by Mutable Instruments specifically version one of the design.
Adapting this circuit was within scope of the project but became unattainable when components essential to the design went out-of-stock. As an alternative, and because during
the testing phase I had access to it, I used a Nuetron Sound DIY VCA kit that had been unassembled. Substituting the linear potentiometers intended for use with the kit for the motorized potentiometers worked well for proof of concept.

## Software
The software can be broken down into several parts: A calibration function, a read EEPROM function, and a write to EEPROM function. The calibration function took the longest to get right
due to the need to account for the drift in absolute value of the potentiometers resistance. Calibration is needed upon every power up of the device in order to assure that the recorded values
are accurately actuated when recalled. The read EEPROM function is called when the corresponding channel button is short pressed and thusly reading the value from the predetermined address in
the EEPROM. The write to EEPROM function is called when a channels button is long pressed, the analog value of the wiper possition is read and converted from a scale of 0-1023 to a scale of 0-255 then stored in the EEPROM.

## Known Issues
Because of the drift in resistance of the pottentiometer due to external factors, even with the calibration procedure upon startup, the recalled value is sometimes overshot.

### Replication

## Hardware
All schematics and board are provided for the motor drive revision 1.2 and 2.0 for replication. Additionally Gerber files have been included for having a PCB fabrication service manufacture a set of PCBs.
Simply upload the gerber .zip file for either revision to a fabrication service such as JLCPCB.com or PCBway.com and then order. Please note that these PCB designs are single layer designs and that the 
coresponding option for single layer PCBs might need to be selected.

## Software
Simply download the Arduino IDE application and install. Choose the applicable board within the program, download the included dependencies from the arduino library manager, and then compile and upload the sketch.