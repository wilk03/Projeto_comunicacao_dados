
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h> 
SoftwareSerial rsSerial (13,15);

const int DE_RE = 4;                               // HIGH:TX, LOW:RX
const int atuador = 5; 
byte ledPin = 2; 
char ssid[] = "SSID";                              // SSID do WiFi
char pass[] = "*******";                           // Senha do WiFi
unsigned long askTimer = 0;

IPAddress server(192,168,15,250);                  // endereço IP
WiFiClient client;

void setup() {
  Serial.begin(9600); 
  rsSerial.begin(9600);
  WiFi.begin(ssid, pass);                          // conecta ao roteador
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  pinMode(ledPin, OUTPUT);
  pinMode(atuador, OUTPUT);
  pinMode(DE_RE, OUTPUT);
  digitalWrite(atuador, LOW);
  digitalWrite(DE_RE, HIGH); 
}

void loop () {
  client.connect(server, 80);                      // se conecta ao servidor
  digitalWrite(ledPin, HIGH);                      // led indicativo
  String comando = client.readStringUntil('\r');   // recebe mensagem do servidor

//---------------------------ATUAR ESCRAVO 1---------------------------------------------------------  

  if(comando=="S1A"){
    digitalWrite(ledPin, LOW);                     // led indicativo
    if(digitalRead(atuador)==LOW){                 // se estiver desligado
      digitalWrite(atuador,HIGH);                  // liga
    }
    else{                                          // se estiver ligado
      digitalWrite(atuador,LOW);                   // desliga
    } 
    client.print("Escravo 1 Atuou!\r");            // mensagem de confirmação
    client.flush();
  } 
//---------------------------ATUAR ESCRAVO 2----------------------------------------------------------  

  else if(comando=="S2A"){ 
    Serial.print("2");                             // endereço do escravo 2
    delay(8);
    Serial.println("A");                           // função Atuador
    Serial.flush();
    digitalWrite(DE_RE, LOW);                      // MAX485 como receptor
    if(rsSerial.find("i")){                        // aguarda confirmação
     client.print("Escravo 2 Atuou!\r");           // envia mensagem ao servidor
     client.flush();
     digitalWrite(ledPin, LOW);                    // led indicativo
   }
   digitalWrite(DE_RE, HIGH);                      // MAX485 como emissor
  }
//---------------------------LEITURA ESCRAVO 1--------------------------------------------------------- 
 
  else if(comando=="S1L"){                         
     int sensor = analogRead(A0);                  // lê o valor do sensor 
     String sensor2 = " " + String(sensor);        // inteiro para string
     client.print("Escravo 1 Sensor:\r");          // envia mensagem de confirmação
     client.flush();
     client.println(sensor2);                      // envia string com o valor
  } 
//---------------------------LEITURA ESCRAVO 2---------------------------------------------------------  

  else if(comando=="S2L"){ 
    Serial.print("2");                             // endereço do escravo
    delay(8);
    Serial.println("L");                           // função leitura
    Serial.flush();
    digitalWrite(DE_RE, LOW);                      // MAX485 como receptor
    if(rsSerial.find("i")){                        // aguarda confirmação 
      delay(10);
      String sensor=rsSerial.readString();         // recebe a leitura
      String sensor2 = "" + String(sensor);  
      client.print("Escravo 2 Sensor:\r");         // envia mensagem de confirmação
      client.flush();    
      client.println(sensor2);                     // envia leitura do sensor
   
      digitalWrite(ledPin, LOW);                   // led indicatico
   }
   digitalWrite(DE_RE, HIGH);                      // MAX485 como emissor
  }
}
