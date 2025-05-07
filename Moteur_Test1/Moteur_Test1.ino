/*
  MD25_Test.ino - Example for the MD25 library.
  Created by Josh Villbrandt (http://javconcepts.com/), July 7, 2012.
  Released into the public domain.
*/

#include <Wire.h>
#include <MD25.h>

MD25 md25; // Par défaut utilise l'adresse 0xB0

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialisation de la carte MD25
  md25.setMode(0);  // Mode 0 : 0 (reverse) → 128 (stop) → 255 (forward)
  md25.setAccelerationRate(5); // Optionnel : régler l'accélération

  Serial.println("MD25 initialisé");
}

void loop() {
  // Démarrer les moteurs
  md25.setMotor1Speed(200);  // Vitesse moteur 1
  md25.setMotor2Speed(200);  // Vitesse moteur 2
  Serial.println("Moteurs ON");
  delay(2000);

  // Stopper les moteurs
  md25.setMotor1Speed(128);  // Stop
  md25.setMotor2Speed(128);  // Stop
  Serial.println("Moteurs OFF");
  delay(2000);
}
