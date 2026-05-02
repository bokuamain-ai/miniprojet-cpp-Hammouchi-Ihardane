#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include "../models/Student.h"

class StudentManager
{
private:
    std::map<int, std::shared_ptr<Student>> students; // ID → Étudiant

public:
    void add(std::shared_ptr<Student> s);
    void remove(int id);
    void update(int id, std::shared_ptr<Student> updated);

    std::shared_ptr<Student> findById(int id) const;
    std::vector<std::shared_ptr<Student>> findByName(const std::string &n) const;

    std::vector<std::shared_ptr<Student>> sortByGpa() const;
    std::vector<std::shared_ptr<Student>> sortByName() const;

    double averageGpa() const;
    int count() const { return students.size(); }

    const std::map<int, std::shared_ptr<Student>> &getAll() const { return students; }
};

#endif