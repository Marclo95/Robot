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

  md25.setMode(0);              // Mode 0 : 0=reverse, 128=stop, 255=forward
  md25.setAccelerationRate(5);  // Accélération douce

  Serial.println("Contrôle clavier prêt.");
  Serial.println("a=avancer, r=reculer, g=gauche, d=droite, s=stop");
}

void loop() {
  if (Serial.available() > 0) {
    char commande = Serial.read();
    Serial.print("Commande reçue : ");
    Serial.println(commande);

    switch (commande) {
      case 'a':
        avancer();
        break;
      case 'r':
        reculer();
        break;
      case 'g':
        tournerGauche();
        break;
      case 'd':
        tournerDroite();
        break;
      case 's':
        arreter();
        break;
      default:
        Serial.println("Commande inconnue.");
        break;
    }
  }
}

// Fonctions de mouvement
void avancer() {
  md25.setMotor1Speed(220);
  md25.setMotor2Speed(220);
  Serial.println("Avancer");
}

void reculer() {
  md25.setMotor1Speed(50);
  md25.setMotor2Speed(50);
  Serial.println("Reculer");
}

void tournerGauche() {
  md25.setMotor1Speed(50);
  md25.setMotor2Speed(220);
  Serial.println("Tourner à gauche");
}

void tournerDroite() {
  md25.setMotor1Speed(220);
  md25.setMotor2Speed(50);
  Serial.println("Tourner à droite");
}

void arreter() {
  md25.setMotor1Speed(128);
  md25.setMotor2Speed(128);
  Serial.println("Stop");
}
