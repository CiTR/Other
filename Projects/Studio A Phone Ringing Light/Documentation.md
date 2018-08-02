# Studio A Phone Light Project Documentation

### Project General Summary

[//]: # (Comment: &nbsp featured below is for spacing purposes)

&nbsp;&nbsp;&nbsp;&nbsp; This project is a light for studio A which turns on whenever a person calls into the studio. It was made per the request of CiTR programmers for a more noticeable phone light in the studio. Before this project, the only available light wasn't very noticeable, meaning programmers would miss call-ins. The project is a simple circuit composed of an Adafruit Neopixel LED Strip which is controlled by an Arudino Nano V3 controller. The controller will turn the LED strip ON/OFF depending if anyone is calling into Studio A.

&nbsp;&nbsp;&nbsp;&nbsp; In this file, all project related information can be found. This includes the circuit diagram, links to all reference websites and documents, a recorded list of encountered issues and their found solutions, and more. Please refer to the table below to quickly navigate to your desired section of documention. 

    
## Table of Contents

1) [Project General Summary](##project-general-summary)

2) [Project Circuitry](##project-circuitry)

3) [Project Coding](##project-coding)


### Project Circuitry

![alt text](https://github.com/CiTR/Other/blob/master/Projects/Studio%20A%20Phone%20Ringing%20Light/Phone_Light_Project_Circuit_Diagram.png "Project Circuit Diagram")

Featured above is the project circuit diagram which was created using Fritzing.

Starting from the top left we see terminal for our plugin dedicated 5V power supply, it feeds the ground and 5V rails of the entire circuit. To mitigate possible power surges, a 1000uF electrolytic capacitor is installed across our 5V rails.  

Moving down, we see the Arduino Nano. Its two jobs are to monitor the control signal and to turn ON/OFF the LED strip as required, depending on the state of the control signal. 

The control signal is a digital signal sent from an Axia iQ Core GPIO port using an open-collector output, meaning this output functions as an opposite logic output. When the phone line is empty (no call incoming), the pin rests at 5V to indicate a LOGIC 0. When someone is calling, the pin will be pulled down to 0V to indicate a LOGIC 1. Note, the reference 5V for the Arduino input pin is provided internally by the Arduino board by configuring its pin using the "INPUT_PULLUP" assignment. For more details about this assignment please [refer to the Project Coding Section](##project-coding). If the board observes a LOGIC 1 it turns the LED strip ON and otherwise it turns the strip OFF. 

In terms of the phyisical circuit, the control signal is sent through the line called "GPIO Phone-Ringing-Signal Input to Arduino." To limit the current between the Axia core and the Arduino we include a 470ohm resistor. Due to the sensitivity of the Arduino pins, to have the input pin to read 0V (or a LOGIC 1) from the GPIO pin properly, we also must attach the AXIA core's commonon return / ground wire to our circuits ground. For reference we are using one GPIO port where GPIO pin 2 is for the control signal and GPIO pin 7 is for the common return line.

To operate the LED strip we use three wires, two for providing the necessary power and 5V for the strip, and a third for the PWM control signal which controls the behaviour of the strip.  




### Project Coding
