#include <iostream>
#include <string>
#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

int main() {
    Keeper keeper;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n=== UNIVERSITY MANAGEMENT SYSTEM ===\n"
                  << "1. Add student\n"
                  << "2. Add teacher\n"
                  << "3. Add staff\n"
                  << "4. View all records\n"
                  << "5. Edit record by index\n"
                  << "6. Delete record by index\n"
                  << "7. Save to file\n"
                  << "8. Load from file\n"
                  << "0. Exit\n"
                  << "Select menu option: ";

        if (!(std::cin >> choice)) {
            std::cout << "Input error! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    Base* student = new Student();
                    student->input();
                    keeper.add(student);
                    std::cout << "Student added successfully!\n";
                    break;
                }
                case 2: {
                    Base* teacher = new Teacher();
                    teacher->input();
                    keeper.add(teacher);
                    std::cout << "Teacher added successfully!\n";
                    break;
                }
                case 3: {
                    Base* staff = new Staff();
                    staff->input();
                    keeper.add(staff);
                    std::cout << "Staff added successfully!\n";
                    break;
                }
                case 4:
                    keeper.printAll();
                    break;
                case 5: {
                    int index;
                    std::cout << "Enter index to edit (starting from 0): ";
                    std::cin >> index;
                    keeper.editElement(index);
                    std::cout << "Record updated successfully!\n";
                    break;
                }
                case 6: {
                    int index;
                    std::cout << "Enter index to delete (starting from 0): ";
                    std::cin >> index;
                    keeper.remove(index);
                    std::cout << "Record deleted successfully!\n";
                    break;
                }
                case 7: {
                    std::string filename;
                    std::cout << "Enter filename to save: ";
                    std::cin >> filename;
                    keeper.saveToFile(filename);
                    std::cout << "Data saved to file successfully!\n";
                    break;
                }
                case 8: {
                    std::string filename;
                    std::cout << "Enter filename to load: ";
                    std::cin >> filename;
                    keeper.loadFromFile(filename);
                    std::cout << "Data loaded from file successfully!\n";
                    break;
                }
                case 0:
                    std::cout << "Exiting program...\n";
                    break;
                default:
                    std::cout << "Invalid menu option! Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "An unknown exception occurred!\n";
        }
    }

    return 0;
}