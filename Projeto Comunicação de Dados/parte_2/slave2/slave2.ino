#include <SoftwareSerial.h> 
SoftwareSerial rsSerial (2,3); // RX, TX nodemcu
const int DE_RE = 4; 
const int atuador =  5; 
void setup() 
{ 

  Serial.begin(9600);
  rsSerial.begin(9600);
  pinMode(DE_RE, OUTPUT);
  pinMode(atuador, OUTPUT);
  digitalWrite(DE_RE, LOW);//RS485 como receptor
  digitalWrite(atuador, LOW);
} 
 
void loop() 
{ 
    if(rsSerial.available()){
    if(rsSerial.read()=='2'){                     // se receber seu endereço inicia o programa
    delay(10);
     char funcao=rsSerial.read();                 // lê o caracter de função
      if(funcao=='A'){
         if(digitalRead(atuador)==LOW){
           digitalWrite(atuador,HIGH);
           }
         else{
           digitalWrite(atuador,LOW);
         } 
          digitalWrite(DE_RE, HIGH);              //rs485 como transmisor 
          rsSerial.println("i");                  //inicio da transmissão  
          delay(8);
          rsSerial.flush(); 
          digitalWrite(DE_RE, LOW);          
       }
       
        else if(funcao=='L'){
          int sensor = analogRead(0);             // lê o sensor 
          String sensor2 = " " + String(sensor);
          digitalWrite(DE_RE, HIGH);              // MAX485 como transmisor 
          rsSerial.print("i");                    // Inicia da transmissão  
          delay(8);    
          rsSerial.print(sensor2);                // envia  
          rsSerial.flush(); 
          digitalWrite(DE_RE, LOW);               // MAX485 como receptor              
       }
     }
   }
 } 
