#include "Staff.h"

Staff::Staff() : position(""), phone(""), responsibility("") {
    std::cout << "Конструктор персонала по умолчанию вызван\n";
}

Staff::Staff(std::string pos, std::string ph, std::string resp) 
    : position(pos), phone(ph), responsibility(resp) {
    std::cout << "Параметризованный конструктор персонала вызван\n";
}

Staff::Staff(const Staff& other) 
    : position(other.position), phone(other.phone), responsibility(other.responsibility) {
    std::cout << "Конструктор копирования персонала вызван\n";
}

Staff::~Staff() {
    std::cout << "Деструктор персонала вызван\n";
}

void Staff::print() const {
    std::cout << "[Персонал] Должность: " << position 
              << ", Телефон: " << phone 
              << ", Зона ответственности: " << responsibility << "\n";
}

void Staff::input() {
    std::cout << "Введите должность: ";
    std::cin >> position;
    std::cout << "Введите телефон: ";
    std::cin >> phone;
    std::cout << "Введите зону ответственности: ";
    std::cin >> responsibility;
}

void Staff::save(std::ofstream& fout) const {
    fout << "Staff\n" << position << "\n" << phone << "\n" << responsibility << "\n";
}

void Staff::load(std::ifstream& fin) {
    fin >> position >> phone >> responsibility;
}