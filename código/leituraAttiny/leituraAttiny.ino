#include<SoftwareSerial.h>
#include<EEPROM.h>

 SoftwareSerial bmpSerial(3, 4);
 void setup() {
 bmpSerial.begin(9600);
 }

 void loop() {
 bmpSerial.println("DUMP START");
 for(int addr=0; addr<EEPROM.length()-1; addr+=2){
 bmpSerial.print(EEPROM.read(addr));
 bmpSerial.print(',');
 bmpSerial.println(EEPROM.read(addr+1));
 delay(100);
}
 bmpSerial.println("DUMP END");
 delay(5000);
{
if(bmpSerial.available()){
 bmpSerial.print((char) bmpSerial.read());
delay(10);
 }
 }
 }
