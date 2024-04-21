# ARDUINO COIN BASED MOBILE CHARGER

Please follow the following link to learn how to simulate Arduino projects in Proteus: [How to Simulate Arduino in Proteus](https://www.instructables.com/How-to-Simulate-Arduino-in-Proteus/)
The Arduino (.ino) file can be found in the `digilock` folder.

## SOFTWARE USED: 
- Simulation Software: Proteus
- Arduino IDE

## COMPONENTS USED: 
- Arduino Mega 2560 R3
- 16x2 Alphanumeric Liquid Crystal Display
- 4x3 Keypad Matrix
- 5V Relay
- 12 Volts Battery
- Green LED
- Female Type A USB
- Probe (in the Proteus software)
- Push Button*
  *A push button was used to replace the signal of a coin detector since the coin detector device was not available in the Proteus Software. Later modifications to this circuit, however, can include the design of the coin detector from scratch.  

## LIBRARIES USED: 
- Arduino Library for Proteus
- Keypad Library in Arduino
- Liquid Crystal Library in Arduino

## Brief Description of Project: 
A push button was used to represent the coin detector. 
The default state of the relay is Normally Open. 
The program begins by prompting the user to insert a coin (press the button). After the coin is inserted, the system then begins listening for keypress from the keypad. The keys pressed are displayed on the LCD. If the key pressed match the Master Password in the code, the relay switches contacts and enable the flow of electricity to the USB. A probe in the software was used to determine and ensure that the voltage received by the USB is 5V. 
On the other hand, a user has the privilege to set their own password. To set a new password, the user needs to input “#####” via the keypad. The LCD would then display a prompt for a new password. The new password is then followed by a confirmation prompt for the user to confirm their password. The user has 3 attempts to confirm the password. If the user is unsuccessful in confirming the password, the system requests a new password again, followed by a confirmation, then another confirmation which finally triggers the relay to allow 5V to be supplied to the terminals of the USB.
