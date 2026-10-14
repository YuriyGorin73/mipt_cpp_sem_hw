#include <iostream>

void deposit(int& balance, int amount) {
    if (amount <= 0) {
        std::cout << "error\n";
        return;
    }
    balance += amount;
}

void withdraw(int& balance, int amount) {
    if (amount <= 0 || amount > balance) {
        std::cout << "error\n";
        return;
    }
    balance -= amount;
}

void showBalance(int& balance) {
    std::cout << balance << '\n';
}

void reset(int& balance) {
    balance = 0;
}

void doubleBalance(int& balance) {
    balance *= 2;
}

int main() {
    int balance = 0;
    char command[20];

    void (*operations[])(int&) = {showBalance, reset, doubleBalance};

    while (std::cin >> command) {
        if (command[0] == 's' && command[1] == 't')
            break;

        if (command[0] == 'b') {
            showBalance(balance);
        } else if (command[0] == 'r') {
            reset(balance);
        } else if (command[0] == 'd' && command[1] == 'o') {
            int amount;
            std::cin >> amount;
            deposit(balance, amount);
        } else if (command[0] == 'w') {
            int amount;
            std::cin >> amount;
            withdraw(balance, amount);
        } else if (command[0] == 'd' && command[1] == 'o') {
            doubleBalance(balance);
        } else {
            std::cout << "error\n";
        }
    }

    return 0;
}
