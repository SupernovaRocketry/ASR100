#include <EEPROM.h>
#include <tinyBMP085.h>
#include <TinyWireM.h>

tinyBMP085 bmp;

int addr = 0;

void setup()
{
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  delay(90000);
  //LIMPANDO A EEPROM
  for (int i = 0 ; i < EEPROM.length() ; i++)
  {    
    EEPROM.write(i, 0);
  }
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  bmp.begin(); 
   
}

void loop()
{
  uint8_t altSTDdm = bmp.readAltitudeSTDdm()/100;
  uint8_t altSTDdm1 = bmp.readAltitudeSTDdm()%100;
  EEPROM.write(addr, altSTDdm); 
  EEPROM.write(addr+1, altSTDdm1);
    
  delay(100);

  addr = addr + 2;
  if (addr == EEPROM.length()){
  while(1);
  }  
}

