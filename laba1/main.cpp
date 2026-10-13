#include <iostream>
#include <string>
#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

void showMenu() {
    std::cout << "\n=== МЕНЮ УПРАВЛЕНИЯ ВУЗОМ ===\n"
              << "1. Добавить студента\n"
              << "2. Добавить преподавателя\n"
              << "3. Добавить сотрудника\n"
              << "4. Просмотреть все записи\n"
              << "5. Удалить запись по индексу\n"
              << "6. Сохранить в файл\n"
              << "7. Загрузить из файла\n"
              << "0. Выход\n"
              << "Выберите пункт меню: ";
}

int main() {
    // Установка кодировки для корректного отображения кириллицы в консоли Windows
    system("chcp 65001 > nul");

    Keeper keeper;
    int choice = -1;

    while (choice != 0) {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода! Пожалуйста, введите число.\n";
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    Student* student = new Student();
                    student->input();
                    keeper.add(student);
                    break;
                }
                case 2: {
                    Teacher* teacher = new Teacher();
                    teacher->input();
                    keeper.add(teacher);
                    break;
                }
                case 3: {
                    Staff* staff = new Staff();
                    staff->input();
                    keeper.add(staff);
                    break;
                }
                case 4: {
                    std::cout << "\n--- СПИСОК ВСЕХ ЗАПИСЕЙ ---\n";
                    keeper.printAll();
                    break;
                }
                case 5: {
                    int index;
                    std::cout << "Введите индекс для удаления: ";
                    std::cin >> index;
                    keeper.remove(index);
                    break;
                }
                case 6: {
                    std::string filename;
                    std::cout << "Введите имя файла для сохранения (например, data.txt): ";
                    std::cin >> filename;
                    keeper.saveToFile(filename);
                    break;
                }
                case 7: {
                    std::string filename;
                    std::cout << "Введите имя файла для загрузки (например, data.txt): ";
                    std::cin >> filename;
                    keeper.loadFromFile(filename);
                    break;
                }
                case 0:
                    std::cout << "Выход из программы...\n";
                    break;
                default:
                    std::cout << "Неверный пункт меню! Попробуйте снова.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Произошло неизвестное исключение!\n";
        }
    }

    return 0;
}