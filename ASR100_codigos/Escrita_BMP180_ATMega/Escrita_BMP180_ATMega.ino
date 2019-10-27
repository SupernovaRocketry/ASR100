// Any Arduino pins labeled:  SDA  SCL
// Uno, Redboard, Pro:        A4   A5

#include <SFE_BMP180.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>

SFE_BMP180 pressure;

File myFile;

Servo motor;

unsigned int i = 0;
unsigned int t0 = 0;
unsigned int t = 500; // Tempo de acionamento do servo
//float alt[1000]; // Talvez não dê pra usar por questão de espaço
unsigned int temp = 0;
double baseline; // baseline pressure

// Função getPressure
double getPressure()
{
  char status;
  double T, P, p0, a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

void setup()
{
  pinMode(3, OUTPUT); // LED simulando motor

// Inicialização do servo motor
  motor.attach(9);  // Servo no pino 9
  motor.write(0); // Depende do grau que o motor vai começar

// Inicialização do cartão SD
  myFile = SD.open("ARQUIVO.txt", FILE_WRITE);
  
// Inicialização do BMP180
  if (pressure.begin())
    myFile.println("Inicialização do BMP180 concluída!");
  else
  {
    myFile.println("Falha na inicialização do BMP180\n\n");
    while(1);
  }

  // Define a pressão de base:
  baseline = getPressure();
}

void loop()
{
  double a, P;
  
  // Get a new pressure reading:
  P = getPressure();

  // Show the relative altitude difference between
  // the new reading and the baseline reading:

  a = pressure.altitude(P,baseline);
//  alt[i] = a;

  if(a > 5.0 && temp == 0)
  {
    temp = 1;
    t0 = millis();
  }
  
  if(millis() - t0 >= t && temp == 1)
  {
    motor.write(180); // Depende do grau que o motor vai ficar
    digitalWrite(3, HIGH);  // Acende o LED
  }
  
//  else if(alt[i] < alt[i-1] && alt[i-1] < alt[i-2] && temp == 0)  // NÃO SEI SE VAI DAR PRA
//  {                                                               // USAR PELO TAMANHO
//    motor.write(180); // Depende do grau que o motor vai ficar    // DE alt[i]
//  }

  if(myFile)
  {
    myFile.print("Dado ");
    myFile.print(i);
    myFile.print(": ");
    myFile.println(a);
    if(i == 1000)
    {
      myFile.close();
      while(1); // Pausa o código
    }
  }

  i = i + 1;
  
  delay(100);
}
