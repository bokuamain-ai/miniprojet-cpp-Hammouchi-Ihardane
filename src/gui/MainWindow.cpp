#include "MainWindow.h"
#include "StudentDialog.h"
#include "../exceptions/StudentExceptions.h"
#include "../models/UndergraduateStudent.h"
#include "../models/GraduateStudent.h"
#include "../models/PhDStudent.h"
#include <QMessageBox>
#include <QHeaderView>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUI();
    PersistenceManager::load(manager, "data/students.txt");
    refreshTable();
}

MainWindow::~MainWindow()
{
    PersistenceManager::save(manager, "data/students.txt");
}

void MainWindow::setupUI()
{
    setWindowTitle("Gestion des Etudiants");
    resize(900, 600);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Barre de recherche
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Rechercher un etudiant...");
    searchLayout->addWidget(new QLabel("Recherche:"));
    searchLayout->addWidget(searchBox);
    mainLayout->addLayout(searchLayout);

    // Tableau
    table = new QTableWidget();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"ID", "Nom", "Type", "GPA", "Bourse (EUR)"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(table);

    // Boutons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnAdd = new QPushButton("+ Ajouter");
    btnEdit = new QPushButton("Modifier");
    btnDelete = new QPushButton("Supprimer");
    QPushButton *btnRefresh = new QPushButton("Rafraichir");
    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnEdit);
    btnLayout->addWidget(btnDelete);
    btnLayout->addWidget(btnRefresh);
    mainLayout->addLayout(btnLayout);

    // Connexions
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::addStudent);
    connect(btnEdit, &QPushButton::clicked, this, &MainWindow::editStudent);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::deleteStudent);
    connect(btnRefresh, &QPushButton::clicked, this, &MainWindow::refreshTable);
    connect(searchBox, &QLineEdit::textChanged, this, &MainWindow::searchStudents);

    statusBar()->showMessage("Pret");
}

void MainWindow::refreshTable()
{
    table->setRowCount(0);
    for (auto &pair : manager.getAll())
    {
        auto s = pair.second;
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(s->getId())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s->getName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s->getType())));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(s->getGpa(), 'f', 1)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(s->computeScholarship(), 'f', 0)));
    }
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    QString msg = QString("Etudiants: %1  |  Moyenne GPA: %2")
                      .arg(manager.count())
                      .arg(manager.averageGpa(), 0, 'f', 2);
    statusBar()->showMessage(msg);
}

void MainWindow::addStudent()
{
    StudentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        try
        {
            manager.add(dialog.getStudent());
            PersistenceManager::save(manager, "data/students.txt");
            refreshTable();
            statusBar()->showMessage("Etudiant ajoute avec succes.", 3000);
        }
        catch (const DuplicateIDException &e)
        {
            QMessageBox::critical(this, "Erreur ID", QString(e.what()));
        }
        catch (const InvalidIDException &e)
        {
            QMessageBox::critical(this, "Erreur ID", QString(e.what()));
        }
        catch (const InvalidGradeException &e)
        {
            QMessageBox::warning(this, "Erreur GPA", QString(e.what()));
        }
    }
}

void MainWindow::editStudent()
{
    int row = table->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "Attention", "Selectionnez un etudiant.");
        return;
    }
    int id = table->item(row, 0)->text().toInt();
    StudentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        try
        {
            manager.update(id, dialog.getStudent());
            PersistenceManager::save(manager, "data/students.txt");
            refreshTable();
            statusBar()->showMessage("Etudiant modifie.", 3000);
        }
        catch (const exception &e)
        {
            QMessageBox::critical(this, "Erreur", QString(e.what()));
        }
    }
}

void MainWindow::deleteStudent()
{
    int row = table->currentRow();
    if (row < 0)
    {
        QMessageBox::warning(this, "Attention", "Selectionnez un etudiant.");
        return;
    }
    int id = table->item(row, 0)->text().toInt();
    auto reply = QMessageBox::question(this, "Confirmation",
                                       "Supprimer cet etudiant ?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        try
        {
            manager.remove(id);
            PersistenceManager::save(manager, "data/students.txt");
            refreshTable();
            statusBar()->showMessage("Etudiant supprime.", 3000);
        }
        catch (const StudentNotFoundException &e)
        {
            QMessageBox::critical(this, "Erreur", QString(e.what()));
        }
    }
}

void MainWindow::searchStudents(const QString &text)
{
    string query = text.toStdString();
    table->setRowCount(0);
    auto results = query.empty() ? [&]()
    {
        vector<shared_ptr<Student>> all;
        for (auto &p : manager.getAll())
            all.push_back(p.second);
        return all;
    }()
                                 : manager.findByName(query);

    for (auto &s : results)
    {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(s->getId())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(s->getName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(s->getType())));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(s->getGpa(), 'f', 1)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(s->computeScholarship(), 'f', 0)));
    }
}