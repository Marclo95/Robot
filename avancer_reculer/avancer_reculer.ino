/*
  MD25_Test.ino - Example for the MD25 library.
  Created by Josh Villbrandt (http://javconcepts.com/), July 7, 2012.
  Released into the public domain.
*/

#include <Wire.h>
#include <MD25.h>

MD25 md25;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  md25.setMode(0);              // Mode 0 : 0 = arrière, 128 = stop, 255 = avant
  md25.setAccelerationRate(5);  // Accélération douce
  Serial.println("MD25 prêt");
}

void loop() {
  avancer(3000); // Avancer 3 secondes
  delay(1000);   // Pause 1 seconde
  reculer(2000); // Reculer 2 secondes
  delay(3000);   // Pause 3 secondes
}

// Fonction avancer pendant une durée en millisecondes
void avancer(unsigned long duree) {
  md25.setMotor1Speed(220); // vitesse avant
  md25.setMotor2Speed(220);
  Serial.println("Avancer");
  delay(duree);
  arreter();
}

// Fonction reculer pendant une durée en millisecondes
void reculer(unsigned long duree) {
  md25.setMotor1Speed(50);  // vitesse arrière
  md25.setMotor2Speed(50);
  Serial.println("Reculer");
  delay(duree);
  arreter();
}

// Fonction stop
void arreter() {
  md25.setMotor1Speed(128); // stop
  md25.setMotor2Speed(128);
  Serial.println("Stop");
}
