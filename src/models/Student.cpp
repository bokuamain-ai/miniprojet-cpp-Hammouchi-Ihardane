#include "Student.h"
#include "../exceptions/StudentExceptions.h"
using namespace std;

Student::Student(const string &name, int id, float gpa)
    : name(name), id(id), gpa(gpa)
{
    if (id < 1000)
        throw InvalidIDException(id);
    if (gpa < 0.0f || gpa > 4.0f)
        throw InvalidGradeException(gpa);
}

void Student::setName(const string &n)
{
    name = n;
}

void Student::setGpa(float g)
{
    if (g < 0.0f || g > 4.0f)
        throw InvalidGradeException(g);
    gpa = g;
}