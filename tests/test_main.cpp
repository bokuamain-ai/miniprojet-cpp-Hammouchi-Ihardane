#include <iostream>
#include <cassert>
#include "../src/models/UndergraduateStudent.h"
#include "../src/models/GraduateStudent.h"
#include "../src/models/PhDStudent.h"
#include "../src/services/StudentManager.h"
#include "../src/exceptions/StudentExceptions.h"
#include "../src/persistence/PersistenceManager.h"
using namespace std;

int passed = 0;
int failed = 0;

void test(const string &name, bool condition)
{
    if (condition)
    {
        cout << "[OK]   " << name << endl;
        passed++;
    }
    else
    {
        cout << "[FAIL] " << name << endl;
        failed++;
    }
}

int main()
{
    cout << "====== TESTS DU PROJET ======\n"
         << endl;

    // ── Partie 1 : OOP ──
    cout << "--- Test OOP ---" << endl;

    UndergraduateStudent u("Benali Amira", 1001, 3.8, "Informatique");
    test("Undergraduate getType()", u.getType() == "Licence");
    test("Undergraduate bourse 500", u.computeScholarship() == 500.0);

    UndergraduateStudent u2("Ziani Sara", 1002, 2.9, "Maths");
    test("Undergraduate bourse 0", u2.computeScholarship() == 0.0);

    GraduateStudent g("Cherif Omar", 1003, 3.5, "IA");
    test("Graduate getType()", g.getType() == "Master");
    test("Graduate bourse GPA*300", g.computeScholarship() == 3.5 * 300);

    PhDStudent p("Meziane Riad", 1004, 3.9, "Dr. Hadj", 2);
    test("PhD getType()", p.getType() == "Doctorat");
    test("PhD bourse 1200", p.computeScholarship() == 1200.0);

    // ── Partie 2 : STL ──
    cout << "\n--- Test STL ---" << endl;

    StudentManager mgr;
    mgr.add(make_shared<UndergraduateStudent>("Benali Amira", 1001, 3.8, "Informatique"));
    mgr.add(make_shared<GraduateStudent>("Cherif Omar", 1002, 3.5, "IA"));
    mgr.add(make_shared<PhDStudent>("Meziane Riad", 1003, 3.9, "Dr. Hadj", 2));
    mgr.add(make_shared<UndergraduateStudent>("Ziani Sara", 1004, 2.9, "Maths"));
    mgr.add(make_shared<GraduateStudent>("Ait Ali Karim", 1005, 3.2, "Reseaux"));

    test("Count 5 etudiants", mgr.count() == 5);
    test("FindById 1001", mgr.findById(1001)->getName() == "Benali Amira");
    test("FindByName 'ali'", mgr.findByName("ali").size() >= 1);

    auto byGpa = mgr.sortByGpa();
    test("SortByGpa decroissant", byGpa[0]->getGpa() >= byGpa[1]->getGpa());

    auto byName = mgr.sortByName();
    test("SortByName alphabetique", byName[0]->getName() <= byName[1]->getName());

    test("AverageGpa > 0", mgr.averageGpa() > 0);

    mgr.remove(1002);
    test("Remove - count 4", mgr.count() == 4);

    // ── Partie 3 : Exceptions ──
    cout << "\n--- Test Exceptions ---" << endl;

    bool caught = false;
    try
    {
        mgr.add(make_shared<UndergraduateStudent>("Test", 42, 3.0, "Info"));
    }
    catch (const InvalidIDException &)
    {
        caught = true;
    }
    test("InvalidIDException (id=42)", caught);

    caught = false;
    try
    {
        mgr.add(make_shared<UndergraduateStudent>("Test", 1010, 5.5, "Info"));
    }
    catch (const InvalidGradeException &)
    {
        caught = true;
    }
    test("InvalidGradeException (gpa=5.5)", caught);

    caught = false;
    try
    {
        mgr.add(make_shared<UndergraduateStudent>("Double", 1001, 3.0, "Info"));
    }
    catch (const DuplicateIDException &)
    {
        caught = true;
    }
    test("DuplicateIDException (id=1001)", caught);

    caught = false;
    try
    {
        mgr.remove(9999);
    }
    catch (const StudentNotFoundException &)
    {
        caught = true;
    }
    test("StudentNotFoundException (9999)", caught);

    // ── Partie 4 : Persistance ──
    cout << "\n--- Test Persistance ---" << endl;

    StudentManager mgr2;
    mgr2.add(make_shared<UndergraduateStudent>("Test Save", 2001, 3.5, "Info"));
    PersistenceManager::save(mgr2, "data/test_save.txt");

    StudentManager mgr3;
    PersistenceManager::load(mgr3, "data/test_save.txt");
    test("Save et reload", mgr3.count() == 1);
    test("Donnees identiques", mgr3.findById(2001)->getName() == "Test Save");

    // ── Résumé ──
    cout << "\n=============================" << endl;
    cout << "PASSED : " << passed << endl;
    cout << "FAILED : " << failed << endl;
    cout << "=============================" << endl;

    return 0;
}