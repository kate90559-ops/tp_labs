#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <string>

class Base {
public:
    Base();
    Base(const Base& other);
    virtual ~Base();

    // Чисто виртуальные методы (интерфейс для классов-наследников)
    virtual void print() const = 0;              // Вывод данных в консоль
    virtual void input() = 0;                    // Ввод данных с клавиатуры
    virtual void save(std::ofstream& fout) const = 0; // Сохранение в файл
    virtual void load(std::ifstream& fin) = 0;   // Чтение из файла
};

#endif // BASE_H