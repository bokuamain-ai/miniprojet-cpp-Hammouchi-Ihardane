#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(const string &name, int id, float gpa)
    : name(name), id(id), gpa(gpa) {}

void Student::setName(const string &n)
{
    name = n;
}

void Student::setGpa(float g)
{
    if (g < 0.0f || g > 4.0f)
    {
        throw invalid_argument("GPA must be between 0.0 and 4.0");
    }
    gpa = g;
}
