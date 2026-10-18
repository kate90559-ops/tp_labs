#include "Base.h"

Base::Base() : fullName("Неизвестно") {
    std::cout << "Базовый конструктор по умолчанию вызван\n";
}

Base::Base(std::string name) : fullName(name) {
    std::cout << "Базовый параметризованный конструктор вызван для: " << fullName << "\n";
}

Base::Base(const Base& other) : fullName(other.fullName) {
    std::cout << "Базовый конструктор копирования вызван для: " << fullName << "\n";
}

Base::~Base() {
    std::cout << "Базовый деструктор вызван для: " << fullName << "\n";
}

std::string Base::getFullName() const {
    return fullName;
}

void Base::setFullName(const std::string& name) {
    fullName = name;
}