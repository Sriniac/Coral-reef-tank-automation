
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
#include <hd44780.h>            // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
hd44780_I2Cexp lcd;  // i2c expander i/o class header

RtcDS1307<TwoWire> Rtc(Wire);
const int red =13 ; 
const int green =15  ; 
const int blue = 0 ; 
const int sblue = 3 ; 
const int white =  14; 
const int one =  12; 
const int two =  1; 
const int three = 2 ;
const int four = 10 ;
const int five = 9 ;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
/* for normal hardware wire use above */


void setup () 
{int status;

 // initialize LCD with number of columns and rows: 
  // hd44780 returns a status from begin() that can be used
  // to determine if initalization failed.
  // the actual status codes are defined in <hd44780.h>
  // See the values RV_XXXX
  //
  // looking at the return status from begin() is optional
  // it is being done here to provide feedback should there be an issue
  //
  // note:
  //  begin() will automatically turn on the backlight
  //
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if(status) // non zero status means it was unsuccesful
  {
    status = -status; // convert negative status value to positive number

    // begin() failed so blink error code using the onboard LED if possible
    hd44780::fatalError(status); // does not return
  }

  // initalization was successful, the backlight should be on now

  // Print a message to the LCD

    Serial.begin(57600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    //--------RTC SETUP ------------
    // if you are using ESP-01 then uncomment the line below to reset the pins to
    // the available pins for SDA, SCL
   Wire.begin(4,5); // due to limited pins, use pin 0 and 2 for SDA, SCL
    
    
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Cuases:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");

        // following line sets the RTC to the date & time this sketch was compiled
        // it will also reset the valid flag internally unless the Rtc device is
        // having an issue

        Rtc.SetDateTime(compiled);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    // never assume the Rtc was last configured by you, so
Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low); 
}

void loop () 
{
   lcd.init();                      // initialize the lcd 
  lcd.backlight();
 
    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Cuases:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    Serial.println();



	// you may also get the temperature as a float and print it
    // Serial.print(temp.AsFloatDegC());
  Serial.println("C");

    delay(1000); // ten seconds
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
           PSTR("%02u"),
         
            dt.Hour()
           // dt.Minute()
             );
    Serial.print(datestring);


 
      if((strcmp(datestring,"06") == false )||(strcmp(datestring,"23") == false ))
     {    Serial.begin(57600);   
  lcd.setCursor(1,1);
lcd.print("0,0,0,0,0");
  analogWrite(red, 512);
  analogWrite(green, 512); 
  analogWrite(blue, 512);
  analogWrite(sblue, 512);
   analogWrite(white, 512);
  
    } 
    if((strcmp(datestring,"07") == false )||(strcmp(datestring,"08") == false )||(strcmp(datestring,"10") == false )||(strcmp(datestring,"09") == false ))
     {

Serial.print("8,8,30,10,15");
    analogWrite(red, 512);
  analogWrite(green, 512); 
  analogWrite(blue, 512);
  analogWrite(sblue, 512);
   analogWrite(white, 512);
 
    } 
  if((strcmp(datestring,"11") == false )||(strcmp(datestring,"12") == false )||(strcmp(datestring,"13") == false )||(strcmp(datestring,"14") == false )||(strcmp(datestring,"15") == false )||(strcmp(datestring,"16") == false ))
     {

Serial.print("15,15,80,20,35");
  analogWrite(red, 512);
  analogWrite(green, 512); 
  analogWrite(blue, 512);
  analogWrite(sblue, 512);
   analogWrite(white, 512);
 
    } 
    if((strcmp(datestring,"17") == false )||(strcmp(datestring,"18") == false ))
     {

Serial.print("8,8,50,10,25");
   analogWrite(red, 512);
  analogWrite(green, 512); 
  analogWrite(blue, 512);
  analogWrite(sblue, 512);
   analogWrite(white, 512);
 
    } 
    if((strcmp(datestring,"19") == false )||(strcmp(datestring,"20") == false )||(strcmp(datestring,"21") == false )||(strcmp(datestring,"22") == false ))
     {

Serial.print("0,3,5,10,3");
  analogWrite(red, 512);
  analogWrite(green, 512); 
  analogWrite(blue, 512);
  analogWrite(sblue, 512);
   analogWrite(white, 512);
 } 
}



