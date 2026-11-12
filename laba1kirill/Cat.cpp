
#include "Cat.h"
#include <iostream>

using namespace std;

Cat::Cat() : Animal() {
    owner = copyText("Не указан");
    name = nullptr;

    try {
        name = copyText("Без клички");
    }
    catch (...) {
        delete[] owner;
        throw;
    }

    cout << "Cat: конструктор без параметров" << endl;
}

Cat::Cat(const char* breed, const char* color,
         const char* owner, const char* name)
    : Animal(breed, color) {
    this->owner = copyText(owner);
    this->name = nullptr;

    try {
        this->name = copyText(name);
    }
    catch (...) {
        delete[] this->owner;
        throw;
    }

    cout << "Cat: конструктор с параметрами" << endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
    owner = copyText(other.owner);
    name = nullptr;

    try {
        name = copyText(other.name);
    }
    catch (...) {
        delete[] owner;
        throw;
    }

    cout << "Cat: конструктор копирования" << endl;
}

Cat::~Cat() {
    cout << "Cat: деструктор" << endl;

    delete[] owner;
    delete[] name;
}

void Cat::setOwner(const char* owner) {
    char* newOwner = copyText(owner);

    delete[] this->owner;
    this->owner = newOwner;
}

void Cat::setName(const char* name) {
    char* newName = copyText(name);

    delete[] this->name;
    this->name = newName;
}

const char* Cat::getOwner() const {
    return owner;
}

const char* Cat::getName() const {
    return name;
}

const char* Cat::getType() const {
    return "Кошка";
}

void Cat::print() const {
    cout << "Порода: " << getBreed() << endl;
    cout << "Окрас: " << getColor() << endl;
    cout << "ФИО владельца: " << owner << endl;
    cout << "Кличка: " << name << endl;
}

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        char* newOwner = copyText(other.owner);
        char* newName = nullptr;

        try {
            newName = copyText(other.name);
        }
        catch (...) {
            delete[] newOwner;
            throw;
        }

        try {
            Animal::operator=(other);
        }
        catch (...) {
            delete[] newOwner;
            delete[] newName;
            throw;
        }

        delete[] owner;
        delete[] name;

        owner = newOwner;
        name = newName;
    }

    cout << "Cat: оператор присваивания" << endl;

    return *this;
}
