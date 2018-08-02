#include <Adafruit_NeoPixel.h>

/*
The structure of this code was derived from code found on
the project website found below
https://www.hackster.io/whimsy-makerspace/arduino-compatible-nano-neopixel-controller-6f0c4b 

For more useful light generating functions check out the code used in the above reference
*/

///////////////////////////////////////////////////////////////////////////
////////////////////////////GLOBAL VARIABLES///////////////////////////////
///////////////////////////////////////////////////////////////////////////
int dataPin = 12;  // used to set which Arduino PWM data pin is used to control LED strip colours, currently to pin D6 
int pixels = 60;  // number of Neopixels in LED strip
int sensorpin = 3; // used to set the Arduino Sensing pin for receiving Axia Core Phone-Ringing Signal, currently set to pin D3
int input_pin_value; //inititiate variable for assigning and storing the read value from the input pin 
int SOUGHT_LOGIC = LOW; //change as needed to configure what type of logic is used to activate the LED strip


///////////////////////////////////////////////////////////////////////////
////////////////////////////LED STRIP SETUP////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//Lines below are used to configure interface between arduino and LED strip,
//be very careful about changing this.

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixels, dataPin, NEO_GRB + NEO_KHZ800);  //DO NOT CHANGE THIS LINE if at all possible, already correctly configured.


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.



///////////////////////////////////////////////////////////////////////////
////////////////////////////////SETUP BLOCK////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//Used for initializing input pin and setting the initial conditions for the LED strip.

void setup() 
{
    pinMode(sensorpin, INPUT_PULLUP); //initiate input pin used to collect output signal from AXIA core. 
                                      //MAKE SURE to use INPUT_PULLUP to ensure that the pullup resistor is activated to invert logic behaviour (0 = HIGH / 5V, 1 = LOW / 0V)
    strip.begin(); //required at the start for the LED strip. 
    strip.show(); // Initialize all pixels to 'off' 
}




///////////////////////////////////////////////////////////////////////////
////////////////////////////////LOOP BLOCK/////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//Loop block runs forever
//First reads value from input pin and then calls functions depending on the read value.

void loop() 
{
    input_pin_value = digitalRead(sensorpin); //read the input pin and assign value to 'input_pin_value'
    if(input_pin_value == SOUGHT_LOGIC) //check if we have the right switching condition, in other words, is the phone ringing
    {                                   //if so go to main function to turn on lights, otherwise turn lights off
        custom_rainbow_wipe(10);  //Edit the value in parantheses to change the scrolling speed of the lights
    }
    else
    {
        colorWipe(strip.Color(0, 0, 0), 10); //turn off LED strip
    }
}





///////////////////////////////////////////////////////////////////////////
///////////////////////////FUNCTION DEFINTIONS/////////////////////////////
///////////////////////////////////////////////////////////////////////////

//Below are all used function definitions



////////////////////////////////////////////////////////
//CUSTOM RAINBOW WIPE
////////////////////////////////////////////////////////

//Main function of this program
//Used to have a scrolling rainbow fill the strip one LED at time, after which it does the same when turning them off
//'wait' is the chosen value used to set the speed in which pixels turn on and off

void custom_rainbow_wipe(uint8_t wait) 
{
    for(uint16_t j = 5000; j>0; j=j-50) //we increment j here in this for-loop to make sure that every time we turn on the 
    {                                   //lights, the rainbow shifts a bit to give a spinning impression as we repeat the loop
        input_pin_value = digitalRead(sensorpin); //actively check the input pin value, if the phone stops rining we want to stop the light without having to proceed through the entire function loop first
        if(input_pin_value == SOUGHT_LOGIC)  //check phone ringing input value, proceed to turn on lights with proper signal received
        {   
            for(uint16_t i=0; i<strip.numPixels(); i++) //'i' is used to increment through all the pixels we want to turn on
            {
                strip.setPixelColor(i, Wheel(j));   //This function sets the color value 'c' of a pixel at position 'i'                                                    
                                                    //Both 'i' and 'c' are numbers of course, where c = Wheel(j)
                strip.show(); //This function pushes all set pixel values to the strip
                delay(wait);  //Delay is as it should be, it delays for the given value 'wait'
                j = j+8; //The number being added to j is what causes colours to change while scrolling through the strip in one pass,
                         //The higher the number being added to j, the more times you will scroll through the rainbow in one pass of the strip
            }            //If j=j+0, then the strip will be the same colour throughout on each pass
        }
        else  //if at any time the phone stops ringing then we leave the loop
        {
            return;
        }
        
        colorWipe(strip.Color(0, 0, 0), wait);  //for visual purposes, to make it more noticeable, we turn all the LEDs beforehand and then turn all them off
    }  
}



////////////////////////////////////////////////////////
//COLORWIPE
////////////////////////////////////////////////////////

//Function sends one colour value to every pixel and turns them on, one-by-one
//By setting the sent colour value to 0 we use this function to turn off the led strip

// Fill the dots one after the other with a color 'c'
void colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) //increment through each pixel
  {
      strip.setPixelColor(i, c); //set the colour value 'c' of the 'i' position pixel  
      strip.show(); //push the set colours to the strip to turn on the lights
      delay(wait);  //wait
  }
}



////////////////////////////////////////////////////////
//WHEEL
////////////////////////////////////////////////////////

//This function is passed an index which is used to generate and pass back a color value
//By continually passing changing index, 'j' in this case which then becomes 'WheelPos', 
//we can scroll through different colours while scrolling on the LED's in one pass of the strip

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
    WheelPos = 255 - WheelPos;
    
    if(WheelPos < 85) 
    {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } 
    else if(WheelPos < 170) 
    {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } 
    else 
    {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

