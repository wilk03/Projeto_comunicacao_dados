
#include <SPI.h>
#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "SSID";                               // SSID do WiFi
char pass[] = "**********";                         // senha do  WiFi
WiFiServer server(80);

IPAddress ip(192, 168, 15, 250);                    // endereço IP do servidor
IPAddress gateway(192, 168, 15, 1);                 // gateway
IPAddress subnet(255, 255, 255, 0);                 // mascara de subrede

void setup() {
  Serial.begin(9600);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  server.begin();
  digitalWrite(ledPin, HIGH);
}

void loop () {
  if (Serial.available()) {                         //verifica se a algum comando
    String comando = Serial.readString();           //Lê o comando
    String check = "";
    String sensor = "";
//-------------------------- ATUAR ESCRAVO 1 ----------------------------------------------------  
 
    if (comando == "S1A") {                
      while (check != "Escravo 1 Atuou!") {         // enquanto nao houver confirmação
        WiFiClient client = server.available();     // Se conecta ao cliente
        if (client) {
          if (client.connected()) {                 // Se estiver conectado
            digitalWrite(ledPin, LOW);              // led indicativo
            client.println("S1A\r");                // envia comando
            check = client.readStringUntil('\r');   // recebe mensagem de confirmação
            client.flush();
          }
          client.stop();                            // termina conexão
        }
      }
      digitalWrite(ledPin, HIGH);                   // led indicativo
      Serial.println(check);                        // imprime mensagem de confirmação 
    }
//---------------------------ATUAR ESCRAVO 2------------------------------------------------------   
 
    else if (comando == "S2A") {
      while (check != "Escravo 2 Atuou!") {
        WiFiClient client = server.available();
        if (client) {
          if (client.connected()) {
            digitalWrite(ledPin, LOW);
            client.println("S2A\r");
            check = client.readStringUntil('\r');
            client.flush();
          }
          client.stop();
        }
      }
      digitalWrite(ledPin, HIGH);
      Serial.println(check);
    }
//----------------------------LEITURA ESCRAVO 1---------------------------------------------------

    else if (comando == "S1L") {                     
      while (check != "Escravo 1 Sensor:") {        // enquanto nao houver confirmação
        WiFiClient client = server.available();     // Se conecta ao cliente
        if (client) {
          if (client.connected()) {                 // Se estiver conectado
            digitalWrite(ledPin, LOW);              // led indicativo
            client.println("S1L\r");                // envia comando
            check = client.readStringUntil('\r');   // recebe mensagem de confirmação
            sensor = client.readString();           // recebe o valor de leitura
            client.flush();
          }
          client.stop();                            // termina conexão
        }
      }
      digitalWrite(ledPin, HIGH);                   // led indicativo
      Serial.print(check);                          // imprime mensagem de confirmação
      Serial.print(sensor);                         // imprime valor de leitura
    }
//------------------------------LEITURA ESCRAVO 2--------------------------------------------------
  
    else if (comando == "S2L") {
      while (check != "Escravo 2 Sensor:") {
        WiFiClient client = server.available();
        if (client) {
          if (client.connected()) {
            digitalWrite(ledPin, LOW); 
            client.println("S2L\r");
            check = client.readStringUntil('\r'); 
            sensor = client.readString();
            client.flush();
          }
          client.stop();               
        }
      }
      digitalWrite(ledPin, HIGH);
      Serial.print(check);
      Serial.print(sensor);
    }
  }
}
