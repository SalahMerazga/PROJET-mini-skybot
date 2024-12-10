#include <Arduino.h>  //EASY PEASY LEMON SQUEEZIE

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "0";

#define BLYNK_TEMPLATE_NAME "Blynk LED";

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const char* auth = "dR6UwI9yK1iE1aai5rxjtN-dsLsNqB7u";
const char* ssid = "BTS_CIEL";
const char* password = "ERIR1234";
/*********************************************************************************************
   Contrôle de deux moteurs cc avec un L298N
   http://electroniqueamateur.blogspot.com/2016/06/controle-dun-ou-deux-moteurs-cc-avec.html
 *********************************************************************************************/

// définition des pins de l'Arduino qui contrôlent le 1er moteur
#define pinIN1 17
#define pinIN2 18
#define pinENA 16 // doit être une pin PWM 

// définition des pins de l'Arduino qui contrôlent le 2e moteur
#define pinIN3 19
#define pinIN4 21
#define pinENB 22 // doit être une pin PWM 

int motorSpeed = 60;

void setup() {

  Serial.begin(9600);
delay(1000);
Serial.println("\n");

pinMode(pinENA, OUTPUT);
digitalWrite(pinENA, LOW);
WiFi.persistent(false);
WiFi.begin(ssid, password);
Serial.print("Tentative de connexion...");
while (WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(100);
}
Serial.println("\n");
Serial.println("Connexion etablie!");
Serial.print("Adresse IP: ");
Serial.println(WiFi.localIP());
Blynk.begin(auth, ssid, password, IPAddress(192,168,1,44), 8080);

  // toutes ces pins sont des sorties

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);

  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

}

void loop() {
  // Faire avancer les moteurs si le bouton Blynk est pressé
  Blynk.run();
}

// Fonction pour contrôler le moteur (avance/recul)
BLYNK_WRITE(V1) { // Associe le bouton Blynk au pin virtuel V1
  int pinValue = param.asInt(); // Valeur du bouton (0 ou 1)
  
  if (pinValue == 1) {  // Si le bouton est pressé
    // Avancer le robot EN
    digitalWrite(pinIN1, HIGH);  // IN1
    digitalWrite(pinIN2, LOW);   // IN2
    digitalWrite(pinIN3, HIGH);  // IN3
    digitalWrite(pinIN4, LOW);   // IN4
    analogWrite(pinENA, motorSpeed); // ENA (vitesse du moteur 1)
    analogWrite(pinENB, motorSpeed); // ENB (vitesse du moteur 2)
  } else {
    // Arrêter les moteurs
    digitalWrite(pinIN1, LOW);  // IN1
    digitalWrite(pinIN2, LOW);  // IN2
    digitalWrite(pinIN3, LOW);  // IN3
    digitalWrite(pinIN4, LOW);  // IN4

    
  }
}
  BLYNK_WRITE(V2) { // Associe le bouton Blynk au pin virtuel V2
  int pinValue = param.asInt(); // Valeur du bouton (0 ou 1)
  
  if (pinValue == 1) {  // Si le bouton est pressé
    // Avancer le robot EN
    digitalWrite(pinIN1, LOW);  // IN1
    digitalWrite(pinIN2, HIGH);   // IN2
    digitalWrite(pinIN3, LOW);  // IN3
    digitalWrite(pinIN4, HIGH);   // IN4
    analogWrite(pinENA, motorSpeed); // ENA (vitesse du moteur 1)
    analogWrite(pinENB, motorSpeed); // ENB (vitesse du moteur 2)
  } else {
    // Arrêter les moteurs
    digitalWrite(pinIN1, LOW);  // IN1
    digitalWrite(pinIN2, LOW);  // IN2
    digitalWrite(pinIN3, LOW);  // IN3
    digitalWrite(pinIN4, LOW);  // IN4

    
  }
}