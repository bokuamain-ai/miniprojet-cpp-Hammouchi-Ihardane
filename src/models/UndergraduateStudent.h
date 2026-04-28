#ifndef UNDERGRADUATESTUDENT_H
#define UNDERGRADUATESTUDENT_H
#include "Student.h"
#include <string>
using namespace std;

class UndergraduateStudent : public Student
{
private:
    string major; // Filière, ex : "Informatique"

public:
    UndergraduateStudent(const string &name, int id, float gpa, const string &major);

    void display() const override;
    string getType() const override;
    double computeScholarship() const override;

    // Accesseurs et mutateurs
    string getMajor() const { return major; }
    void setMajor(const string &m) { major = m; }
};

#endif
