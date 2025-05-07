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
  avancer(2000);
  delay(1000);
  tournerGauche(1000);
  delay(1000);
  reculer(1500);
  delay(1000);
  tournerDroite(1000);
  delay(2000);
}

// Fonction avancer pendant une durée (ms)
void avancer(unsigned long duree) {
  md25.setMotor1Speed(220);
  md25.setMotor2Speed(220);
  Serial.println("Avancer");
  delay(duree);
  arreter();
}

// Fonction reculer pendant une durée (ms)
void reculer(unsigned long duree) {
  md25.setMotor1Speed(50);
  md25.setMotor2Speed(50);
  Serial.println("Reculer");
  delay(duree);
  arreter();
}

// Fonction tourner à gauche sur place
void tournerGauche(unsigned long duree) {
  md25.setMotor1Speed(50);    // recule moteur gauche
  md25.setMotor2Speed(220);   // avance moteur droit
  Serial.println("Tourner à gauche");
  delay(duree);
  arreter();
}

// Fonction tourner à droite sur place
void tournerDroite(unsigned long duree) {
  md25.setMotor1Speed(220);   // avance moteur gauche
  md25.setMotor2Speed(50);    // recule moteur droit
  Serial.println("Tourner à droite");
  delay(duree);
  arreter();
}

// Fonction stop
void arreter() {
  md25.setMotor1Speed(128);
  md25.setMotor2Speed(128);
  Serial.println("Stop");
}
