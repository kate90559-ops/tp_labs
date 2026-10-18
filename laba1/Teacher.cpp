#include "Teacher.h"
#include <string>

char* copyString(const char* str);

Teacher::Teacher() : Base() {
    groups = copyString("");
    subjects = copyString("");
    std::cout << "[Teacher] Default constructor called\n";
}

Teacher::Teacher(const char* name, const char* grps, const char* subjs) : Base(name) {
    groups = copyString(grps);
    subjects = copyString(subjs);
    std::cout << "[Teacher] Parameterized constructor called\n";
}

Teacher::Teacher(const Teacher& other) : Base(other) {
    groups = copyString(other.groups);
    subjects = copyString(other.subjects);
    std::cout << "[Teacher] Copy constructor called\n";
}

Teacher::~Teacher() {
    std::cout << "[Teacher] Destructor called\n";
    delete[] groups;
    delete[] subjects;
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        Base::operator=(other);
        delete[] groups;
        delete[] subjects;
        groups = copyString(other.groups);
        subjects = copyString(other.subjects);
        std::cout << "[Teacher] Assignment operator called\n";
    }
    return *this;
}

void Teacher::print() const {
    std::cout << "[Teacher] Full Name: " << fullName 
              << ", Groups: " << groups 
              << ", Subjects: " << subjects << "\n";
}

void Teacher::input() {
    std::string temp;
    std::cout << "Enter Full Name: ";
    std::cin >> std::ws;
    std::getline(std::cin, temp);
    setFullName(temp.c_str());

    std::cout << "Enter groups (separated by comma): ";
    std::getline(std::cin, temp);
    delete[] groups;
    groups = copyString(temp.c_str());

    std::cout << "Enter subjects: ";
    std::getline(std::cin, temp);
    delete[] subjects;
    subjects = copyString(temp.c_str());
}

void Teacher::edit() {
    std::cout << "--- Edit Teacher ---\n";
    input();
}

void Teacher::save(std::ofstream& fout) const {
    fout << "Teacher\n" << fullName << "\n" << groups << "\n" << subjects << "\n";
}

void Teacher::load(std::ifstream& fin) {
    std::string temp;
    fin >> std::ws;
    std::getline(fin, temp);
    setFullName(temp.c_str());

    std::getline(fin, temp);
    delete[] groups;
    groups = copyString(temp.c_str());

    std::getline(fin, temp);
    delete[] subjects;
    subjects = copyString(temp.c_str());
}