#ifndef BANKDATABASE_H
#define BANKDATABASE_H

#include "account.h"
#include <vector>

class BankDatabase {
private:
    std::vector<Account> accounts;
    Account* getAccount(int accountNumber);

public:
    BankDatabase();
    bool authenticateUser(int accountNumber, int userPIN);
    double getBalance(int accountNumber);
    bool debit(int accountNumber, double amount);
    void credit(int accountNumber, double amount);
};

#endif // BANKDATABASE_H
