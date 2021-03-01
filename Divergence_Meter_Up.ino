/**
 * @file        max7219_7segment_date_time_temp.c
 *
 * @brief       view DATE/TIME/TEMPERATURE using an 8-digit 
 *              7-Segment display
 *
 * @history     Feb 6th, 2017
 *
 * @author      Allan Schwartz <allans@CodeValue.net>
 *              Michael Diamond <m.diamond.il@gmail.com>
 *
 * @notes       The following Arduino Pins are attached:
 *
 *              name    Arduino   7 Segment display
 *              -----   ----      -----
 *                      +5V       VCC
 *                      GND       GND
 *              DIN     D11/MOSI  DIN
 *              CS      D10/SS    CS
 *              CLK     D13/SCK   CLK
 *
 *              name    Arduino   RTC module
 *              -----   ----      -----
 *                      nc        32K
 *                      nc        SQW
 *              SCL     SCL/A5    SCL
 *              SDA     SDA/A4    SDA
 *                      3v3       VCC
 *                      GND       GND
 */

#include <DS3231.h>           // import library from rinkydink.com

// define pins attached to MAX7219 (and also see notes above)
#define MAX7219_DIN           11
#define MAX7219_CS            10
#define MAX7219_CLK           12
const int buzzerPin = 9;
// enumerate the MAX7219 registers
// See MAX7219 Datasheet, Table 2, page 7
enum {  MAX7219_REG_DECODE    = 0x09,  
        MAX7219_REG_INTENSITY = 0x0A,
        MAX7219_REG_SCANLIMIT = 0x0B,
        MAX7219_REG_SHUTDOWN  = 0x0C,
        MAX7219_REG_DISPTEST  = 0x0F };

// enumerate the SHUTDOWN modes
// See MAX7219 Datasheet, Table 3, page 7
enum  { OFF = 0,  
        ON  = 1 };

const byte DP = 0b10000000;  
const byte C  = 0b01001110;  
const byte F  = 0b01000111;


// create an instance of the DS3231 called 'rtc', 
// and specify the hardware interface PINS
DS3231 rtc(SDA, SCL);


// ... setup code here, to run once
void setup()  
{
    pinMode(buzzerPin, OUTPUT);
    // initialize the serial port:
    Serial.begin(115200);           // initialize serial communication
    Serial.println("max7219_7segment_date_time_temp");

    // define type of pin
    pinMode(MAX7219_DIN, OUTPUT);   // serial data-in
    pinMode(MAX7219_CS, OUTPUT);    // chip-select, active low    
    pinMode(MAX7219_CLK, OUTPUT);   // serial clock
    digitalWrite(MAX7219_CS, HIGH);

    resetDisplay();                 // reset the MAX2719 display

    rtc.begin();                    // init. the DS3231 RTC interface

    // Uncomment the following lines to set the RTC
    //rtc.setDOW(WEDNESDAY);        // Set Day-of-Week to WEDNESDAY
    rtc.setTime(16, 20, 0);       // Set the time to 4:20pm
    //rtc.setDate(8, 2, 2017);      // Set the date to 8-Feb-2017
}


void loop()  
{
      int i0 = random(2);
      int i1 = random(10);
      int i2 = random(10);
      int i3 = random(10);
      int i4 = random(10);
      int i5 = random(10);
      int i6 = random(10);
      int i7 = random(101);
      Serial.println(i7);
      if(i7 > 9)
      {
          i0 = 0;
      }
      else
      {
          i0 = 1;
          tone(buzzerPin, 7000, 500);   
      }
      String firstNumb = String(i0);
      String first = String(i0) + String(i1) + String(i2) + String(i3) + String(i4) + String(i5) + String(i6);
      //first = "0000001";
      Serial.println(first);
      displayString(first);
      if(first == "0000001")
      {
          
          displayString("12345678");
          delay(3000);
      }
      else
      {
          
          delay(500);
      }
//    String str;                     // scratch or working string
//
//    // ... display Date, dd.mm.yyyy
//    // read the date as a string from the RTC
//    str = rtc.getDateStr(FORMAT_LONG);
//    Serial.println(str);            // debug
//    displayDate(str);               // display on the 7-segment 
//    delay(6000);
//
//    // ... display Time, hh-mm-ss
//    for ( int i = 0; i < 6; i++ ) {
//        // read the time as a string from the RTC
//        str = rtc.getTimeStr(FORMAT_LONG);
//        Serial.println(str);        // debug
//        displayTime(str);           // display on the 7-segment 
//        delay(1000);
//    }
//
//    // ... display Temperature in Celsius, xx.xx C
//    // read the temperature, as a float, from the RTC
//    float t = rtc.getTemp();
//    str = String(t, 2);             // format that value
//    Serial.println(str);            // debug
//    displayTemp(str, C);            // display on the 7-segment
//    delay(3000);
//
//    // ... display Temperature in Fahrenheit, xx.xx F
//    t = t * 1.8 + 32.0;             // convert the value to Fahrenheit
//    str = String(t, 1);             // format that value
//    Serial.println(str);            // debug
//    displayTemp(str, F);            // display on the 7-segment
//    delay(3000);
}


// ... write a value into a max7219 register 
// See MAX7219 Datasheet, Table 1, page 6
void set_register(byte reg, byte value)  
{
    digitalWrite(MAX7219_CS, LOW);
    shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, reg);
    shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, value);
    digitalWrite(MAX7219_CS, HIGH);
}


// ... reset the max7219 chip
void resetDisplay()  
{
    set_register(MAX7219_REG_SHUTDOWN, OFF);   // turn off display
    set_register(MAX7219_REG_DISPTEST, OFF);   // turn off test mode
    set_register(MAX7219_REG_INTENSITY, 0x0D); // display intensity
}


// ... display the DATE on the 7-segment display
void displayDate(String dateString)  
{
    set_register(MAX7219_REG_SHUTDOWN, OFF);  // turn off display
    set_register(MAX7219_REG_SCANLIMIT, 7);   // scan limit 8 digits
    set_register(MAX7219_REG_DECODE, 0b11111111); // decode all digits

    set_register(1, dateString.charAt(9));
    set_register(2, dateString.charAt(8));
    set_register(3, dateString.charAt(7));
    set_register(4, dateString.charAt(6));
    set_register(5, dateString.charAt(4) | DP); // plus decimal point
    set_register(6, dateString.charAt(3));
    set_register(7, dateString.charAt(1) | DP);
    set_register(8, dateString.charAt(0));

    set_register(MAX7219_REG_SHUTDOWN, ON);   // Turn on display
}


void displayString(String dateString)  
{
    set_register(MAX7219_REG_SHUTDOWN, OFF);  // turn off display
    set_register(MAX7219_REG_SCANLIMIT, 7);   // scan limit 8 digits
    set_register(MAX7219_REG_DECODE, 0b11111111); // decode all digits

    set_register(1, dateString.charAt(7));
    set_register(2, dateString.charAt(6));
    set_register(3, dateString.charAt(5));
    set_register(4, dateString.charAt(4));
    set_register(5, dateString.charAt(3)); // plus decimal point
    set_register(6, dateString.charAt(2));
    set_register(7, dateString.charAt(1));
    set_register(8, dateString.charAt(0) | DP);

    set_register(MAX7219_REG_SHUTDOWN, ON);   // Turn on display
}


// ... display the TIME on the 7-segment display
void displayTime(String timeString)  
{
    set_register(MAX7219_REG_SHUTDOWN, OFF);  // turn off display
    set_register(MAX7219_REG_SCANLIMIT, 7);   // scan limit 8 digits
    set_register(MAX7219_REG_DECODE, 0b11111111); // decode all digits

    set_register(1, timeString.charAt(7));
    set_register(2, timeString.charAt(6));
    set_register(3, timeString.charAt(5));
    set_register(4, timeString.charAt(4));
    set_register(5, timeString.charAt(3));
    set_register(6, timeString.charAt(2));
    set_register(7, timeString.charAt(1));
    set_register(8, timeString.charAt(0));

    set_register(MAX7219_REG_SHUTDOWN, ON);   // Turn on display
}


// ... display the TEMP on the 7-segment display
void displayTemp(String tempString, char C_or_F )  
{
    set_register(MAX7219_REG_SHUTDOWN, OFF);  // turn off display
    set_register(MAX7219_REG_SCANLIMIT, 5);   // scan limit 6 digits
    set_register(MAX7219_REG_DECODE, 0b00111100); // decode 4 digits

    set_register(1, C_or_F);
    set_register(2, 0);                       // blank
    set_register(3, tempString.charAt(4));
    set_register(4, tempString.charAt(3));
    set_register(5, tempString.charAt(1) | DP); // plus decimal point
    set_register(6, tempString.charAt(0));

    set_register(MAX7219_REG_SHUTDOWN, ON);   // Turn On display
}
