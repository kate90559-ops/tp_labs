#include "Student.h"

Student::Student() : fullName(nullptr), grades(nullptr), gradeCount(0) {
    std::cout << "[Constructor] Student default created.\n";
    fullName = new char[1];
    fullName[0] = '\0';
}

Student::Student(const char* name, const int* gr, int count) : gradeCount(count) {
    std::cout << "[Constructor] Student parameterized created.\n";
    if (name) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    } else {
        fullName = new char[1];
        fullName[0] = '\0';
    }

    if (count > 0 && gr != nullptr) {
        grades = new int[count];
        for (int i = 0; i < count; ++i) {
            grades[i] = gr[i];
        }
    } else {
        grades = nullptr;
        gradeCount = 0;
    }
}

Student::Student(const Student& other) : gradeCount(other.gradeCount) {
    std::cout << "[Constructor] Student copy created.\n";
    fullName = new char[strlen(other.fullName) + 1];
    strcpy(fullName, other.fullName);

    if (other.gradeCount > 0) {
        grades = new int[other.gradeCount];
        for (int i = 0; i < other.gradeCount; ++i) {
            grades[i] = other.grades[i];
        }
    } else {
        grades = nullptr;
    }
}

Student::~Student() {
    std::cout << "[Destructor] Student destroyed.\n";
    delete[] fullName;
    delete[] grades;
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        delete[] fullName;
        delete[] grades;

        gradeCount = other.gradeCount;
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);

        if (other.gradeCount > 0) {
            grades = new int[other.gradeCount];
            for (int i = 0; i < other.gradeCount; ++i) {
                grades[i] = other.grades[i];
            }
        } else {
            grades = nullptr;
        }
    }
    return *this;
}

const char* Student::getFullName() const { return fullName; }
void Student::setFullName(const char* name) {
    if (!name || strlen(name) == 0) {
        throw std::invalid_argument("Error: Name cannot be empty!");
    }
    delete[] fullName;
    fullName = new char[strlen(name) + 1];
    strcpy(fullName, name);
}

const int* Student::getGrades() const { return grades; }
int Student::getGradeCount() const { return gradeCount; }

void Student::setGrades(const int* gr, int count) {
    if (count <= 0) {
        throw std::invalid_argument("Error: Grades count must be > 0!");
    }
    delete[] grades;
    gradeCount = count;
    grades = new int[count];
    for (int i = 0; i < count; ++i) {
        if (gr[i] < 2 || gr[i] > 5) {
            throw std::out_of_range("Error: Grade must be between 2 and 5!");
        }
        grades[i] = gr[i];
    }
}

double Student::getAverageGrade() const {
    if (gradeCount == 0) return 0.0;
    double sum = 0;
    for (int i = 0; i < gradeCount; ++i) {
        sum += grades[i];
    }
    return sum / gradeCount;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Full Name: " << s.fullName << " | Grades: [";
    for (int i = 0; i < s.gradeCount; ++i) {
        os << s.grades[i] << (i + 1 < s.gradeCount ? ", " : "");
    }
    os << "] | Avg: " << s.getAverageGrade();
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    char buffer[256];
    std::cout << "Enter Full Name: ";
    is.ignore();
    is.getline(buffer, 256);
    s.setFullName(buffer);

    int count;
    std::cout << "Enter count of grades: ";
    if (!(is >> count) || count <= 0) {
        throw std::invalid_argument("Invalid grades count input!");
    }

    int* tempGrades = new int[count];
    std::cout << "Enter " << count << " grades (2-5): ";
    for (int i = 0; i < count; ++i) {
        is >> tempGrades[i];
    }
    s.setGrades(tempGrades, count);
    delete[] tempGrades;

    return is;
}