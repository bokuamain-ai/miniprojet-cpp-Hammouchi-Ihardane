#ifndef PHDSTUDENT_H
#define PHDSTUDENT_H
#include "Student.h"
#include <string>
using namespace std;

class PhDStudent : public Student
{
private:
    string supervisor; // Superviseur/Directeur de thèse
    int yearOfStudy;   // Année de doctorat (1-4 typically)

public:
    PhDStudent(const string &name, int id, float gpa, const string &supervisor, int yearOfStudy);

    void display() const override;
    string getType() const override;
    double computeScholarship() const override;

    // Accesseurs et mutateurs
    string getSupervisor() const { return supervisor; }
    void setSupervisor(const string &sup) { supervisor = sup; }
    int getYearOfStudy() const { return yearOfStudy; }
    void setYearOfStudy(int year) { yearOfStudy = year; }
};

#endif
