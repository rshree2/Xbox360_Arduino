


#include <XBOXUSB.h>
#include<Servo.h>         // for normal use RC hobby..... 
#include <SoftwareServo.h>
#include<TimerOne.h>



#ifdef dobogusinclude
#include <spi4teensy3.h>///this is for the teensy
#include <SPI.h>
#endif

/*
const byte pololuCommandByte = 170;
const byte smcDeviceNumber = 13;
const byte smcSpeedDataByte3 = 0;
const byte smcFWDbyte = 5;
const byte smcREVbyte = 6;
const byte jrkDeviceNumber = 11;
*/


Servo myservo;
Servo myservo1;

USB Usb;
XBOXUSB Xbox(&Usb);


int initialpos=50;
int initialpos1=0;
int angle,angle1;

long previousmillis=0;    
long ontime =50;



int LeftHatx = analogRead(Xbox.getAnalogHat(LeftHatX));
int LeftHaty = analogRead(Xbox.getAnalogHat(LeftHatY));
int RightHatx = analogRead(Xbox.getAnalogHat(RightHatX));
int RightHaty = analogRead(Xbox.getAnalogHat(RightHatY));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
 Serial.begin(57600);
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif  
  if (Usb.Init() == -1) 
  {
     Serial.print(F("device did not start.....loook into it fool"));
     while (1); //halt
  }
  else
    {
    Serial.print(F("\r\nXBOX USB Library Started"));
    myservo.attach(9);
    myservo1.attach(2);
    myservo.write(initialpos);
    myservo1.write(initialpos1);

     
  

    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() 
{
    int XboxR2; //= Xbox.getButtonPress(R2);
    int XboxL2; //= Xbox.getButtonPress(L2);
    
   
  Usb.Task();
  
  if (Xbox.Xbox360Connected) 
  {
   
   unsigned long currentmillis= millis();
    
   if ( currentmillis-previousmillis >= ontime)
   
   {
   
   previousmillis=currentmillis;
    // XboxR2 = map(XboxR2, 0, 255, 0, -180);
    // XboxL2 = map(XboxL2, 0, 255, 0, 180);
  
    if(Xbox.getButtonClick(START))
    {
      Serial.println(Xbox.getButtonPress(START));
     /* Xbox.setLedMode(ALTERNATING);
      Serial.println(F("Start"));
      Serial.write(pololuCommandByte);
      Serial.write(smcDeviceNumber);
      Serial.write(3);
      Serial.print("written to the device witth the device number");
    */
    }
//****************************************************************************************************    
    
    if(Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2))
     {
    if (Xbox.getButtonPress(L2)) 
      {
      for(XboxL2=initialpos;XboxL2<=100;)
        {
          if (XboxL2==180)
            {
              Serial.println(" \tCant move forward anymore......");
             // break;
            }
           else    
            {
            Serial.print("\tL2: ");
            XboxL2=initialpos+5;
            Serial.println(XboxL2);
            myservo.write(XboxL2);
            initialpos++;
            Xbox.setRumbleOn(Xbox.getButtonPress(L2),0);
         break;
            }
            break;
        }
            
      }
       
        
    if (Xbox.getButtonPress(R2)) 
      { 
      for (XboxR2=initialpos; XboxR2>=50; )
       {
         if (XboxR2==0)
            {
              Serial.println(" \tCant move backward anymore......");
             // break;
            }
         else  
            {
             XboxR2=initialpos-5;
             Serial.print("\tR2: ");
             myservo.write(XboxR2);
             Serial.println(XboxR2);
             initialpos--;
             Xbox.setRumbleOn(0,Xbox.getButtonPress(R2));
             
            break;
            }
          break;  
        }
       
      }
    }
     
     else
     Xbox.setRumbleOff();
     
     
//*******************************************************************************************************
      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500)
       {
      if (Xbox.getAnalogHat(LeftHatX) >7500 || Xbox.getAnalogHat(LeftHatX) <-7500 ) 
       {
        LeftHatx= map(Xbox.getAnalogHat(LeftHatX),-32767, 32768, -180, 180); 
        Serial.print(F("LeftHatX: "));
        Serial.print(LeftHatx);
        Serial.print("\t");
       }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) 
       {
        LeftHaty = map(Xbox.getAnalogHat(LeftHatY),-32767, 32768, -180, 180); 
        Serial.print(F("LeftHatY: "));
        Serial.print(LeftHaty);
        Serial.print("\t");
       }
      if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) 
       {
        RightHatx = map(Xbox.getAnalogHat(RightHatY),-32767, 32767, -180, 180); 
        Serial.print(F("RightHatX: "));
        Serial.print(RightHatx);
        Serial.print("\t");
       }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY)< -7500) 
       {
         RightHaty = map(Xbox.getAnalogHat(RightHatX),-32767, 32768, -180, 180  ); 
         Serial.print(F("RightHatY: "));
         Serial.print(RightHaty);
       }
      Serial.println();
       }
       

      if (Xbox.getButtonClick(UP)) 
       {
        Xbox.setLedOn(LED1);
        Serial.println(F("Up"));
       }
      if (Xbox.getButtonClick(DOWN))
       {
         Xbox.setLedOn(LED4);
         Serial.println(F("Down"));
       }
      if (Xbox.getButtonClick(LEFT))
       {
         Xbox.setLedOn(LED3);
         Serial.println(F("Left"));
       }
      if (Xbox.getButtonClick(RIGHT)) 
       {
        Xbox.setLedOn(LED2);
        Serial.println(F("Right"));
       }
  
      if (Xbox.getButtonClick(BACK))
       {
         Xbox.setLedBlink(ALL);
         Serial.println(F("Back"));
       }
        
     if (Xbox.getButtonClick(R3))
        Serial.println(F("R3"));
        
        
        
//*********************************CODED**************************************************
     if (Xbox.getButtonClick(L1)) //Forward direction
     {
       for( angle1=initialpos1; angle1<=180;)
       {      
        if (initialpos1==180)
          {
            Serial.println(F("Cant move forward--\n"));
          }
        else
          { 
           angle1=angle1+10;
           myservo1.write(angle1);
           initialpos1=angle1;
           Serial.println(F("L1"));
           break;
          }
          break;
       }
      
     }
     
      
     if (Xbox.getButtonClick(R1))// Reverse direction
     {   
       for(angle1=initialpos1; angle1>=0;)
          {
        if (initialpos1==0)
           {
            Serial.println("Cant move bavkward-\n");
           }
      else 
           {    
        angle1=angle1-10;
        myservo1.write(angle1);
        initialpos1=angle1;
        Serial.println(F("R1"));
        break;
           }
          break; 
         }
     // delay(1);
     } 
     
//***********************************************************************************     
     if (Xbox.getButtonClick(XBOX)) 
       {
        Xbox.setLedMode(ROTATING);
        Serial.println(F("Xbox"));
       }

     if (Xbox.getButtonClick(A))
      Serial.println(F("A"));
      
     if (Xbox.getButtonClick(B))
      Serial.println(F("B"));
      
     if (Xbox.getButtonClick(X))
      Serial.println(F("X"));
      
     if (Xbox.getButtonClick(Y))
      Serial.println(F("Y"));
 
    }
   
  }
}


/*

void setPwmFrequency(int pin, int divisor) 
{
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) 
  {
    switch(divisor) 
    {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      
      default: return;
    }
  }


if(pin == 5 || pin == 6)
{
      TCCR0B = TCCR0B & 0b11111000 | mode;
}
}
*/
      
class Timer
{
 
 public: 
  long previousMillis;
  long Milliseconds=50;
  
 

};


  
