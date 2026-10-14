#include <iostream>

bool equal(const char* first, const char* second) {
    int i = 0;
    while (first[i] && second[i]) {
        if (first[i] != second[i])
            return false;
        i++;
    }
    return first[i] == second[i];
}

void deposit(int& balance, int amount) {
    if (amount <= 0)
        std::cout << "error\n";
    else
        balance += amount;
}

void withdraw(int& balance, int amount) {
    if (amount <= 0 || amount > balance)
        std::cout << "error\n";
    else
        balance -= amount;
}

void showBalance(int& balance, int) {
    std::cout << balance << '\n';
}

void reset(int& balance, int) {
    balance = 0;
}

void doubleBalance(int& balance, int) {
    balance *= 2;
}

int main() {
    int balance = 0;
    char command[100];
    int amount;

    const char* names[] = {
        "deposit", "withdraw", "balance", "reset", "double"
    };

    void (*operations[])(int&, int) = {
        deposit, withdraw, showBalance, reset, doubleBalance
    };

    while (std::cin >> command) {
        if (equal(command, "stop"))
            break;

        int operation = -1;

        for (int i = 0; i < 5; i++) {
            if (equal(command, names[i])) {
                operation = i;
                break;
            }
        }

        if (operation == -1) {
            std::cout << "error\n";
            continue;
        }

        if (operation < 2) {
            if (!(std::cin >> amount))
                break;
            operations[operation](balance, amount);
        } else {
            operations[operation](balance, 0);
        }
    }

    return 0;
}
