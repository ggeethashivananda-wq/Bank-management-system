#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(int accNo = 0, string name = "", double bal = 0.0) {
        accountNumber = accNo;
        accountHolder = name;
        balance = bal;
    }

    int getAccountNumber() const { return accountNumber; }
    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited: $" << amount << "\n";
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Successfully withdrew: $" << amount << "\n";
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    void saveToFile() const {
        ofstream file("accounts.txt", ios::app);
        file << accountNumber << "," << accountHolder << "," << balance << "\n";
        file.close();
    }
};

void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();

int main() {
    int choice;
    do {
        cout << "\n==================================\n";
        cout << "      BANK MANAGEMENT SYSTEM      \n";
        cout << "==================================\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: cout << "Exiting system. Thank you!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void createAccount() {
    int accNo;
    string name;
    double initialBalance;

    cout << "\nEnter Account Number: ";
    cin >> accNo;
    cin.ignore();
    cout << "Enter Account Holder Name: ";
    getline(cin, name);
    cout << "Enter Initial Deposit: ";
    cin >> initialBalance;

    BankAccount acc(accNo, name, initialBalance);
    acc.saveToFile();
    cout << "Account created successfully!\n";
}

void depositMoney() {
    int searchAcc;
    double amount;
    cout << "\nEnter Account Number: ";
    cin >> searchAcc;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string accNoStr, name, balStr;
        getline(ss, accNoStr, ',');
        getline(ss, name, ',');
        getline(ss, balStr, ',');

        int accNo = stoi(accNoStr);
        double balance = stod(balStr);

        if (accNo == searchAcc) {
            balance += amount;
            cout << "Successfully deposited $" << amount << ". New Balance: $" << balance << "\n";
            found = true;
        }
        temp << accNo << "," << name << "," << balance << "\n";
    }
    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found!\n";
}

void withdrawMoney() {
    int searchAcc;
    double amount;
    cout << "\nEnter Account Number: ";
    cin >> searchAcc;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string accNoStr, name, balStr;
        getline(ss, accNoStr, ',');
        getline(ss, name, ',');
        getline(ss, balStr, ',');

        int accNo = stoi(accNoStr);
        double balance = stod(balStr);

        if (accNo == searchAcc) {
            if (balance >= amount) {
                balance -= amount;
                cout << "Successfully withdrew $" << amount << ". New Balance: $" << balance << "\n";
            } else {
                cout << "Insufficient balance!\n";
            }
            found = true;
        }
        temp << accNo << "," << name << "," << balance << "\n";
    }
    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) cout << "Account not found!\n";
}

void checkBalance() {
    int searchAcc;
    cout << "\nEnter Account Number: ";
    cin >> searchAcc;

    ifstream file("accounts.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string accNoStr, name, balStr;
        getline(ss, accNoStr, ',');
        getline(ss, name, ',');
        getline(ss, balStr, ',');

        if (stoi(accNoStr) == searchAcc) {
            cout << "\n--- Account Details ---\n";
            cout << "Account Holder: " << name << "\n";
            cout << "Current Balance: $" << balStr << "\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Account not found!\n";
}
