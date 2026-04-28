#ifndef GRADUATESTUDENT_H
#define GRADUATESTUDENT_H
#include "Student.h"
#include <string>
using namespace std;

class GraduateStudent : public Student
{
private:
    string researchTopic; // Sujet de recherche

public:
    GraduateStudent(const string &name, int id, float gpa, const string &researchTopic);

    void display() const override;
    string getType() const override;
    double computeScholarship() const override;

    // Accesseurs et mutateurs
    string getResearchTopic() const { return researchTopic; }
    void setResearchTopic(const string &topic) { researchTopic = topic; }
};

#endif
