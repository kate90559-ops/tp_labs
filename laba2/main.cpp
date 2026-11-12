#include <iostream>
#include <string>
#include "Group.h"
#include "FileTask.h"

// Контейнер для хранения списка групп с динамическим расширением
struct GroupList {
    Group* groups = nullptr;
    int count = 0;
    int capacity = 0;

    void addGroupSorted(const Group& g) {
        if (count == capacity) {
            capacity = (capacity == 0) ? 2 : capacity * 2;
            Group* newG = new Group[capacity];
            for (int i = 0; i < count; ++i) newG[i] = groups[i];
            delete[] groups;
            groups = newG;
        }

        // Автоматическая сортировка по возрастанию номера группы
        int pos = count;
        for (int i = 0; i < count; ++i) {
            if (g.getGroupNumber() < groups[i].getGroupNumber()) {
                pos = i;
                break;
            }
        }

        for (int i = count; i > pos; --i) {
            groups[i] = groups[i - 1];
        }
        groups[pos] = g;
        count++;
    }

    ~GroupList() {
        delete[] groups;
    }
};

void printMenu() {
    std::cout << "\n===== LAB 2 USER MENU (Variant 1) =====\n"
              << "1. Add Group (auto-sorted by number)\n"
              << "2. Add Student to Group\n"
              << "3. Edit Student in Group\n"
              << "4. Remove Student from Group\n"
              << "5. Print All Groups & Students\n"
              << "6. Show High Achievers (Avg > 4.0) [Task Requirement]\n"
              << "7. Run Task 2 (File Word Swap)\n"
              << "0. Exit\n"
              << "Choice: ";
}

int main() {
    GroupList groupList;
    int choice = -1;

    while (choice != 0) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    int gNum;
                    std::cout << "Enter new group number: ";
                    std::cin >> gNum;
                    groupList.addGroupSorted(Group(gNum));
                    std::cout << "Group added and sorted!\n";
                    break;
                }
                case 2: {
                    if (groupList.count == 0) {
                        std::cout << "No groups available. Create a group first!\n";
                        break;
                    }
                    std::cout << "Select group index (0 to " << groupList.count - 1 << "): ";
                    int gIdx;
                    std::cin >> gIdx;
                    if (gIdx < 0 || gIdx >= groupList.count) throw std::out_of_range("Invalid group index!");

                    Student s;
                    std::cin >> s;

                    std::cout << "Enter index to insert student (-1 for end): ";
                    int pos;
                    std::cin >> pos;

                    groupList.groups[gIdx].addStudent(s, pos);
                    std::cout << "Student added successfully!\n";
                    break;
                }
                case 3: {
                    if (groupList.count == 0) { std::cout << "No groups!\n"; break; }
                    std::cout << "Select group index (0 to " << groupList.count - 1 << "): ";
                    int gIdx;
                    std::cin >> gIdx;
                    if (gIdx < 0 || gIdx >= groupList.count) throw std::out_of_range("Invalid group index!");

                    std::cout << "Select student index (0 to " << groupList.groups[gIdx].getStudentCount() - 1 << "): ";
                    int sIdx;
                    std::cin >> sIdx;

                    groupList.groups[gIdx].editStudent(sIdx);
                    break;
                }
                case 4: {
                    if (groupList.count == 0) { std::cout << "No groups!\n"; break; }
                    std::cout << "Select group index (0 to " << groupList.count - 1 << "): ";
                    int gIdx;
                    std::cin >> gIdx;
                    if (gIdx < 0 || gIdx >= groupList.count) throw std::out_of_range("Invalid group index!");

                    std::cout << "Select student index to remove: ";
                    int sIdx;
                    std::cin >> sIdx;

                    groupList.groups[gIdx].removeStudent(sIdx);
                    std::cout << "Student removed!\n";
                    break;
                }
                case 5: {
                    std::cout << "\n--- ALL GROUPS & STUDENTS ---\n";
                    if (groupList.count == 0) std::cout << "List is empty.\n";
                    for (int i = 0; i < groupList.count; ++i) {
                        std::cout << "[" << i << "] " << groupList.groups[i];
                    }
                    break;
                }
                case 6: {
                    std::cout << "\n--- STUDENTS WITH AVG GRADE > 4.0 ---\n";
                    for (int i = 0; i < groupList.count; ++i) {
                        groupList.groups[i].printHighAchievers();
                    }
                    break;
                }
                case 7: {
                    std::cout << "Enter text filename (e.g., test.txt): ";
                    std::string fname;
                    std::cin >> fname;
                    processFileSwapWords(fname);
                    break;
                }
                case 0:
                    std::cout << "Exiting program...\n";
                    break;
                default:
                    std::cout << "Unknown choice!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "\n[EXCEPTION CAUGHT] " << e.what() << "\n";
        }
    }

    return 0;
}