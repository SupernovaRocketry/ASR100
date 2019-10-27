#include <SPI.h>

#include <Adafruit_BMP085.h>

#include <SD.h>


Adafruit_BMP085 bmp;

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  if (!bmp.begin()) {
  digitalWrite(7, HIGH);
  while (1) {}
  }
  else{
  digitalWrite(7, LOW);   
  }
  if (!SD.begin(2)) {
  digitalWrite(6, HIGH);
  while (1) {}
  }
  else{
  digitalWrite(6, LOW);   
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // Abre o arquivo arquivo.txt do cartao SD
    int aux =0;
    File dataFile = SD.open("arquivo.txt", FILE_WRITE);
    // Grava os dados no arquivo
    if (dataFile) 
    {
      dataFile.print("Altitude : ");
      dataFile.println(bmp.readAltitude()); //pegar a altitude
      dataFile.close();
      delay(100);
    }  
    else 
    {
      // Mensagem de erro caso ocorra algum problema
      // na abertura do arquivo
    }
    aux = aux +1;
    while(aux < 200) ; 
}
