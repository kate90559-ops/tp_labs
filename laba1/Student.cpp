#include "Student.h"

Student::Student() : group(""), specialty(""), course(1), averageGrade(0.0) {
    std::cout << "Конструктор студента по умолчанию вызван\n";
}

Student::Student(std::string name, std::string grp, std::string spec, int crs, double avg)
    : group(grp), specialty(spec), course(crs), averageGrade(avg) {
    std::cout << "Параметризованный конструктор студента вызван\n";
}

Student::Student(const Student& other) : group(other.group), specialty(other.specialty), course(other.course), averageGrade(other.averageGrade) {
    std::cout << "Конструктор копирования студента вызван\n";
}

Student::~Student() {
    std::cout << "Деструктор студента вызван\n";
}

void Student::print() const {
    std::cout << "[Студент] Группа: " << group 
              << ", Специальность: " << specialty 
              << ", Курс: " << course 
              << ", Ср. балл: " << averageGrade << "\n";
}

void Student::input() {
    std::cout << "Введите группу: ";
    std::cin >> group;
    std::cout << "Введите специальность: ";
    std::cin >> specialty;
    std::cout << "Введите курс: ";
    std::cin >> course;
    std::cout << "Введите средний балл: ";
    std::cin >> averageGrade;
}

void Student::save(std::ofstream& fout) const {
    fout << "Student\n" << group << "\n" << specialty << "\n" << course << "\n" << averageGrade << "\n";
}

void Student::load(std::ifstream& fin) {
    fin >> group >> specialty >> course >> averageGrade;
}