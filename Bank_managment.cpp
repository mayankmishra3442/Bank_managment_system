#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Function to set text color to red (for error messages)
void red() { cout << "\033[31m"; }

// Bank Account class
class BankAccount {
private:
    string bankName = "Bank of Baroda";
    int bankcode;
    string accountHolderName;
    string accountNumber;
    string accountPassword;
    string adharnumber;
    string email;
    string phoneNumber;
    double balance;
    vector<string> transactionHistory;

public:
    void saveToFile();
    void loadFromFile();
    void mainMenu();
    void createAccount();
    void loginBankAccount();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void accountDetails();
    void allTransactionHistory();
};

// Save account details to a file
void BankAccount::saveToFile() {
    ofstream file(accountNumber + ".txt");
    if (file.is_open()) {
        file << accountHolderName << endl;
        file << accountNumber << endl;
        file << accountPassword << endl;
        file << adharnumber << endl;
        file << email << endl;
        file << phoneNumber << endl;
        file << balance << endl;
        for (const auto& transaction : transactionHistory) {
            file << transaction << endl;
        }
        file.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}

// Load account details from a file
void BankAccount::loadFromFile() {
    ifstream file(accountNumber + ".txt");
    if (file.is_open()) {
        getline(file, accountHolderName);
        getline(file, accountNumber);
        getline(file, accountPassword);
        getline(file, adharnumber);
        getline(file, email);
        getline(file, phoneNumber);
        file >> balance;
        file.ignore();
        string transaction;
        transactionHistory.clear();
        while (getline(file, transaction)) {
            transactionHistory.push_back(transaction);
        }
        file.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}

// Create new account
void BankAccount::createAccount() {
    cout << "\n------- Create Account -------\n";
    cout << "Enter your Full Name: ";
    getline(cin, accountHolderName);
    cout << "Enter Email ID: ";
    getline(cin, email);
    cout << "Enter Phone Number: ";
    getline(cin, phoneNumber);
    cout << "Enter Aadhar Number: ";
    getline(cin, adharnumber);
    cout << "Enter Password: ";
    getline(cin, accountPassword);

    balance = 500.00;

    ifstream file("Bank-Code.txt");
    if (file.is_open()) {
        file >> bankcode;
        file.close();
    } else {
        bankcode = 1000;  // Default starting code
    }

    accountNumber =  to_string(bankcode);
    transactionHistory.push_back("Initial Deposit: Rs =" + to_string(balance));

    ofstream output("Bank-Code.txt");
    if (output.is_open()) {
        output << bankcode + 1;
        output.close();
    }

    cout << "Your account number is: " << accountNumber << endl;
}

// User login
void BankAccount::loginBankAccount() {
    string accNo, pass;
    cout << "\n------- Login to Your Account -------\n";
    cout << "Enter Account Number: ";
    getline(cin, accNo);
    cout << "Enter Password: ";
    getline(cin, pass);

    ifstream file(accNo + ".txt");
    if (!file.is_open()) {
        red(); cout << "Account not found.\n";
        return;
    }

    string tempName, tempAccNo, tempPass;
    getline(file, tempName);
    getline(file, tempAccNo);
    getline(file, tempPass);

    if (pass != tempPass) {
        red(); cout << "Incorrect password.\n";
        file.close();
        return;
    }

    accountHolderName = tempName;
    accountNumber = tempAccNo;
    accountPassword = tempPass;

    getline(file, adharnumber);
    getline(file, email);
    getline(file, phoneNumber);
    file >> balance;
    file.ignore();

    string transaction;
    transactionHistory.clear();
    while (getline(file, transaction)) {
        transactionHistory.push_back(transaction);
    }

    file.close();
    cout << "\nLogin successful. Welcome " << accountHolderName << "!\n";
    mainMenu();
}

// Menu after login
void BankAccount::mainMenu() {
    int choice;
    do {
        cout << "\n------- Main Menu -------\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Account Details\n";
        cout << "4. Check Balance\n";
        cout << "5. All Transaction History\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: depositMoney(); break;
            case 2: withdrawMoney(); break;
            case 3: accountDetails(); break;
            case 4: checkBalance(); break;
            case 5: allTransactionHistory(); break;
            case 6: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}

// Deposit
void BankAccount::depositMoney() {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    if (amount > 0) {
        balance += amount;
        transactionHistory.push_back("Deposited: Rs = " + to_string(amount));
        cout << "Deposited ₹" << amount << " successfully.\n";
        saveToFile();
    } else {
        red(); cout << "Invalid deposit amount.\n";
    }
}

// Withdraw
void BankAccount::withdrawMoney() {
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        transactionHistory.push_back("Withdrawn: Rs =" + to_string(amount));
        cout << "Withdrawn ₹" << amount << " successfully.\n";
        saveToFile();
    } else {
        red(); cout << "Invalid amount or insufficient balance.\n";
    }
}

// Balance check
void BankAccount::checkBalance() {
    cout << "Your current balance is ₹" << balance << endl;
}

// Account details
void BankAccount::accountDetails() {
    cout << "\n------- Account Details -------\n";
    cout << "Account Holder: " << accountHolderName << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Email: " << email << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Aadhar Number: " << adharnumber << endl;
}

// All transactions
void BankAccount::allTransactionHistory() {
    cout << "\n------- Transaction History -------\n";
    for (const auto& txn : transactionHistory) {
        cout << "- " << txn << endl;
    }
}

// Main function
int main() {
    BankAccount account;
    int choice;

    cout << "======= Welcome to Bank Management System =======\n";
    cout << "1. Create New Account\n";
    cout << "2. Login to Existing Account\n";
    cout << "=================================================\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            account.createAccount();
            account.saveToFile();
            account.mainMenu();
            break;
        case 2:
            account.loginBankAccount();
            break;
        default:
            cout << "Invalid choice!\n";
    }

    return 0;
}