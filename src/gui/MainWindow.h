#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../services/StudentManager.h"
#include "../persistence/PersistenceManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addStudent();
    void editStudent();
    void deleteStudent();
    void refreshTable();
    void searchStudents(const QString &text);

private:
    StudentManager manager;
    QTableWidget *table;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QLineEdit *searchBox;

    void setupUI();
    void updateStatusBar();
};

#endif