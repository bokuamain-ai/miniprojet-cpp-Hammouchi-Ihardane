#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <string>
#include "../services/StudentManager.h"

class PersistenceManager
{
public:
    static void save(const StudentManager &mgr, const std::string &path);
    static void load(StudentManager &mgr, const std::string &path);
};

#endif