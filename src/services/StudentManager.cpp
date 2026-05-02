#include "StudentManager.h"
#include <stdexcept>
#include <cctype>
using namespace std;

void StudentManager::add(shared_ptr<Student> s)
{
    if (students.count(s->getId()))
    {
        throw runtime_error("ID deja utilise : " + to_string(s->getId()));
    }
    students[s->getId()] = s;
}

void StudentManager::remove(int id)
{
    if (!students.count(id))
    {
        throw runtime_error("Etudiant introuvable avec ID : " + to_string(id));
    }
    students.erase(id);
}

void StudentManager::update(int id, shared_ptr<Student> updated)
{
    if (!students.count(id))
    {
        throw runtime_error("Etudiant introuvable avec ID : " + to_string(id));
    }
    students[id] = updated;
}

shared_ptr<Student> StudentManager::findById(int id) const
{
    auto it = students.find(id);
    if (it == students.end())
    {
        throw runtime_error("Etudiant introuvable avec ID : " + to_string(id));
    }
    return it->second;
}

vector<shared_ptr<Student>> StudentManager::findByName(const string &n) const
{
    vector<shared_ptr<Student>> result;
    string nLower = n;
    for (char &c : nLower)
        c = tolower(c);
    for (auto &pair : students)
    {
        string nameLower = pair.second->getName();
        for (char &c : nameLower)
            c = tolower(c);
        if (nameLower.find(nLower) != string::npos)
        {
            result.push_back(pair.second);
        }
    }
    return result;
}

vector<shared_ptr<Student>> StudentManager::sortByGpa() const
{
    vector<shared_ptr<Student>> vec;
    for (auto &pair : students)
        vec.push_back(pair.second);
    sort(vec.begin(), vec.end(), [](const shared_ptr<Student> &a, const shared_ptr<Student> &b)
         { return a->getGpa() > b->getGpa(); });
    return vec;
}

vector<shared_ptr<Student>> StudentManager::sortByName() const
{
    vector<shared_ptr<Student>> vec;
    for (auto &pair : students)
        vec.push_back(pair.second);
    sort(vec.begin(), vec.end(), [](const shared_ptr<Student> &a, const shared_ptr<Student> &b)
         {
        string na = a->getName(), nb = b->getName();
        for (char& c : na) c = tolower(c);
        for (char& c : nb) c = tolower(c);
        return na < nb; });
    return vec;
}

double StudentManager::averageGpa() const
{
    if (students.empty())
        return 0.0;
    double total = 0;
    for (auto &pair : students)
        total += pair.second->getGpa();
    return total / students.size();
}