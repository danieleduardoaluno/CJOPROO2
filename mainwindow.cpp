#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentAccount(0) {
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    this->setWindowTitle("Caixa Eletrônico - ATM");
    this->resize(450, 350);

    stackedWidget = new QStackedWidget(this);
    this->setCentralWidget(stackedWidget);

    // --- TELA 1: LOGIN ---
    QWidget *loginWidget = new QWidget();
    QVBoxLayout *loginLayout = new QVBoxLayout(loginWidget);

    QLabel *title = new QLabel("<h2>Bem-vindo</h2>Insira os dados do cartão:");
    title->setAlignment(Qt::AlignCenter);

    accInput = new QLineEdit();
    accInput->setPlaceholderText("Número da Conta (ex: 12345)");

    pinInput = new QLineEdit();
    pinInput->setPlaceholderText("Senha de 4 dígitos (ex: 1234)");
    pinInput->setEchoMode(QLineEdit::Password);

    QPushButton *btnLogin = new QPushButton("Entrar");
    loginStatus = new QLabel("");
    loginStatus->setStyleSheet("color: red;");
    loginStatus->setAlignment(Qt::AlignCenter);

    loginLayout->addStretch();
    loginLayout->addWidget(title);
    loginLayout->addWidget(accInput);
    loginLayout->addWidget(pinInput);
    loginLayout->addWidget(btnLogin);
    loginLayout->addWidget(loginStatus);
    loginLayout->addStretch();

    // --- TELA 2: MENU PRINCIPAL ---
    QWidget *menuWidget = new QWidget();
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);

    menuLabel = new QLabel("Conta Ativa");
    menuLabel->setAlignment(Qt::AlignCenter);

    QPushButton *btnWithdraw = new QPushButton("Sacar R$ 50,00");
    QPushButton *btnDeposit = new QPushButton("Depositar R$ 100,00");
    QPushButton *btnBalance = new QPushButton("Ver Saldo");
    QPushButton *btnLogout = new QPushButton("Retirar Cartão (Sair)");

    menuLayout->addStretch();
    menuLayout->addWidget(menuLabel);
    menuLayout->addWidget(btnWithdraw);
    menuLayout->addWidget(btnDeposit);
    menuLayout->addWidget(btnBalance);
    menuLayout->addWidget(btnLogout);
    menuLayout->addStretch();

    // Adicionando as telas ao StackedWidget
    stackedWidget->addWidget(loginWidget); // Index 0
    stackedWidget->addWidget(menuWidget);  // Index 1

    // Sinais e Slots (Eventos de Clique)
    connect(btnLogin, &QPushButton::clicked, this, &MainWindow::attemptLogin);
    connect(btnWithdraw, &QPushButton::clicked, this, &MainWindow::doWithdrawal);
    connect(btnDeposit, &QPushButton::clicked, this, &MainWindow::doDeposit);
    connect(btnBalance, &QPushButton::clicked, this, &MainWindow::showBalance);
    connect(btnLogout, &QPushButton::clicked, this, &MainWindow::logout);
}

void MainWindow::attemptLogin() {
    int acc = accInput->text().toInt();
    int pin = pinInput->text().toInt();

    if (database.authenticateUser(acc, pin)) {
        currentAccount = acc;
        loginStatus->setText("");
        pinInput->clear();
        menuLabel->setText("<h2>Sessão Ativa</h2>Conta: " + QString::number(acc));
        stackedWidget->setCurrentIndex(1); // Vai para o Menu
    } else {
        loginStatus->setText("Conta ou Senha incorretos!");
    }
}

void MainWindow::doWithdrawal() {
    if (database.debit(currentAccount, 50.0)) {
        QMessageBox::information(this, "Sucesso", "Saque de R$ 50,00 aprovado.\nRetire as notas no local indicado.");
    } else {
        QMessageBox::warning(this, "Erro", "Saldo insuficiente para este saque.");
    }
}

void MainWindow::doDeposit() {
    database.credit(currentAccount, 100.0);
    QMessageBox::information(this, "Sucesso", "Depósito de R$ 100,00 recebido!");
}

void MainWindow::showBalance() {
    double balance = database.getBalance(currentAccount);
    QMessageBox::information(this, "Saldo", "Seu saldo atual é:\n\nR$ " + QString::number(balance, 'f', 2));
}

void MainWindow::logout() {
    currentAccount = 0;
    accInput->clear();
    pinInput->clear();
    stackedWidget->setCurrentIndex(0); // Volta para a tela de login
    QMessageBox::information(this, "Sessão Encerrada", "Obrigado por utilizar nosso banco.\nSeu cartão foi ejetado.");
}
