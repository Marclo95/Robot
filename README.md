# Projet robot autonome

# Etudiants : KITSOUKOU Debora , DJEUNGA Daniela, ASERNE Marc, FARAG David

Brainstorming : Résumé des tâches
- Concevoir la structure du robot : Daniela
- Choisir les moteurs et réaliser leurs contrôles : Debora, Marc
- Concevoir le module d'alimentation de l'ensemble : Debora, Marc, Daniela et David
- Faire le lien entre l'application ROS2 et la carte Arduino : Debora
- Choix des composants et autres : David

# Suivi des Contributions et Choix Techniques
# 1. Structure du robot
  -Responsable : Daniela
  -Outil utilisé : Fusion 360
  -Travail effectué : Conception du schéma 3D du robot.

# 2. Choix des moteurs et contrôle
  -Responsables : Debora, Marc
  -Matériel utilisé : MD25 - Dual 12V 2.8A H Bridge Motor Drive
  -Détails :
      -Pilote deux moteurs avec retour des encodeurs.
      -Communication via I2C ou Série TTL.
      -Alimentation en 12V, avec régulation 5V intégrée pour la logique externe.
      -Intègre des fonctions avancées : régulation automatique de vitesse, timeout de sécurité, mode de virage.
      -Compatible avec ROS2 via Arduino.

# 3. Module d’alimentation
  -Responsables : Debora, Marc, Daniela, David
  -Choix technique : Batterie 12V minimum
  -Remarque : Le MD25 exige un minimum de 9V pour fonctionner correctement.

# 4. Lien entre ROS2 et Arduino
  -Responsable : Debora
  -Objectif : Assurer la communication entre ROS2 (sur Raspberry Pi) et la carte Arduino contrôlant les moteurs via le MD25.

# 5. Choix des composants principaux
  -Responsable : David
  -Composants choisis :
  -Raspberry Pi 3 Model B+ : pour faire tourner ROS2.
  -Arduino Uno R3 (CH340) : pour la gestion des moteurs et capteurs.
  -LIDAR : pour la détection d’obstacles et la navigation autonome.
