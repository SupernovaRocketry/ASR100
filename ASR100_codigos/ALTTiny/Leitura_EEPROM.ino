#include <EEPROM.h>
#include <tinyBMP085.h>
#include <TinyWireM.h>
#include <SoftwareSerial.h>

tinyBMP085 bmp;
SoftwareSerial SSerial = SoftwareSerial(4,3);

int addr = 0;

void setup()
{
  bmp.begin();  
  SSerial.begin(19200);
}

void loop()
{

  uint8_t value = EEPROM.read(addr);
  uint8_t value1 = EEPROM.read(addr+1);

  SSerial.print(addr);
  SSerial.print(" ");
  SSerial.print(value, DEC);
  SSerial.print(value1, DEC);
  SSerial.println();

  addr = addr + 2;
  if(addr == EEPROM.length()){
    addr=0;
  }
}
