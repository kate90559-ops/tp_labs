
#include "Bird.h"
#include <iostream>

using namespace std;

Bird::Bird() : Animal() {
    food = copyText("Не указан");
    habitat = nullptr;

    try {
        habitat = copyText("Не указано");
    }
    catch (...) {
        delete[] food;
        throw;
    }

    cout << "Bird: конструктор без параметров" << endl;
}

Bird::Bird(const char* breed, const char* color,
           const char* food, const char* habitat)
    : Animal(breed, color) {
    this->food = copyText(food);
    this->habitat = nullptr;

    try {
        this->habitat = copyText(habitat);
    }
    catch (...) {
        delete[] this->food;
        throw;
    }

    cout << "Bird: конструктор с параметрами" << endl;
}

Bird::Bird(const Bird& other) : Animal(other) {
    food = copyText(other.food);
    habitat = nullptr;

    try {
        habitat = copyText(other.habitat);
    }
    catch (...) {
        delete[] food;
        throw;
    }

    cout << "Bird: конструктор копирования" << endl;
}

Bird::~Bird() {
    cout << "Bird: деструктор" << endl;

    delete[] food;
    delete[] habitat;
}

void Bird::setFood(const char* food) {
    char* newFood = copyText(food);

    delete[] this->food;
    this->food = newFood;
}

void Bird::setHabitat(const char* habitat) {
    char* newHabitat = copyText(habitat);

    delete[] this->habitat;
    this->habitat = newHabitat;
}

const char* Bird::getFood() const {
    return food;
}

const char* Bird::getHabitat() const {
    return habitat;
}

const char* Bird::getType() const {
    return "Птица";
}

void Bird::print() const {
    cout << "Порода: " << getBreed() << endl;
    cout << "Окрас: " << getColor() << endl;
    cout << "Чем питается: " << food << endl;
    cout << "Где обитает: " << habitat << endl;
}

Bird& Bird::operator=(const Bird& other) {
    if (this != &other) {
        char* newFood = copyText(other.food);
        char* newHabitat = nullptr;

        try {
            newHabitat = copyText(other.habitat);
        }
        catch (...) {
            delete[] newFood;
            throw;
        }

        try {
            Animal::operator=(other);
        }
        catch (...) {
            delete[] newFood;
            delete[] newHabitat;
            throw;
        }

        delete[] food;
        delete[] habitat;

        food = newFood;
        habitat = newHabitat;
    }

    cout << "Bird: оператор присваивания" << endl;

    return *this;
}
