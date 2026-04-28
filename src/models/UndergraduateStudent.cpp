#include "UndergraduateStudent.h"
#include <iostream>
#include <iomanip>
using namespace std;

UndergraduateStudent::UndergraduateStudent(const string &name, int id, float gpa, const string &major)
    : Student(name, id, gpa), major(major) {}

void UndergraduateStudent::display() const
{
    cout << "[Licence] ID: " << id << " | Nom: " << name
         << " | GPA: " << fixed << setprecision(1) << gpa
         << " | Filiere: " << major
         << " | Bourse: " << fixed << setprecision(0) << computeScholarship()
         << " EUR" << endl;
}

string UndergraduateStudent::getType() const
{
    return "Licence";
}

double UndergraduateStudent::computeScholarship() const
{
    if (gpa >= 3.5f)
    {
        return 500.0;
    }
    return 0.0;
}
