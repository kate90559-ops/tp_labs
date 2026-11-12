#include "Group.h"

void Group::resize() {
    capacity = (capacity == 0) ? 2 : capacity * 2;
    Student* newStudents = new Student[capacity];
    for (int i = 0; i < studentCount; ++i) {
        newStudents[i] = students[i];
    }
    delete[] students;
    students = newStudents;
}

Group::Group() : groupNumber(0), students(nullptr), studentCount(0), capacity(0) {
    std::cout << "[Constructor] Group default created.\n";
}

Group::Group(int number) : groupNumber(number), students(nullptr), studentCount(0), capacity(0) {
    std::cout << "[Constructor] Group parameterized created.\n";
}

Group::Group(const Group& other) : groupNumber(other.groupNumber), studentCount(other.studentCount), capacity(other.capacity) {
    std::cout << "[Constructor] Group copy created.\n";
    if (capacity > 0) {
        students = new Student[capacity];
        for (int i = 0; i < studentCount; ++i) {
            students[i] = other.students[i];
        }
    } else {
        students = nullptr;
    }
}

Group::~Group() {
    std::cout << "[Destructor] Group destroyed.\n";
    delete[] students;
}

Group& Group::operator=(const Group& other) {
    if (this != &other) {
        delete[] students;
        groupNumber = other.groupNumber;
        studentCount = other.studentCount;
        capacity = other.capacity;

        if (capacity > 0) {
            students = new Student[capacity];
            for (int i = 0; i < studentCount; ++i) {
                students[i] = other.students[i];
            }
        } else {
            students = nullptr;
        }
    }
    return *this;
}

int Group::getGroupNumber() const { return groupNumber; }
void Group::setGroupNumber(int number) { groupNumber = number; }

int Group::getStudentCount() const { return studentCount; }

double Group::getGroupAverage() const {
    if (studentCount == 0) return 0.0;
    double totalSum = 0;
    for (int i = 0; i < studentCount; ++i) {
        totalSum += students[i].getAverageGrade();
    }
    return totalSum / studentCount;
}

void Group::addStudent(const Student& s, int index) {
    if (studentCount == capacity) {
        resize();
    }

    if (index < 0 || index > studentCount) {
        index = studentCount; // по умолчанию в конец
    }

    for (int i = studentCount; i > index; --i) {
        students[i] = students[i - 1];
    }

    students[index] = s;
    studentCount++;
}

void Group::removeStudent(int index) {
    if (index < 0 || index >= studentCount) {
        throw std::out_of_range("Error: Student index out of range!");
    }
    for (int i = index; i < studentCount - 1; ++i) {
        students[i] = students[i + 1];
    }
    studentCount--;
}

void Group::editStudent(int index) {
    if (index < 0 || index >= studentCount) {
        throw std::out_of_range("Error: Student index out of range!");
    }
    std::cout << "Editing student #" << index + 1 << ":\n";
    std::cin >> students[index];
}

const Student& Group::getStudent(int index) const {
    if (index < 0 || index >= studentCount) {
        throw std::out_of_range("Error: Index out of bounds!");
    }
    return students[index];
}

void Group::printHighAchievers() const {
    bool found = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].getAverageGrade() > 4.0) {
            std::cout << "  Name: " << students[i].getFullName()
                      << " | Group: " << groupNumber
                      << " | Avg: " << students[i].getAverageGrade() << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No students with average grade > 4.0 in group " << groupNumber << ".\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Group& g) {
    os << "=== GROUP №" << g.groupNumber << " (Avg score: " << g.getGroupAverage() << ") ===\n";
    if (g.studentCount == 0) {
        os << "  [Group is empty]\n";
    } else {
        for (int i = 0; i < g.studentCount; ++i) {os << "  " << i + 1 << ". " << g.students[i] << "\n";
        }
    }
    return os;
}