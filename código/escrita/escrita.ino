//========================== Bibliotecas
#include <EEPROM.h>
#include "tinyBMP085.h"
#include "TinyWireM.h"
//========================== Variaveis
tinyBMP085 brmt;

float base    =  0;
bool  iniciar = false; 

//========================== Ativar buzzer
void buzzer(int vezes){
  for(int i=0;i<vezes;i++){
    digitalWrite(4,HIGH);
    delay(400);
    digitalWrite(4,LOW);
    delay(400);
  }
}
//========================== Setup
void setup(){ 
//========================== Declaração de pinos: 1 buzzer, 2 bota                       o
 
  pinMode(4,OUTPUT);
  
  delay(2000);
  while(!brmt.begin()){
    buzzer(5);
  }

//========================== Calculo da média da altitude inicial
  
  for(int i=0;i<20;i++){
    base+= brmt.readAltitude();
  }
   base=base/20;
   buzzer(2);
}

void loop(){ 
  int addr = 0;
  float comp1;
  float comp2=0;

  while(!iniciar){
    digitalWrite(4  , HIGH);
    delay(60000);
    digitalWrite(4, LOW);
    iniciar = true;
    delay(2000);
  }
//========================== Testa a altitude
  //if(brmt.readAltitude()-base>20){
//========================== Compara cada valor medido para salvar o apice
    for(int i =0;addr<(EEPROM.length())-2;i++){
      comp1=(brmt.readAltitude())-base;
      if(comp1>comp2){
        comp2=comp1;      
      }
//========================== A cada 60 ciclos(ajustavel) salva se um valor porem, salva-se o apice independentemente
      if(i%5==0){
        EEPROM.write(addr,(int)comp1); 
        EEPROM.write(addr+1,((int)((comp1)*100))%100);
        addr+=2;
      }
    }
//========================== Salvamento do apice contido na variavel comp2 no final do lançamento

    EEPROM.write(EEPROM.length()-2, (int)comp2);
    EEPROM.write(EEPROM.length()-1, ((int)(comp2*100))%100);
//========================== Loop infinito final do buzzer
    while(1){
      buzzer(2);
    }
//}
}
