#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <cstring>

class Base {
protected:
    char* fullName; // Динамическая строка fullName (для хранения фио массив с динамической памятью)

public:
    Base(); // конструктор по умолчанию (вызывается, когда создаем объект базового класса без передачи каких-либо параметров)
    Base(const char* name); //параметризированный конструктор (когда сразу передаем имя при создании объекта)
    Base(const Base& other); // конструктор копирования (когда новый объект создается как точная копия существующего объекта)
    virtual ~Base(); //деструктор (при уничтожении объекта)

    Base& operator=(const Base& other); //оператор присвоения (когда один уже существующий оъект присваивается другому)

    const char* getFullName() const;
    void setFullName(const char* name);

    virtual void print() const = 0;
    virtual void input() = 0;
    virtual void edit() = 0;
    virtual void save(std::ofstream& fout) const = 0;
    virtual void load(std::ifstream& fin) = 0;
};

#endif // BASE_H