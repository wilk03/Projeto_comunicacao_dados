
const int DE_RE =  2; 
const int atuador =  3; 
void setup() 
{ 
  Serial.begin(9600);  
  pinMode(DE_RE, OUTPUT);
  pinMode(atuador, OUTPUT);
  digitalWrite(DE_RE, LOW);                 // RS485 como receptor
  digitalWrite(atuador, LOW);
} 
 
void loop() 
{ 
    if(Serial.available()){
    if(Serial.read()=='2'){                //endereço do escravo 1/2
    delay(10);
     char funcao=Serial.read();            // ler o caracter de função
      if(funcao=='A'){
         if(digitalRead(atuador)==LOW){
           digitalWrite(atuador,HIGH);
           }
         else{
           digitalWrite(atuador,LOW);
         }          
       }

       
        if(funcao=='L'){
          int temperatura = analogRead(A0);
          digitalWrite(DE_RE, HIGH);       // rs485 como transmisor 
          Serial.print("i");               // inicio da transmissão  
          delay(8);    
          Serial.print(temperatura);       // envia  
          Serial.flush(); 
          digitalWrite(DE_RE, LOW);        // RS485 como receptor              
       }
     }
   }
 } 
