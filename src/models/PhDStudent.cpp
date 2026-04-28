#include "PhDStudent.h"
#include <iostream>
#include <iomanip>
using namespace std;

PhDStudent::PhDStudent(const string &name, int id, float gpa, const string &supervisor, int yearOfStudy)
    : Student(name, id, gpa), supervisor(supervisor), yearOfStudy(yearOfStudy) {}

void PhDStudent::display() const
{
    cout << "[Doctorat] ID: " << id << " | Nom: " << name
         << " | GPA: " << fixed << setprecision(1) << gpa
         << " | Superviseur: " << supervisor
         << " | Annee: " << yearOfStudy
         << " | Bourse: " << fixed << setprecision(0) << computeScholarship()
         << " EUR" << endl;
}

string PhDStudent::getType() const
{
    return "Doctorat";
}

double PhDStudent::computeScholarship() const
{
    return 1200.0;
}
