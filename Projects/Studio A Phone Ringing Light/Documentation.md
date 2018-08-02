# Studio A Phone Light Project Documentation

### Project General Summary

[//]: # (Comment: &nbsp featured below is for spacing purposes)

&nbsp;&nbsp;&nbsp;&nbsp; This project is a light for studio A which turns on whenever a person calls into the studio. It was made by the current technical coordinator at the time, Jarod Ben-Oliel, per the request of CiTR programmers for a more noticeable phone light in the studio. Before this project, the only available light wasn't very noticeable, meaning programmers would miss call-ins. The project is a simple circuit composed of an Adafruit Neopixel LED Strip which is controlled by an Arudino Nano V3 controller. The controller will turn the LED strip ON/OFF depending if anyone is calling into Studio A.

&nbsp;&nbsp;&nbsp;&nbsp; In this file, all project related information can be found. This includes the circuit diagram, links to all reference websites and documents, a recorded list of encountered issues and their found solutions, and more. Please refer to the table below to quickly navigate to your desired section of documention. 

    
## Table of Contents

1.  [Project General Summary](###project-general-summary)


2. [Project Circuitry](###project-circuitry)
    * [Component List](#####component-list) 



3. [Project Coding](###project-coding)

4. [Physical Setup](###physical-setup) 

5. [Encountered Issues with Solutions](###encountered-issues-with-solutions) 


6. [References and Appreciation](###references-and-appreciations) 




### Project Circuitry

![alt text](https://github.com/CiTR/Other/blob/master/Projects/Studio%20A%20Phone%20Ringing%20Light/Phone_Light_Project_Circuit_Diagram.png "Project Circuit Diagram")

Featured above is the project circuit diagram which was created using Fritzing.

Starting from the top left we see terminal for our plugin dedicated 5V power supply, it feeds the ground and 5V rails of the entire circuit. To mitigate possible power surges, a 1000uF electrolytic capacitor is installed across our 5V rails.  

Moving down, we see the Arduino Nano. Its two jobs are to monitor the control signal and to turn ON/OFF the LED strip as required, depending on the state of the control signal. 

The control signal is a digital signal sent from an Axia iQ Core GPIO port using an open-collector output pin, meaning this output functions as an opposite logic output. When the phone line is empty (no call incoming), the pin rests at 5V to indicate a LOGIC 0. When someone is calling, the pin will be pulled down to 0V to indicate a LOGIC 1. Note, the reference 5V for the Arduino input pin is provided internally by the Arduino board by configuring its pin using the "INPUT_PULLUP" assignment. For more details about this assignment please [refer to the Project Coding Section](##project-coding). If the board observes a LOGIC 1 it turns the LED strip ON and otherwise it turns the strip OFF. 

In terms of the phyisical circuit, the control signal is sent through the line called "GPIO Phone-Ringing-Signal Input to Arduino." To limit the current between the Axia core and the Arduino we include a 470 ohm resistor. Due to the sensitivity of the Arduino pins, to have the input pin to read 0V (or a LOGIC 1) from the GPIO pin properly, we also must attach the AXIA core's commonon return / ground wire to our circuits ground. For reference we are using one GPIO port where GPIO pin 2 is for the control signal and GPIO pin 7 is for the common return line.

To operate the LED strip we use three wires, two for providing the necessary power and 5V for the strip, and a third for the PWM control signal which controls the behaviour of the strip. These are labelled "LED Strip Ground Wire," "LED Strip 5V Wire," and LED Strip Control-Signal Wire" respectively. Again, as a precaution, we include a 1000 ohm resistor to limit current going between the Arduino board and the LED strip Control-Signal Wire. 

For reference, below is the list of the components used for the project, including where the parts were sourced from. Note that the JST SM connectors, mentioned in the below table, are used between the strip board and the GPIO port and between the strip board and the LED strip to allow easy removal and maintenace. 


##### Component List 
# 

[//]: # (Comment: The extra # below the "Component List" header is to add necessary space between this header and the below table.)

| Component                                   | Source for Purchasing                  |
|:-------------:                              |:-------------:                         |
| Prototyping Strip Board                     | Lee's Electronics                      |
| AWG 6 Wire                                  | Lee's Electornics                      |   
| Arduino Nano V3 from Elegoo                 | Amazon.ca - Link 1                     |
| Neopixel 60 LED Strip                       | Amazon.ca - Link 2                     |
| 5V 5A Power Supply with female Connector    | Amazon.ca - Link 3                     |
| 1000uF Electrolytic Capacitors              | Amazon.ca - Link 4                     |
| Resistor Pack of Multiple Values            | Amazon.ca - Link 5                     |
| JST SM Connectors                           | Amazon.ca - Link 6                    |

**NOTE:** Links mentioned in the above table are listed below to avoid messy table formatting:

##### Component Purchase Links
+ Link 1 - https://www.amazon.ca/Arduino-ELEGOO-ATmega328P-Compatible-Without/dp/B071NMD14Y/ref=pd_cp_107_1?pf_rd_m=A3DWYIK6Y9EEQB&pf_rd_p=5749673626753893530&pf_rd_r=FJ9947MQKW51RNMMHDAW&pd_rd_wg=jlC5T&pf_rd_s=desktop-dp-sims&pf_rd_t=40701&pd_rd_w=QLDJ3&pf_rd_i=desktop-dp-sims&pd_rd_r=4db2a773-78ce-11e8-8a2a-83c3f18333a3&pd_rd_i=B071NMD14Y&psc=1&refRID=FJ9947MQKW51RNMMHDAW

+ Link 2 - https://www.amazon.ca/NooElec-Addressable-Waterproof-Connectors-Pre-Soldered/dp/B00JR0MJIU/ref=sr_1_fkmr0_4?ie=UTF8&qid=1530123814&sr=8-4-fkmr0&keywords=neopixel+140

+ Link 3 - https://www.amazon.ca/ALITOVE-Converter-5-5x2-1mm-100V-240V-Security/dp/B078RT3ZPS/ref=sr_1_7?s=electronics&ie=UTF8&qid=1529971198&sr=1-7&keywords=5V%2Bpower%2Bsupply%2B5.5x2.1mm%2BPlug&th=1

+ Link 4 - https://www.amazon.ca/Nichicon-Electrolytic-Capacitor-1000uF-10X20mm/dp/B00J0CAWRA/ref=sr_1_2?s=industrial&ie=UTF8&qid=1529969521&sr=1-2&keywords=1000uF+capacitor&dpID=31-u1fMJGNL&preST=_SX342_QL70_&dpSrc=srch 

+ Link 5 - https://www.amazon.ca/ELEGOO-Values-Resistor-Assortment-Ohm-1M/dp/B071HJWJZB/ref=sr_1_4?s=industrial&ie=UTF8&qid=1529969597&sr=1-4&keywords=resistors&dpID=51XXj07ePIL&preST=_SX342_QL70_&dpSrc=srch
 
+ Link 6 - https://www.amazon.ca/Electop-Pairs-Female-Connector-Cable/dp/B01MQ011XO/ref=sr_1_fkmr0_1?ie=UTF8&qid=1529969808&sr=8-1-fkmr0&keywords=3-pin+JST+SM+Plug+%2B+Receptacle+Cable+Set




### Project Coding

The only coding in this project is that used to configure the Arduino Nano for controlling the circuit. In this section the general fucntion of the coding will be discussed, but to see the actual written-as-is code, please [refer to the coding document found here](https://github.com/CiTR/Other/blob/master/Projects/Studio%20A%20Phone%20Ringing%20Light/Studio_Light_Code.ino). 

Using the code, the Arduino's pins are configured as needed for input from the Axia's GPIO port and for output to the LED strip. The only other function of the code is to detail and specify the ON behavior of the LED strip. Note that many different LED behaviors are achievable depending on the coding employed. If you are curious on the possibilities I would check out the site for Neopixels online, or refer to the coding document included in this project's directory. 


### References and Appreciation











