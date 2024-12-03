/*********************************************************************************************
   Contrôle de deux moteurs cc avec un L298N
   http://electroniqueamateur.blogspot.com/2016/06/controle-dun-ou-deux-moteurs-cc-avec.html
 *********************************************************************************************/

// définition des pins de l'Arduino qui contrôlent le 1er moteur

#include <Arduino.h>

/*********************************************************************************************
   Contrôle de deux moteurs cc avec un L298N
   http://electroniqueamateur.blogspot.com/2016/06/controle-dun-ou-deux-moteurs-cc-avec.html
 *********************************************************************************************/

// définition des pins de l'Arduino qui contrôlent le 1er moteur
#define pinIN1 4
#define pinIN2 3
#define pinENA 1 // doit être une pin PWM 

// définition des pins de l'Arduino qui contrôlent le 2e moteur
#define pinIN3 16
#define pinIN4 2
#define pinENB 15 // doit être une pin PWM 


void setup() {

  // toutes ces pins sont des sorties

  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);

  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  pinMode(pinENB, OUTPUT);

}

void loop() {

  // le premier moteur tourne en marche avant, lentement

  analogWrite(pinENA, 20); // vitesse lente (entre 0 et 255)
  // si le moteur ne tourne pas du tout, augmentez la valeur
  digitalWrite(pinIN1, true);
  digitalWrite(pinIN2, false);

  // le deuxième moteur en marche arrière, rapidement

  analogWrite(pinENB, 200); // vitesse assez rapide
  digitalWrite(pinIN3, false);
  digitalWrite(pinIN4, true);

  // on les laisse tourner comme ça pendant 2 secondes

  delay(2000);

  // le premier moteur tourne en marche arrière, rapidement

  analogWrite(pinENA, 255); // vitesse maximale
  digitalWrite(pinIN1, false); // le contraire de ce qu'on avait en marche avant
  digitalWrite(pinIN2, true);

  analogWrite(pinENB, 40); // vitesse assez lente: augmentez le nombre si votre moteur ne tourne pas du tout
  digitalWrite(pinIN3, true); // le contraire de ce qu'on avait en marche arrière
  digitalWrite(pinIN4, false);

  // on les laisse tourner comme ça pendant 2 secondes

  delay(2000);

}