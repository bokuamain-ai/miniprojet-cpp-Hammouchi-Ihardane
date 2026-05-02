#include <iostream>
#include "src/models/UndergraduateStudent.h"
#include "src/models/GraduateStudent.h"
#include "src/models/PhDStudent.h"
#include "src/services/StudentManager.h"
#include "src/exceptions/StudentExceptions.h"
#include "src/persistence/PersistenceManager.h"
using namespace std;

int main()
{
    StudentManager mgr;

    // Chargement automatique au demarrage
    PersistenceManager::load(mgr, "data/students.txt");

    if (mgr.count() == 0)
    {
        cout << "Ajout d'etudiants..." << endl;
        mgr.add(make_shared<UndergraduateStudent>("Benali Amira", 1001, 3.8, "Informatique"));
        mgr.add(make_shared<GraduateStudent>("Cherif Omar", 1002, 3.5, "IA"));
        mgr.add(make_shared<PhDStudent>("Meziane Riad", 1003, 3.9, "Dr. Hadj", 2));
    }

    cout << "\n=== Etudiants en memoire ===" << endl;
    for (auto &pair : mgr.getAll())
        pair.second->display();

    // Sauvegarde
    PersistenceManager::save(mgr, "data/students.txt");

    cout << "\n=== Rechargement depuis fichier ===" << endl;
    StudentManager mgr2;
    PersistenceManager::load(mgr2, "data/students.txt");
    for (auto &pair : mgr2.getAll())
        pair.second->display();

    return 0;
}