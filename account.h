#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    int accountNumber;
    int pin;
    double balance;

public:
    Account(int accNum, int accountPin, double initialBalance);
    bool validatePIN(int userPIN) const;
    double getBalance() const;
    void credit(double amount);
    bool debit(double amount);
    int getAccountNumber() const;
};

#endif // ACCOUNT_H
