#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <string>

class Base {
protected:
    std::string fullName; // ФИО элемента

public:
    Base();
    Base(std::string name);
    Base(const Base& other);
    virtual ~Base();

    std::string getFullName() const;
    void setFullName(const std::string& name);

    // Чисто виртуальные методы
    virtual void print() const = 0;              // Вывод данных в консоль
    virtual void input() = 0;                    // Ввод данных с клавиатуры
    virtual void save(std::ofstream& fout) const = 0; // Сохранение в файл
    virtual void load(std::ifstream& fin) = 0;   // Чтение из файла
};

#endif // BASE_H