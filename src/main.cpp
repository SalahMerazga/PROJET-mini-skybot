#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "0"
#define BLYNK_TEMPLATE_NAME "New Device"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Authentification Blynk
const char* auth = "dR6UwI9yK1iE1aai5rxjtN-dsLsNqB7u";
// WiFi credentials
const char* ssid = "BTS_CIEL";
const char* password = "ERIR1234";

// Pins de contrôle
const int pins[] = {4, 3, 21, 16, 2, 15};

// Initialisation
void setup() {
  Serial.begin(9600);

  // Configurer les pins en sortie
  for (int i = 0; i < 6; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW); // Assurez-vous que toutes les broches sont à l'arrêt au début
  }

  // Connexion WiFi
  Serial.println("\nConnexion au WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnexion établie!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  // Initialisation de Blynk
  Blynk.begin(auth, ssid, password);
}

// Fonction appelée par Blynk pour le bouton sur V1
BLYNK_WRITE(V1) {
  int pinValue = param.asInt(); // Lire la valeur du bouton (0 ou 1)
  if (pinValue == 1) {
    Serial.println("Activer les moteurs !");
    // Activer les broches
    for (int i = 0; i < 6; i++) {
      digitalWrite(pins[i], HIGH);
    }
  } else {
    Serial.println("Arrêter les moteurs !");
    // Désactiver les broches
    for (int i = 0; i < 6; i++) {
      digitalWrite(pins[i], LOW);
    }
  }
}

void loop() {
  Blynk.run(); // Exécuter les tâches Blynk
}
