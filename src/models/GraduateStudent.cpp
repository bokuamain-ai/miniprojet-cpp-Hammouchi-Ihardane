#include "GraduateStudent.h"
#include <iostream>
#include <iomanip>
using namespace std;

GraduateStudent::GraduateStudent(const string &name, int id, float gpa, const string &researchTopic)
    : Student(name, id, gpa), researchTopic(researchTopic) {}

void GraduateStudent::display() const
{
    cout << "[Master] ID: " << id << " | Nom: " << name
         << " | GPA: " << fixed << setprecision(1) << gpa
         << " | Sujet: " << researchTopic
         << " | Bourse: " << fixed << setprecision(0) << computeScholarship()
         << " EUR" << endl;
}

string GraduateStudent::getType() const
{
    return "Master";
}

double GraduateStudent::computeScholarship() const
{
    return gpa * 300.0;
}
