#include "bankdatabase.h"

BankDatabase::BankDatabase() {
    // Contas criadas automaticamente para testarmos
    accounts.push_back(Account(12345, 1234, 1000.0));
    accounts.push_back(Account(98765, 4321, 5000.0));
}

Account* BankDatabase::getAccount(int accountNumber) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accountNumber) return &acc;
    }
    return nullptr;
}

bool BankDatabase::authenticateUser(int accountNumber, int userPIN) {
    Account* acc = getAccount(accountNumber);
    if (acc != nullptr) return acc->validatePIN(userPIN);
    return false;
}

double BankDatabase::getBalance(int accountNumber) {
    Account* acc = getAccount(accountNumber);
    return acc ? acc->getBalance() : 0.0;
}

bool BankDatabase::debit(int accountNumber, double amount) {
    Account* acc = getAccount(accountNumber);
    return acc ? acc->debit(amount) : false;
}

void BankDatabase::credit(int accountNumber, double amount) {
    Account* acc = getAccount(accountNumber);
    if (acc) acc->credit(amount);
}
