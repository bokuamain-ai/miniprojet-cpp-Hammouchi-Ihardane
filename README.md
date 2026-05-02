# Système de Gestion des Étudiants

## Informations
- **Noms** : Hammouchi Niama & Ihardane Hammouchi
- **Groupe** : 1ère année IMS
- **Année universitaire** : 2025/2026
- **Date de rendu** : 15-05-2026

## Description
Système complet de gestion des étudiants en C++ orienté objet.
Le projet couvre : OOP, STL, Exceptions, Persistance et Interface Qt.

## Structure du projet
StudentManager/
├── src/
│   ├── models/          # Classes Student, Undergraduate, Graduate, PhD
│   ├── services/        # StudentManager (logique métier)
│   ├── exceptions/      # Exceptions personnalisées
│   ├── persistence/     # Lecture/écriture fichiers
│   └── gui/             # Interface Qt
├── data/
│   └── students.txt     # Données persistantes
├── tests/
│   └── test_main.cpp    # Tests unitaires
├── StudentManager.pro   # Fichier projet Qt
└── README.md
## Compilation

### Interface graphique (Qt)
qmake StudentManager.pro
mingw32-make
release\StudentManager.exe
### Tests unitaires
C:\mingw64\bin\g++ -std=c++17 -static tests/test_main.cpp src/models/*.cpp src/services/StudentManager.cpp src/persistence/PersistenceManager.cpp -o tests/test_main.exe
tests\test_main.exe
## Fonctionnalités
- Ajout, modification, suppression d'étudiants
- 3 types : Licence, Master, Doctorat
- Calcul automatique des bourses
- Tri par GPA et par nom
- Recherche en temps réel
- Persistance des données
- Gestion des exceptions
- 20/20 tests passés

## Vidéo de démonstration
[Lien YouTube/Drive ici]

## Lien GitHub
https://github.com/bokuamain-ai/miniprojet-cpp-Hammouchi-Ihardane
