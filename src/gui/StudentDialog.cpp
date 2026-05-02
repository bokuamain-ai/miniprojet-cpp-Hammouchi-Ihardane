#include "StudentDialog.h"
#include "../models/UndergraduateStudent.h"
#include "../models/GraduateStudent.h"
#include "../models/PhDStudent.h"
#include "../exceptions/StudentExceptions.h"
#include <QMessageBox>
#include <QVBoxLayout>
using namespace std;

StudentDialog::StudentDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();
}

void StudentDialog::setupUI()
{
    setWindowTitle("Ajouter / Modifier un etudiant");
    setMinimumWidth(400);

    formLayout = new QFormLayout();

    typeBox = new QComboBox();
    typeBox->addItems({"Licence", "Master", "Doctorat"});

    nameEdit = new QLineEdit();
    idEdit = new QLineEdit();

    gpaSpinBox = new QDoubleSpinBox();
    gpaSpinBox->setRange(0.0, 4.0);
    gpaSpinBox->setSingleStep(0.1);
    gpaSpinBox->setDecimals(1);

    extraLabel1 = new QLabel("Filiere:");
    extraEdit1 = new QLineEdit();
    extraLabel2 = new QLabel("");
    extraEdit2 = new QLineEdit();
    extraEdit2->hide();
    extraLabel2->hide();

    formLayout->addRow("Type:", typeBox);
    formLayout->addRow("Nom:", nameEdit);
    formLayout->addRow("ID:", idEdit);
    formLayout->addRow("GPA:", gpaSpinBox);
    formLayout->addRow(extraLabel1, extraEdit1);
    formLayout->addRow(extraLabel2, extraEdit2);

    btnOk = new QPushButton("Valider");
    btnCancel = new QPushButton("Annuler");
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    connect(typeBox, &QComboBox::currentTextChanged, this, &StudentDialog::onTypeChanged);
    connect(btnOk, &QPushButton::clicked, this, &StudentDialog::validate);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

void StudentDialog::onTypeChanged(const QString &type)
{
    if (type == "Licence")
    {
        extraLabel1->setText("Filiere:");
        extraEdit1->setPlaceholderText("ex: Informatique");
        extraEdit2->hide();
        extraLabel2->hide();
    }
    else if (type == "Master")
    {
        extraLabel1->setText("Sujet de recherche:");
        extraEdit1->setPlaceholderText("ex: Intelligence Artificielle");
        extraEdit2->hide();
        extraLabel2->hide();
    }
    else if (type == "Doctorat")
    {
        extraLabel1->setText("Superviseur:");
        extraEdit1->setPlaceholderText("ex: Dr. Hadj");
        extraLabel2->setText("Annee:");
        extraEdit2->setPlaceholderText("ex: 2");
        extraEdit2->show();
        extraLabel2->show();
    }
}

void StudentDialog::validate()
{
    if (nameEdit->text().isEmpty() || idEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Nom et ID obligatoires.");
        return;
    }
    accept();
}

shared_ptr<Student> StudentDialog::getStudent() const
{
    string name = nameEdit->text().toStdString();
    int id = idEdit->text().toInt();
    float gpa = (float)gpaSpinBox->value();
    string type = typeBox->currentText().toStdString();

    if (type == "Licence")
    {
        string major = extraEdit1->text().toStdString();
        return make_shared<UndergraduateStudent>(name, id, gpa, major);
    }
    else if (type == "Master")
    {
        string topic = extraEdit1->text().toStdString();
        return make_shared<GraduateStudent>(name, id, gpa, topic);
    }
    else
    {
        string supervisor = extraEdit1->text().toStdString();
        int year = extraEdit2->text().toInt();
        return make_shared<PhDStudent>(name, id, gpa, supervisor, year);
    }
}