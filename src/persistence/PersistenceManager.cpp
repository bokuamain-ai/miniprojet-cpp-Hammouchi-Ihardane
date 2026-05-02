#include "PersistenceManager.h"
#include "../models/UndergraduateStudent.h"
#include "../models/GraduateStudent.h"
#include "../models/PhDStudent.h"
#include "../exceptions/StudentExceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void PersistenceManager::save(const StudentManager &mgr, const string &path)
{
    ofstream file(path);
    if (!file.is_open())
    {
        cerr << "Erreur : impossible d'ouvrir le fichier " << path << endl;
        return;
    }
    for (auto &pair : mgr.getAll())
    {
        auto s = pair.second;
        string type = s->getType();
        if (type == "Licence")
        {
            auto u = dynamic_pointer_cast<UndergraduateStudent>(s);
            file << "Licence|" << u->getId() << "|" << u->getName()
                 << "|" << u->getGpa() << "|" << u->getMajor() << "\n";
        }
        else if (type == "Master")
        {
            auto g = dynamic_pointer_cast<GraduateStudent>(s);
            file << "Master|" << g->getId() << "|" << g->getName()
                 << "|" << g->getGpa() << "|" << g->getResearchTopic() << "\n";
        }
        else if (type == "Doctorat")
        {
            auto p = dynamic_pointer_cast<PhDStudent>(s);
            file << "Doctorat|" << p->getId() << "|" << p->getName()
                 << "|" << p->getGpa() << "|" << p->getSupervisor()
                 << "|" << p->getYearOfStudy() << "\n";
        }
    }
    file.close();
    cout << "Donnees sauvegardees dans " << path << endl;
}

void PersistenceManager::load(StudentManager &mgr, const string &path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Fichier absent, demarrage avec liste vide." << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        try
        {
            stringstream ss(line);
            string type, idStr, name, gpaStr;
            getline(ss, type, '|');
            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, gpaStr, '|');
            int id = stoi(idStr);
            float gpa = stof(gpaStr);
            if (type == "Licence")
            {
                string major;
                getline(ss, major, '|');
                mgr.add(make_shared<UndergraduateStudent>(name, id, gpa, major));
            }
            else if (type == "Master")
            {
                string topic;
                getline(ss, topic, '|');
                mgr.add(make_shared<GraduateStudent>(name, id, gpa, topic));
            }
            else if (type == "Doctorat")
            {
                string supervisor, yearStr;
                getline(ss, supervisor, '|');
                getline(ss, yearStr, '|');
                int year = stoi(yearStr);
                mgr.add(make_shared<PhDStudent>(name, id, gpa, supervisor, year));
            }
        }
        catch (...)
        {
        }
    }
    file.close();
    cout << "Donnees chargees depuis " << path << endl;
}