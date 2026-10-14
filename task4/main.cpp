#include <iostream>

int main() {
    // int*** хранит несколько двумерных массивов.
    // void* хранит адрес элемента без указания его типа.
    // Программа создаёт массивы, меняет один элемент и выводит их содержимое.

    int*** warehouses = new int**[3];

    for (int warehouse = 0; warehouse < 3; warehouse++) {
        warehouses[warehouse] = new int*[2];

        for (int row = 0; row < 2; row++) {
            warehouses[warehouse][row] = new int[4];

            for (int column = 0; column < 4; column++)
                warehouses[warehouse][row][column] = warehouse + row + column;
        }
    }

    void* elementAddress = &warehouses[1][0][2];
    int* selectedElement = static_cast<int*>(elementAddress);
    *selectedElement = 10;

    int total = 0;

    for (int warehouse = 0; warehouse < 3; warehouse++) {
        for (int row = 0; row < 2; row++) {
            for (int column = 0; column < 4; column++) {
                std::cout << warehouses[warehouse][row][column] << ' ';
                total += warehouses[warehouse][row][column];
            }
            std::cout << '\n';
        }
    }

    std::cout << "Total: " << total << '\n';

    for (int warehouse = 0; warehouse < 3; warehouse++) {
        for (int row = 0; row < 2; row++)
            delete[] warehouses[warehouse][row];

        delete[] warehouses[warehouse];
    }

    delete[] warehouses;

    return 0;
}
