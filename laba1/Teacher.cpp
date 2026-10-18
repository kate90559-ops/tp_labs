#include "Teacher.h"

Teacher::Teacher() : Base(), groups(""), subjects("") {
    std::cout << "Конструктор преподавателя по умолчанию вызван\n";
}

Teacher::Teacher(std::string name, std::string grps, std::string subjs)
    : Base(name), groups(grps), subjects(subjs) {
    std::cout << "Параметризованный конструктор преподавателя вызван\n";
}

Teacher::Teacher(const Teacher& other)
    : Base(other), groups(other.groups), subjects(other.subjects) {
    std::cout << "Конструктор копирования преподавателя вызван\n";
}

Teacher::~Teacher() {
    std::cout << "Деструктор преподавателя вызван\n";
}

void Teacher::print() const {
    std::cout << "[Преподаватель] ФИО: " << fullName
              << ", Группы: " << groups
              << ", Предметы: " << subjects << "\n";
}

void Teacher::input() {
    std::cout << "Введите ФИО преподавателя: ";
    std::cin >> std::ws;
    std::getline(std::cin, fullName);
    std::cout << "Введите группы (через запятую): ";
    std::getline(std::cin, groups);
    std::cout << "Введите предметы: ";
    std::getline(std::cin, subjects);
}

void Teacher::save(std::ofstream& fout) const {
    fout << "Teacher\n" << fullName << "\n" << groups << "\n" << subjects << "\n";
}

void Teacher::load(std::ifstream& fin) {
    fin >> std::ws;
    std::getline(fin, fullName);
    std::getline(fin, groups);
    std::getline(fin, subjects);
}