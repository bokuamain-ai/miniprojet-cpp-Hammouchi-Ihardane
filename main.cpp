#include <iostream>
#include "src/models/UndergraduateStudent.h"
#include "src/models/GraduateStudent.h"
#include "src/models/PhDStudent.h"
#include "src/services/StudentManager.h"
using namespace std;

int main()
{
    StudentManager mgr;

    mgr.add(make_shared<UndergraduateStudent>("Benali Amira", 1001, 3.8, "Informatique"));
    mgr.add(make_shared<GraduateStudent>("Cherif Omar", 1002, 3.5, "IA"));
    mgr.add(make_shared<PhDStudent>("Meziane Riad", 1003, 3.9, "Dr. Hadj", 2));
    mgr.add(make_shared<UndergraduateStudent>("Ziani Sara", 1004, 2.9, "Mathematiques"));
    mgr.add(make_shared<GraduateStudent>("Ait Ali Karim", 1005, 3.2, "Reseaux"));

    cout << "=== Tri par GPA (decroissant) ===" << endl;
    for (auto &s : mgr.sortByGpa())
        s->display();

    cout << "\n=== Tri par Nom ===" << endl;
    for (auto &s : mgr.sortByName())
        s->display();

    cout << "\nMoyenne GPA : " << mgr.averageGpa() << endl;
    cout << "Nombre d'etudiants : " << mgr.count() << endl;

    cout << "\n=== Recherche 'ali' ===" << endl;
    for (auto &s : mgr.findByName("ali"))
        s->display();

    cout << "\n=== Test suppression ID 1002 ===" << endl;
    mgr.remove(1002);
    cout << "Apres suppression : " << mgr.count() << " etudiants" << endl;

    return 0;
}