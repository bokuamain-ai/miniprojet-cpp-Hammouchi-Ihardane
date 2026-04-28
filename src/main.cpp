#include "models/Student.h"
#include "models/UndergraduateStudent.h"
#include "models/GraduateStudent.h"
#include "models/PhDStudent.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "====== Mini-Projet C++ - Gestion des Etudiants ======" << endl;
    cout << "Annee Universitaire 2025/2026" << endl
         << endl;

    // Test UndergraduateStudent
    cout << "--- Test Undergraduate Student ---" << endl;
    UndergraduateStudent student1("Amira Benali", 1042, 3.8f, "Informatique");
    student1.display();
    cout << "Bourse calculee: " << student1.computeScholarship() << " EUR" << endl;
    cout << "Type: " << student1.getType() << endl
         << endl;

    // Test UndergraduateStudent avec GPA < 3.5
    cout << "--- Test Undergraduate Student (GPA < 3.5) ---" << endl;
    UndergraduateStudent student2("Zahra Ahmed", 1043, 3.2f, "Mathematiques");
    student2.display();
    cout << "Bourse calculee: " << student2.computeScholarship() << " EUR" << endl
         << endl;

    // Test GraduateStudent
    cout << "--- Test Graduate Student ---" << endl;
    GraduateStudent student3("Cherif Omar", 1055, 3.5f, "IA");
    student3.display();
    cout << "Bourse calculee: " << student3.computeScholarship() << " EUR" << endl;
    cout << "Type: " << student3.getType() << endl
         << endl;

    // Test GraduateStudent avec GPA different
    cout << "--- Test Graduate Student (GPA different) ---" << endl;
    GraduateStudent student4("Karim Hassan", 1056, 3.9f, "Machine Learning");
    student4.display();
    cout << "Bourse calculee: " << student4.computeScholarship() << " EUR" << endl
         << endl;

    // Test PhDStudent
    cout << "--- Test PhD Student ---" << endl;
    PhDStudent student5("Fatima Bouacida", 1070, 3.7f, "Prof. Mohamed Ali", 2);
    student5.display();
    cout << "Bourse calculee: " << student5.computeScholarship() << " EUR" << endl;
    cout << "Type: " << student5.getType() << endl
         << endl;

    // Test PhDStudent
    cout << "--- Test PhD Student 2 ---" << endl;
    PhDStudent student6("Ahmed Naceri", 1071, 4.0f, "Prof. Yasmine Karim", 3);
    student6.display();
    cout << "Bourse calculee: " << student6.computeScholarship() << " EUR" << endl
         << endl;

    // Test setters
    cout << "--- Test Setters ---" << endl;
    student1.setName("Amira B. Benali");
    cout << "Nom modifie: " << student1.getName() << endl;

    try
    {
        student1.setGpa(3.9f);
        cout << "GPA modifie avec succes: " << student1.getGpa() << endl;
        student1.setGpa(5.0f); // Cette ligne devrait lancer une exception
    }
    catch (const invalid_argument &e)
    {
        cout << "Exception rattrapee: " << e.what() << endl;
    }

    cout << "\n====== Tests termines avec succes! ======" << endl;

    return 0;
}
