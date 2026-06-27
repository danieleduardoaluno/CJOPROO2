#include "account.h"

Account::Account(int accNum, int accountPin, double initialBalance)
    : accountNumber(accNum), pin(accountPin), balance(initialBalance) {}

bool Account::validatePIN(int userPIN) const {
    return userPIN == pin;
}

double Account::getBalance() const {
    return balance;
}

void Account::credit(double amount) {
    balance += amount;
}

bool Account::debit(double amount) {
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

int Account::getAccountNumber() const {
    return accountNumber;
}
