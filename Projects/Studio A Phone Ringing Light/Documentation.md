# Studio A Phone Light Project Documentation

### Project General Summary

[//]: # (Comment: &nbsp featured below is for spacing purposes)

BEFORE MAKING ANY CHANGES TO THIS PROJECT, please make sure to consult the [maintenance and care section](#maintenance-and-care) of this report. If you need to carry out any repairs on the project, please make sure to consult the [Troubleshooting Issues and Their Solutions section](#troubleshooting-issues-and-their-solutions) first.

This project is a light for studio A which turns on whenever a person calls into the studio. It was made by the current technical coordinator at the time, Jarod Ben-Oliel, per the request of CiTR programmers for a more noticeable phone light in the studio. Before this project, the only available light wasn't very noticeable, meaning programmers would miss call-ins. The project is a simple circuit composed of an Adafruit Neopixel LED Strip which is controlled by an Arudino Nano V3 controller. The controller will turn the LED strip ON/OFF depending if anyone is calling into Studio A.

In this file, all project related information can be found. This includes the circuit diagram, links to all reference websites and documents, a recorded list of encountered issues and their found solutions, and more. Please refer to the table below to quickly navigate to your desired section of documention. 

Speaking of references, I first want to give a huge shoutout and thanks to Team Whimsy Makerspace: Mel Lester Jr, whose online project served as my main guide for creating this project. For information regarding his project, please read reference one under the [References and Appreciation section](#references-and-appreciation). I also want to give thanks to my boss, Saman Gharib, for allowing me the chance to make this and for all the help you've given me throughout the process of creating this. 

#

## Table of Contents

1. [Project General Summary](#project-general-summary)

2. [Project Circuitry](#project-circuitry)
    * [Description](#description)
    * [Component List](#component-list) 

3. [Project Coding](#project-coding)

4. [GPIO Configuration](#gpio-configuration)

5. [Maintenance and Care](#maintenance-and-care)

6. [Troubleshooting Issues and Their Solutions](#troubleshooting-issues-and-their-solutions) 

7. [Upgrades and Improvement](#upgrades-and-improvement)

8. [References and Appreciation](#references-and-appreciation) 


#

### Project Circuitry

<img src="https://github.com/CiTR/Other/blob/master/Projects/Studio%20A%20Phone%20Ringing%20Light/Images/Phone_Light_Project_Circuit_Diagram.png" width="1000" height="500">

<img src="https://github.com/CiTR/Other/blob/master/Projects/Studio%20A%20Phone%20Ringing%20Light/Images/Circuit_Module_Photo.jpg" width="450" height="450">

#

##### Description

Featured above is the project circuit diagram (which was created using Fritzing) and a picture of the actual circuit module.

Starting from the top left of the circuit diagram we see terminal for our plugin dedicated 5V power supply, it feeds the ground and 5V rails of the entire circuit. To mitigate possible power surges, a 1000uF electrolytic capacitor is installed across our 5V rails.  

Moving down, we see the Arduino Nano. Its two jobs are to monitor the control signal and to turn ON/OFF the LED strip as required, depending on the state of the control signal. 

The control signal is a digital signal sent from an Axia iQ Core GPIO port using an open-collector output pin, meaning this output functions as an opposite logic output. When the phone line is empty (no call incoming), the pin rests at 5V to indicate a LOGIC 0. When someone is calling, the pin will be pulled down to 0V to indicate a LOGIC 1. Note, the reference 5V for the Arduino input pin is provided internally by the Arduino board by configuring its pin using the "INPUT_PULLUP" assignment. For more details about this assignment please [refer to the Project Coding Section](#project-coding). If the board observes a LOGIC 1 it turns the LED strip ON and otherwise it turns the strip OFF. 

In terms of the phyisical circuit, the control signal is sent through the line called "GPIO Phone-Ringing-Signal Input to Arduino" which is connected to the strip board and to GPIO PIN 2 of GPIO PORT 8 of the axia core in Studio A. To limit the current between the Axia core and the Arduino we include a 470 ohm resistor. Due to the sensitivity of the Arduino pins, to have the input pin read 0V (or a LOGIC 1) properly from GPIO PIN 2, we also must attach the AXIA core's commonon return / ground wire to our circuits ground. To accomplish this we use the wire labelled "GPIO Common Return Wire" to connect from GPIO PIN 7, of GPIO PORT 8, to our circuit's ground rail. For reference documentation regarding the GPIO Setup, please look to chapter 5 of Axia's "iQ Console System Installation & User's Guide" (REFERENCE 2). For more information about this guide please go to the [References and Appreciation section](#references-and-appreciation). To make sure you have the proper GPIO port configured for this project, please refer to the [GPIO Configuration section](#gpio-configuration). 

To operate the LED strip we use three wires, two for providing the necessary power and 5V for the strip, and a third for the PWM control signal which controls the behaviour of the strip. These are labelled "LED Strip Ground Wire," "LED Strip 5V Wire," and LED Strip Control-Signal Wire" respectively. Again, as a precaution, we include a 1000 ohm resistor to limit current going between the Arduino board and the LED strip Control-Signal Wire. 

For reference, below is the list of the components used for the project, including where the parts were sourced from. Note that the JST SM connectors, mentioned in the below table, are used between the strip board and the GPIO port and between the strip board and the LED strip to allow easy removal and maintenace. This allows the circuit module to be easily unistalled and maintained as needed. For more details regarding this please consult the [Physical Setup section](#physical-setup). 

#

##### Component List 

# 

[//]: # (Comment: The extra # below the "Component List" header is to add necessary space between this header and the below table.)

| Component                                   | Source for Purchasing                  |
|:-------------:                              |:-------------:                         |
| Prototyping Strip Board                     | Lee's Electronics                      |
| AWG 6 Wire                                  | Lee's Electornics                      |   
| Arduino Nano V3 from Elegoo                 | http://a.co/cxNeK63                    |
| Neopixel 60 LED Strip                       | http://a.co/cSyl0I4                    |
| 5V 5A Power Supply with female Connector    | http://a.co/5IKmlYb                    |
| 1000uF Electrolytic Capacitors              | http://a.co/6uLZvpv                    |
| Resistor Pack of Multiple Values            | http://a.co/3XxzDq6                    |
| JST SM Connectors                           | http://a.co/7mpo3dt                    |

#

### Project Coding

The only coding in this project is that used to configure the Arduino Nano for controlling the circuit. In this section the general fucntion of the coding will be discussed, but to see the actual written-as-is code, please [refer to the coding document found here](https://github.com/CiTR/Other/blob/master/Projects/Studio%20A%20Phone%20Ringing%20Light/Studio_Light_Code.ino). 

To summarize, using the code, the Arduino's pins are configured as needed for input from the Axia's GPIO port and for output to the LED strip. The only other function of the code is to detail and specify the ON behavior of the LED strip. 

Note that many different LED ON behaviors are achievable depending on the coding employed. If you are curious on possible LED behaviours not listed in my coding then I would read over the coding from the project I used for my main reference (REFERENCE 1), found [here](https://www.hackster.io/whimsy-makerspace/arduino-compatible-nano-neopixel-controller-6f0c4b). And if you need more after that then look over the many Neopixel related projects hosted on Adafruit's website found [here](https://learn.adafruit.com/search?q=neopixel).  

#

### GPIO Configuration

To have the project work, the Axia iQ Core must be configured to relay the "Phone-is-ringing Signal" to the correct GPIO port. Once done, you can connect the GPIO cable from the circuit module to the configured GPIO port for the desired result (assuming the configuration sends the needed signal through GPIO PIN 2). 

To configure the GPIO port correctly please read over the following steps:

1) Go to the iQ6 Gateway Unit in the server room and open its configuration browser using the appropriate IP address.
2) In the configuration browser, under the GPIO Configuration window, give Port #1 on the iQ6 Gateway Unit unique livewire channel number




### Maintenance and Care

#### Accessing the Module
The circuit seen in the picture under the [Project Circuitry section](#project-circuitry) is the main module of this project. The 3 plugs on the outside of the container must be disconnected from their respective lines to access the module properly. **_ALWAYS unplug the power plug first before handling any of the other cables to avoid damaging the project_**. After this you may unplug the other cords in whichever order you like.     

#### Reprogramming the Arduino
To reprogram the Arduino you will need to remove the circuit module from the rest of the system, using the steps outlined in the above paragraph. After that you can use the hole provided on the container to run a USB mini b cable to the Arduino Nano. **_IF POSSIBLE, avoid removing the Nano from the strip board_** as its pins are quite delicate and will break after a few times of the Arduino being removed and reinstalled into its pin receptables. 

#

### Troubleshooting Issues and Their Solutions

| ISSUE                                                                                           | SOLUTION                |
|:-------------:                                                                                  |:-------------:          |
| Computer cannot connect to Arduino to upload a new code configruation. | Make sure that the cord being used isn't charge only. |
| LED strip won't light up after lengthings connection wires between LED strip and circuit module. |  Recall that more wire means more resistance, try reducing the resistor value of the resistor placed between the Arduino Nano and the LED Strip Control-Signal Wire. |   
| Circuit works when the activation signal is looped directly to the circuit's ground rail. Circuit doesn't work when it is instead connected to the GPIO signal from GPIO PIN 2 of the given port. | Make sure that you also attach the ground signal from GPIO PIN 7 of the given GPIO port to the ground of the circuit module. Without this, the arduino pin cannot accurately read logic off the output signal pin. |
| When I plug in the LED strip using the male JST plug it doesn't work | Note that you must feed a signal into the LED strip using the female JST plug as the control signal properly passes through the circuit one way only. Use the the male JST plug side to chain multiple LED strips together  |
| Arduino isn't working even though the PWR LED on it lights up. | Make sure you have the power wire soldered to the Arduino's 5V or VIN pin and that it isn't soldered to the Arduino's RST pin. |

#

### Upgrades and Improvement







### References and Appreciation

1) Arduino Compatible Nano Neopixel Controller   
Made by Team Whimsy Makerspace: Mel Lester Jr  
Website Address: https://www.hackster.io/whimsy-makerspace/arduino-compatible-nano-neopixel-controller-6f0c4b  

2) iQ Console System Installation & User's Guide   
Manual Rev 1.01e -- March 2011 for iQ v1.00 and higher  
Made by Axia, a Telos Alliance Company  

3) Saman Gharib  
Technical Manager - CiTR  
Appreciation mentioned for help given to make this project  

#









