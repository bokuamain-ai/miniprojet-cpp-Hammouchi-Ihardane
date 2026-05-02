#include <iostream>
#include "src/models/UndergraduateStudent.h"
#include "src/models/GraduateStudent.h"
#include "src/models/PhDStudent.h"
#include "src/services/StudentManager.h"
#include "src/exceptions/StudentExceptions.h"
using namespace std;

int main()
{
    StudentManager mgr;

    // Ajout normal
    mgr.add(make_shared<UndergraduateStudent>("Benali Amira", 1001, 3.8, "Informatique"));
    mgr.add(make_shared<GraduateStudent>("Cherif Omar", 1002, 3.5, "IA"));
    mgr.add(make_shared<PhDStudent>("Meziane Riad", 1003, 3.9, "Dr. Hadj", 2));

    cout << "=== Test 1 : ID invalide (< 1000) ===" << endl;
    try
    {
        mgr.add(make_shared<UndergraduateStudent>("Test", 42, 3.0, "Info"));
    }
    catch (const InvalidIDException &e)
    {
        cout << "[ERREUR ID] " << e.what() << endl;
    }

    cout << "\n=== Test 2 : GPA invalide (> 4.0) ===" << endl;
    try
    {
        mgr.add(make_shared<UndergraduateStudent>("Test", 1010, 5.5, "Info"));
    }
    catch (const InvalidGradeException &e)
    {
        cout << "[ERREUR GPA] " << e.what() << endl;
    }

    cout << "\n=== Test 3 : ID duplique ===" << endl;
    try
    {
        mgr.add(make_shared<UndergraduateStudent>("Autre", 1001, 3.0, "Info"));
    }
    catch (const DuplicateIDException &e)
    {
        cout << "[DOUBLON ID] " << e.what() << endl;
    }

    cout << "\n=== Test 4 : Etudiant introuvable ===" << endl;
    try
    {
        mgr.remove(9999);
    }
    catch (const StudentNotFoundException &e)
    {
        cout << "[INTROUVABLE] " << e.what() << endl;
    }

    cout << "\n=== Tous les tests passes ! Programme stable ===" << endl;

    return 0;
}