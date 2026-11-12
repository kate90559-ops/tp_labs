
#include "Fish.h"
#include <iostream>

using namespace std;

Fish::Fish() : Animal() {
    foodType = copyText("Не указан");

    cout << "Fish: конструктор без параметров" << endl;
}

Fish::Fish(const char* breed, const char* color,
           const char* foodType)
    : Animal(breed, color) {
    this->foodType = copyText(foodType);

    cout << "Fish: конструктор с параметрами" << endl;
}

Fish::Fish(const Fish& other) : Animal(other) {
    foodType = copyText(other.foodType);

    cout << "Fish: конструктор копирования" << endl;
}

Fish::~Fish() {
    cout << "Fish: деструктор" << endl;

    delete[] foodType;
}

void Fish::setFoodType(const char* foodType) {
    char* newFoodType = copyText(foodType);

    delete[] this->foodType;
    this->foodType = newFoodType;
}

const char* Fish::getFoodType() const {
    return foodType;
}

const char* Fish::getType() const {
    return "Рыба";
}

void Fish::print() const {
    cout << "Порода: " << getBreed() << endl;
    cout << "Окрас: " << getColor() << endl;
    cout << "Тип питания: " << foodType << endl;
}

Fish& Fish::operator=(const Fish& other) {
    if (this != &other) {
        char* newFoodType = copyText(other.foodType);

        try {
            Animal::operator=(other);
        }
        catch (...) {
            delete[] newFoodType;
            throw;
        }

        delete[] foodType;
        foodType = newFoodType;
    }

    cout << "Fish: оператор присваивания" << endl;

    return *this;
}
