#include <Wire.h>
#include "MMA7660.h"

// MD25
#define MD25_ADDR 0x58
#define CMD_REG 0x10
#define SPEED1_REG 0x00
#define SPEED2_REG 0x01

// HC-SR04
const int sonarPin = 7;

// Accelerometer
MMA7660 acc;

// Fonctions MD25
void setMotorSpeeds(int8_t speed1, int8_t speed2) {
  Wire.beginTransmission(MD25_ADDR);
  Wire.write(SPEED1_REG);
  Wire.write(speed1);
  Wire.write(speed2);
  Wire.endTransmission();
}

void stopMotors() {
  setMotorSpeeds(0, 0);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(sonarPin, OUTPUT);
  digitalWrite(sonarPin, LOW);
  delay(100);

  acc.init();  // initialise l'accéléro

  // Reset les encodeurs MD25
  Wire.beginTransmission(MD25_ADDR);
  Wire.write(CMD_REG);
  Wire.write(0x20);  // reset encoder counts
  Wire.endTransmission();

  Serial.println("Robot autonome prêt !");
}

void loop() {
  // === Lire HC-SR04 ===
  long duration, distance;
  pinMode(sonarPin, OUTPUT);
  digitalWrite(sonarPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sonarPin, LOW);
  pinMode(sonarPin, INPUT);
  duration = pulseIn(sonarPin, HIGH, 30000); // timeout 30 ms
  distance = duration * 0.034 / 2;
  Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");

  // === Lire accéléro ===
  int8_t x, y, z;
  acc.getXYZ(&x, &y, &z);
  Serial.print("Acc X: "); Serial.print(x);
  Serial.print(" | Y: "); Serial.print(y);
  Serial.print(" | Z: "); Serial.println(z);

  bool obstacle = (distance > 0 && distance < 30); // obstacle détecté
  bool danger = (abs(x) > 5 || abs(y) > 5 || z < 17); // inclinaison anormale

  if (danger) {
    Serial.println("⚠️ Inclinaison détectée → arrêt d'urgence");
    stopMotors();
    delay(500);
    return;
  }

  if (obstacle) {
    Serial.println("🚧 Obstacle ! Stop + tourne");
    stopMotors();
    delay(500);

    // recule un peu
    setMotorSpeeds(-80, -80);
    delay(600);
    stopMotors();
    delay(300);

    // tourne à gauche
    setMotorSpeeds(-60, 60);
    delay(600);
    stopMotors();
    delay(300);
  } else {
    // Avance
    setMotorSpeeds(80, 80);
  }

  delay(200);
}





































// #include <Wire.h>

// // ----- MD25 Constants -----
// #define MD25_ADDR 0x58   // Adresse I2C du MD25 (par défaut)
// #define ENCODER1_REG 0x02
// #define ENCODER2_REG 0x06

// // ----- HC-SR04 (1-pin version) -----
// const int sonarPin = 7;

// // ----- Grove Accelerometer (ADXL345 compatible I2C) -----
// //#define ACC_ADDR 0x53    // Adresse I2C du Grove Accelerometer
// #define ACC_ADDR 0x4C    // Adresse I2C du Grove Accelerometer


// void setup() {
//   Serial.begin(9600);
//   Wire.begin();  // Démarre la communication I2C

//   // Configuration de la broche sonar
//   pinMode(sonarPin, OUTPUT);
//   digitalWrite(sonarPin, LOW);
//   delay(100);

//   // Initialiser l'accéléromètre : activer le mode mesure
//   Wire.beginTransmission(ACC_ADDR);
//   Wire.write(0x2D); // POWER_CTL
//   Wire.write(0x08); // Mode mesure
//   Wire.endTransmission();

//   delay(500);
//   Serial.println("Initialisation terminée");
// }

// void loop() {
//   // ---- Lecture HC-SR04 ----
//   long duration, distance;
//   pinMode(sonarPin, OUTPUT);
//   digitalWrite(sonarPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(sonarPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(sonarPin, LOW);

//   pinMode(sonarPin, INPUT);
//   duration = pulseIn(sonarPin, HIGH, 30000); // Timeout 30 ms

//   distance = duration * 0.034 / 2;
//   Serial.print("Distance HC-SR04 : ");
//   Serial.print(distance);
//   Serial.println(" cm");

//   // ---- Lecture de l'accéléromètre ----
//   int16_t ax, ay, az;
//   Wire.beginTransmission(ACC_ADDR);
//   Wire.write(0x32); // Adresse du registre X-axis LSB
//   Wire.endTransmission(false);
//   Wire.requestFrom((uint8_t)ACC_ADDR, (uint8_t)6, (uint8_t)true);

//   if (Wire.available() == 6) {
//     ax = Wire.read() | (Wire.read() << 8);
//     ay = Wire.read() | (Wire.read() << 8);
//     az = Wire.read() | (Wire.read() << 8);
//     Serial.print("Acc X: "); Serial.print(ax);
//     Serial.print(" | Y: "); Serial.print(ay);
//     Serial.print(" | Z: "); Serial.println(az);
//   } else {
//     Serial.println("Erreur lecture accéléro");
//   }

//   // ---- Lecture des encodeurs MD25 ----
//   long encoder1 = readEncoder(MD25_ADDR, ENCODER1_REG);
//   long encoder2 = readEncoder(MD25_ADDR, ENCODER2_REG);

//   Serial.print("Encoder1: "); Serial.print(encoder1);
//   Serial.print(" | Encoder2: "); Serial.println(encoder2);

//   Serial.println("-----------------------------");
//   delay(1000);
// }

// long readEncoder(byte addr, byte reg) {
//   Wire.beginTransmission(addr);
//   Wire.write(reg);
//   Wire.endTransmission();

//   Wire.requestFrom((uint8_t)addr, (uint8_t)4, (uint8_t)true);

//   long value = 0;
//   while (Wire.available() < 4); // attendre les 4 octets
//   for (int i = 0; i < 4; i++) {
//     value = (value << 8) | Wire.read();
//   }
//   return value;
// }


// #include <Wire.h>
// #include "MMA7660.h"

// MMA7660 acc;

// void setup() {
//   Serial.begin(9600);
//   acc.init();  // Initialise le capteur
//   Serial.println("MMA7660 prêt");
// }

// void loop() {
//   int8_t x, y, z;
//   acc.getXYZ(&x, &y, &z);

//   Serial.print("Acc X: "); Serial.print(x);
//   Serial.print(" | Y: "); Serial.print(y);
//   Serial.print(" | Z: "); Serial.println(z);

//   delay(1000);
// }



