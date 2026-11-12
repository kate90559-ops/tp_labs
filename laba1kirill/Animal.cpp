
#include "Animal.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

using namespace std;

char* Animal::copyText(const char* text) {
    if (text == nullptr) {
        throw invalid_argument("Строка не должна быть nullptr");
    }

    char* result = new char[strlen(text) + 1];
    strcpy(result, text);

    return result;
}

Animal::Animal() {
    breed = copyText("Не указана");
    color = nullptr;

    try {
        color = copyText("Не указан");
    }
    catch (...) {
        delete[] breed;
        throw;
    }

    cout << "Animal: конструктор без параметров" << endl;
}

Animal::Animal(const char* breed, const char* color) {
    this->breed = copyText(breed);
    this->color = nullptr;

    try {
        this->color = copyText(color);
    }
    catch (...) {
        delete[] this->breed;
        throw;
    }

    cout << "Animal: конструктор с параметрами" << endl;
}

Animal::Animal(const Animal& other) {
    breed = copyText(other.breed);
    color = nullptr;

    try {
        color = copyText(other.color);
    }
    catch (...) {
        delete[] breed;
        throw;
    }

    cout << "Animal: конструктор копирования" << endl;
}

Animal::~Animal() {
    cout << "Animal: деструктор" << endl;

    delete[] breed;
    delete[] color;
}

void Animal::setBreed(const char* breed) {
    char* newBreed = copyText(breed);

    delete[] this->breed;
    this->breed = newBreed;
}

void Animal::setColor(const char* color) {
    char* newColor = copyText(color);

    delete[] this->color;
    this->color = newColor;
}

const char* Animal::getBreed() const {
    return breed;
}

const char* Animal::getColor() const {
    return color;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        char* newBreed = copyText(other.breed);
        char* newColor = nullptr;

        try {
            newColor = copyText(other.color);
        }
        catch (...) {
            delete[] newBreed;
            throw;
        }

        delete[] breed;
        delete[] color;

        breed = newBreed;
        color = newColor;
    }

    cout << "Animal: оператор присваивания" << endl;

    return *this;
}

ostream& operator<<(ostream& out, const Animal& animal) {
    out << "Тип: " << animal.getType() << endl;
    animal.print();

    return out;
}
