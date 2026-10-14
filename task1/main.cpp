#include <iostream>

double calculateAverage(const int* temperatures, int numberOfDays) {
    int sum = 0;
    for (int day = 0; day < numberOfDays; day++)
        sum += temperatures[day];

    return static_cast<double>(sum) / numberOfDays;
}

int findMinimum(const int* temperatures, int numberOfDays) {
    int minimum = temperatures[0];
    for (int day = 1; day < numberOfDays; day++)
        if (temperatures[day] < minimum)
            minimum = temperatures[day];

    return minimum;
}

int findMaximum(const int* temperatures, int numberOfDays) {
    int maximum = temperatures[0];
    for (int day = 1; day < numberOfDays; day++)
        if (temperatures[day] > maximum)
            maximum = temperatures[day];

    return maximum;
}

int countFreezingDays(const int* temperatures, int numberOfDays) {
    int freezingDays = 0;
    for (int day = 0; day < numberOfDays; day++)
        if (temperatures[day] < 0)
            freezingDays++;

    return freezingDays;
}

int main() {
    int numberOfDays;
    std::cin >> numberOfDays;

    int* temperatures = new int[numberOfDays];

    for (int day = 0; day < numberOfDays; day++)
        std::cin >> temperatures[day];

    double average = calculateAverage(temperatures, numberOfDays);
    int roundedTenths = static_cast<int>(average * 10 + (average >= 0 ? 0.5 : -0.5));
    int integerPart = roundedTenths / 10;
    int fractionalPart = roundedTenths % 10;

    if (fractionalPart < 0)
        fractionalPart = -fractionalPart;

    std::cout << integerPart << '.' << fractionalPart << '\n';
    std::cout << findMinimum(temperatures, numberOfDays) << ' '
              << findMaximum(temperatures, numberOfDays) << '\n';
    std::cout << countFreezingDays(temperatures, numberOfDays) << '\n';

    delete[] temperatures;
    return 0;
}
