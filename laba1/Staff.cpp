#include "Staff.h"

Staff::Staff() : Base(), position(""), phone(""), responsibility("") {
    std::cout << "Конструктор персонала по умолчанию вызван\n";
}

Staff::Staff(std::string name, std::string pos, std::string ph, std::string resp) 
    : Base(name), position(pos), phone(ph), responsibility(resp) {
    std::cout << "Параметризованный конструктор персонала вызван\n";
}

Staff::Staff(const Staff& other) 
    : Base(other), position(other.position), phone(other.phone), responsibility(other.responsibility) {
    std::cout << "Конструктор копирования персонала вызван\n";
}

Staff::~Staff() {
    std::cout << "Деструктор персонала вызван\n";
}

void Staff::print() const {
    std::cout << "[Персонал] ФИО: " << fullName
              << ", Должность: " << position 
              << ", Телефон: " << phone 
              << ", Область ответственности: " << responsibility << "\n";
}

void Staff::input() {
    std::cout << "Введите ФИО сотрудника: ";
    std::cin >> std::ws;
    std::getline(std::cin, fullName);
    std::cout << "Введите должность: ";
    std::getline(std::cin, position);
    std::cout << "Введите телефон: ";
    std::getline(std::cin, phone);
    std::cout << "Введите область ответственности: ";
    std::getline(std::cin, responsibility);
}

void Staff::save(std::ofstream& fout) const {
    fout << "Staff\n" << fullName << "\n" << position << "\n" << phone << "\n" << responsibility << "\n";
}

void Staff::load(std::ifstream& fin) {
    fin >> std::ws;
    std::getline(fin, fullName);
    std::getline(fin, position);
    std::getline(fin, phone);
    std::getline(fin, responsibility);
}