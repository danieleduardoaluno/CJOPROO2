#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "bankdatabase.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void attemptLogin();
    void doWithdrawal();
    void doDeposit();
    void showBalance();
    void logout();

private:
    BankDatabase database;
    int currentAccount;

    QStackedWidget *stackedWidget;
    QLineEdit *accInput;
    QLineEdit *pinInput;
    QLabel *loginStatus;
    QLabel *menuLabel;

    void setupUI();
};

#endif // MAINWINDOW_H
