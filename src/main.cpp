#include <Arduino.h>
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "0"
#define BLYNK_TEMPLATE_NAME "Blynk LED"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk credentials
const char* auth = "dR6UwI9yK1iE1aai5rxjtN-dsLsNqB7u";
const char* ssid = "BTS_CIEL";
const char* password = "ERIR1234";

// Motor pins
#define pinIN1 16
#define pinIN2 17
#define pinENA 18 // PWM
#define pinIN3 19
#define pinIN4 21
#define pinENB 22 // PWM

// Motor speed (PWM duty cycle: 0 to 255)
int motorSpeed = 255;

// PWM configuration
const int pwmFreq = 5000;      // PWM frequency (5kHz)
const int pwmResolution = 8;  // 8-bit resolution (0-255)
const int pwmChannelENA = 0;  // Channel for ENA
const int pwmChannelENB = 1;  // Channel for ENB

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n");

  // Initialize WiFi
  WiFi.persistent(false);
  WiFi.begin(ssid, password);
  Serial.print("Tentative de connexion...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nConnexion établie!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  // Initialize Blynk
  Blynk.begin(auth, ssid, password, IPAddress(192, 168, 1, 44), 8080);

  // Motor pins configuration
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

  // Setup PWM channels
  ledcSetup(pwmChannelENA, pwmFreq, pwmResolution); // Configure channel for ENA
  ledcSetup(pwmChannelENB, pwmFreq, pwmResolution); // Configure channel for ENB

  // Attach PWM channels to motor pins
  ledcAttachPin(pinENA, pwmChannelENA);
  ledcAttachPin(pinENB, pwmChannelENB);
}

void loop() {
  // Run Blynk
  Blynk.run();
}

// Function to control motor (forward/reverse)
BLYNK_WRITE(V1) { // Linked to Blynk virtual pin V1
  int pinValue = param.asInt(); // Button state (0 or 1)

  if (pinValue == 1) {
    // Move robot forward
    digitalWrite(pinIN1, HIGH);  // IN1
    digitalWrite(pinIN2, LOW);   // IN2
    digitalWrite(pinIN3, HIGH);  // IN3
    digitalWrite(pinIN4, LOW);   // IN4
    ledcWrite(pwmChannelENA, motorSpeed); // Set speed for Motor 1 (ENA)
    ledcWrite(pwmChannelENB, motorSpeed); // Set speed for Motor 2 (ENB)
  } else {
    // Stop motors
    digitalWrite(pinIN1, LOW);  // IN1
    digitalWrite(pinIN2, LOW);  // IN2
    digitalWrite(pinIN3, LOW);  // IN3
    digitalWrite(pinIN4, LOW);  // IN4
    ledcWrite(pwmChannelENA, 0); // Stop Motor 1
    ledcWrite(pwmChannelENB, 0); // Stop Motor 2
  }
}
