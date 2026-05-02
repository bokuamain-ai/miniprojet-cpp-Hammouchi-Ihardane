#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <memory>
#include "../models/Student.h"

class StudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentDialog(QWidget *parent = nullptr);
    std::shared_ptr<Student> getStudent() const;

private slots:
    void onTypeChanged(const QString &type);
    void validate();

private:
    QComboBox *typeBox;
    QLineEdit *nameEdit;
    QLineEdit *idEdit;
    QDoubleSpinBox *gpaSpinBox;
    QLineEdit *extraEdit1;
    QLineEdit *extraEdit2;
    QLabel *extraLabel1;
    QLabel *extraLabel2;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QFormLayout *formLayout;

    void setupUI();
};

#endif