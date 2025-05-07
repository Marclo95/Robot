#include <Wire.h>
#include <MD25.h>

MD25 md25;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialisation du MD25 en mode 0 (0 = arrière, 128 = stop, 255 = avant)
  md25.setMode(0);
  md25.setAccelerationRate(5);  // Accélération douce pour éviter les à-coups

  Serial.println("Contrôle clavier MD25 prêt.");
  Serial.println("Commandes :");
  Serial.println(" a = avancer");
  Serial.println(" r = reculer");
  Serial.println(" g = tourner à gauche");
  Serial.println(" d = tourner à droite");
  Serial.println(" s = stop");
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
  md25.setMotor1Speed(220);  // moteur gauche
  md25.setMotor2Speed(220);  // moteur droit
  Serial.println("→ Avancer");
}

void reculer() {
  md25.setMotor1Speed(50);   // moteur gauche
  md25.setMotor2Speed(50);   // moteur droit
  Serial.println("← Reculer");
}

void tournerGauche() {
  md25.setMotor1Speed(50);   // recule à gauche
  md25.setMotor2Speed(200);  // avance à droite
  Serial.println("↶ Tourner à gauche");
}

void tournerDroite() {
  md25.setMotor1Speed(200);  // avance à gauche
  md25.setMotor2Speed(50);   // recule à droite
  Serial.println("↷ Tourner à droite");
}

void arreter() {
  md25.setMotor1Speed(128);  // stop
  md25.setMotor2Speed(128);
  Serial.println("■ Stop");
}
