#include <iostream>
#include "Student.h"

int main() {
    std::cout << "=== Testing Student Class (Day 1) ===\n\n";

    // 1. Проверка конструктора по умолчанию
    std::cout << "--- 1. Default constructor test ---\n";
    Student s1;
    std::cout << "Default student: " << s1 << "\n\n";

    // 2. Проверка ввода с клавиатуры (оператор >>) и геттеров/сеттеров
    std::cout << "--- 2. Input operator (>>) test ---\n";
    Student s2;
    try {
        std::cin >> s2;
        std::cout << "\nYou successfully entered:\n" << s2 << "\n";
        std::cout << "Average grade: " << s2.getAverageGrade() << "\n\n";
    } catch (const std::exception& e) {
        std::cout << "\n[ERROR] " << e.what() << "\n\n";
    }

    // 3. Проверка конструктора копирования
    std::cout << "--- 3. Copy constructor test ---\n";
    Student s3(s2);
    std::cout << "Copied student (s3): " << s3 << "\n\n";

    std::cout << "=== End of test, destructors will be called now ===\n";
    return 0;
}