#include "Teacher.h"

Teacher::Teacher() : groups(""), subjects("") {
    std::cout << "Конструктор преподавателя по умолчанию вызван\n";
}

Teacher::Teacher(std::string grps, std::string subjs) : groups(grps), subjects(subjs) {
    std::cout << "Параметризованный конструктор преподавателя вызван\n";
}

Teacher::Teacher(const Teacher& other) : groups(other.groups), subjects(other.subjects) {
    std::cout << "Конструктор копирования преподавателя вызван\n";
}

Teacher::~Teacher() {
    std::cout << "Деструктор преподавателя вызван\n";
}

void Teacher::print() const {
    std::cout << "[Преподаватель] Группы: " << groups << ", Предметы: " << subjects << "\n";
}

void Teacher::input() {
    std::cout << "Введите группы (через запятую): ";
    std::cin >> groups;
    std::cout << "Введите предметы: ";
    std::cin >> subjects;
}

void Teacher::save(std::ofstream& fout) const {
    fout << "Teacher\n" << groups << "\n" << subjects << "\n";
}

void Teacher::load(std::ifstream& fin) {
    fin >> groups >> subjects;
}