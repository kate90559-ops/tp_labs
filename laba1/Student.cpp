#include "Student.h"
#include <string>

char* copyString(const char* str);

Student::Student() : Base(), course(1), averageGrade(0.0) {
    group = copyString("");
    specialty = copyString("");
    std::cout << "[Student] Default constructor called\n";
}

Student::Student(const char* name, const char* grp, const char* spec, int crs, double avg)
    : Base(name), course(crs), averageGrade(avg) {
    group = copyString(grp);
    specialty = copyString(spec);
    std::cout << "[Student] Parameterized constructor called\n";
}

Student::Student(const Student& other) : Base(other), course(other.course), averageGrade(other.averageGrade) {
    group = copyString(other.group);
    specialty = copyString(other.specialty);
    std::cout << "[Student] Copy constructor called\n";
}

Student::~Student() {
    std::cout << "[Student] Destructor called\n";
    delete[] group;
    delete[] specialty;
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Base::operator=(other);
        delete[] group;
        delete[] specialty;
        group = copyString(other.group);
        specialty = copyString(other.specialty);
        course = other.course;
        averageGrade = other.averageGrade;
        std::cout << "[Student] Assignment operator called\n";
    }
    return *this;
}

void Student::print() const {
    std::cout << "[Student] Full Name: " << fullName 
              << ", Group: " << group 
              << ", Specialty: " << specialty 
              << ", Course: " << course 
              << ", Avg Grade: " << averageGrade << "\n";
}

void Student::input() {
    std::string temp;
    std::cout << "Enter Full Name: ";
    std::cin >> std::ws;
    std::getline(std::cin, temp);
    setFullName(temp.c_str());

    std::cout << "Enter group: ";
    std::getline(std::cin, temp);
    delete[] group;
    group = copyString(temp.c_str());

    std::cout << "Enter specialty: ";
    std::getline(std::cin, temp);
    delete[] specialty;
    specialty = copyString(temp.c_str());

    std::cout << "Enter course: ";
    std::cin >> course;
    std::cout << "Enter average grade: ";
    std::cin >> averageGrade;
}

void Student::edit() {
    std::cout << "--- Edit Student ---\n";
    input();
}

void Student::save(std::ofstream& fout) const {
    fout << "Student\n" << fullName << "\n" << group << "\n" << specialty << "\n" << course << "\n" << averageGrade << "\n";
}

void Student::load(std::ifstream& fin) {
    std::string temp;
    fin >> std::ws;
    std::getline(fin, temp);
    setFullName(temp.c_str());

    std::getline(fin, temp);
    delete[] group;
    group = copyString(temp.c_str());

    std::getline(fin, temp);
    delete[] specialty;
    specialty = copyString(temp.c_str());

    fin >> course >> averageGrade;
}