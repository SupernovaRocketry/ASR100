#include<SoftwareSerial.h>
 #include<EEPROM.h>

 SoftwareSerial bmpSerial(3, 4);
 void setup() {
 bmpSerial.begin(9600);
 }

 void loop() {
 for(int addr=0; addr<EEPROM.length()-1; addr+=2){
 bmpSerial.print(EEPROM.read(addr));
 bmpSerial.print(',');
 bmpSerial.println(EEPROM.read(addr+1));
 delay(100);
}
 delay(5000);
{
if(Serial.available()){
 Serial.print((char) Serial.read());
delay(10);
 }
 }
 }
