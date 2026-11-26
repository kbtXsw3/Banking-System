#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Maximum number of users
const int MAX_USERS = 3;

// User account details stored in arrays
string names[MAX_USERS] = {
    "John Smith",
    "Mary Jones",
    "David Brown"
};

int accountNumbers[MAX_USERS] = {
    1001, 1002, 1003
};

int pins[MAX_USERS] = {
    1234, 2345, 3456
};

double balances[MAX_USERS] = {
    5000.00, 3000.00, 2500.00
};

// Function declarations
void displayMenu();
int findAccount(int accountNumber);
bool login(int userIndex);
void deposit(int userIndex);
void withdraw(int userIndex);
void sendCash(int userIndex);
void checkBalance(int userIndex);
void displayUserDetails();

// Display banking menu
void displayMenu() {
    cout << "\n====================================\n";
    cout << "       COMMAND LINE BANKING SYSTEM\n";
    cout << "====================================\n";
    cout << "1. Deposit Money\n";
    cout << "2. Withdraw Money\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. User Details\n";
    cout << "6. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

// Find an account using its account number
int findAccount(int accountNumber) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (accountNumbers[i] == accountNumber) {
            return i;
        }
    }
    return -1;
}

// Login function
bool login(int userIndex) {
    int enteredPIN;

    cout << "Enter your PIN: ";
    cin >> enteredPIN;

    if (enteredPIN == pins[userIndex]) {
        cout << "\nLogin successful!";
        cout << "\nWelcome, " << names[userIndex] << "!\n";
        return true;
    }
    else {
        cout << "\nIncorrect PIN. Access denied.\n";
        return false;
    }
}

// Deposit function
void deposit(int userIndex) {
    double amount;

    cout << "\nEnter amount to deposit: R";
    cin >> amount;

    if (amount > 0) {
        balances[userIndex] += amount;

        cout << "Deposit successful!";
        cout << "\nNew balance: R"
             << balances[userIndex] << endl;
    }
    else {
        cout << "Invalid amount! Deposit must be greater than zero.\n";
    }
}

// Withdraw function
void withdraw(int userIndex) {
    double amount;

    cout << "\nEnter amount to withdraw: R";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount! Enter an amount greater than zero.\n";
    }
    else if (amount > balances[userIndex]) {
        cout << "Insufficient balance! Withdrawal denied.\n";
    }
    else {
        balances[userIndex] -= amount;

        cout << "Withdrawal successful!";
        cout << "\nRemaining balance: R"
             << balances[userIndex] << endl;
    }
}

// Send cash function
void sendCash(int userIndex) {
    int receiverAccount;
    double amount;

    cout << "\nEnter receiver account number: ";
    cin >> receiverAccount;

    int receiverIndex = findAccount(receiverAccount);

    if (receiverIndex == -1) {
        cout << "Error! Account number does not exist.\n";
        return;
    }

    if (receiverIndex == userIndex) {
        cout << "You cannot transfer money to your own account.\n";
        return;
    }

    cout << "Enter amount to send: R";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid transfer amount!\n";
    }
    else if (amount > balances[userIndex]) {
        cout << "Insufficient balance! Transfer cancelled.\n";
    }
    else {
        balances[userIndex] -= amount;
        balances[receiverIndex] += amount;

        cout << "\nTransfer successful!";
        cout << "\nSent to: " << names[receiverIndex];
        cout << "\nAmount sent: R" << amount;
        cout << "\nRemaining balance: R"
             << balances[userIndex] << endl;
    }
}

// Check balance function
void checkBalance(int userIndex) {
    cout << "\n========== ACCOUNT BALANCE ==========\n";
    cout << "Account holder: " << names[userIndex] << endl;
    cout << "Account number: " << accountNumbers[userIndex] << endl;
    cout << "Available balance: R"
         << fixed << setprecision(2)
         << balances[userIndex] << endl;
    cout << "=====================================\n";
}

// Display registered user details
void displayUserDetails() {
    cout << "\n========== REGISTERED USERS ==========\n";

    for (int i = 0; i < MAX_USERS; i++) {
        cout << "\nName: " << names[i];
        cout << "\nAccount Number: " << accountNumbers[i];
        cout << "\nBalance: R"
             << fixed << setprecision(2)
             << balances[i] << endl;
    }

    cout << "======================================\n";
}

// Main function
int main() {
    int accountNumber;
    int choice;
    char anotherUser;

    cout << "====================================\n";
    cout << "       WELCOME TO OUR BANK\n";
    cout << "====================================\n";

    do {
        cout << "\nEnter your account number: ";
        cin >> accountNumber;

        int userIndex = findAccount(accountNumber);

        if (userIndex == -1) {
            cout << "Invalid account number! Please try again.\n";
            continue;
        }

        if (!login(userIndex)) {
            continue;
        }

        // Banking menu loop
        do {
            displayMenu();
            cin >> choice;

            switch (choice) {

            case 1:
                deposit(userIndex);
                break;

            case 2:
                withdraw(userIndex);
                break;

            case 3:
                sendCash(userIndex);
                break;

            case 4:
                checkBalance(userIndex);
                break;

            case 5:
                displayUserDetails();
                break;

            case 6:
                cout << "\nThank you for banking with us!\n";
                break;

            default:
                cout << "\nInvalid menu choice! Please select 1-6.\n";
            }

        } while (choice != 6);

        cout << "\nWould another user like to login? (Y/N): ";
        cin >> anotherUser;

    } while (anotherUser == 'Y' || anotherUser == 'y');

    cout << "\nBanking system closed successfully.\n";

    return 0;
}
