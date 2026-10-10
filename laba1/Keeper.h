#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"

class Keeper {
private:
    Base** data;     // Динамический массив указателей на базовый класс
    int size;        // Текущее количество элементов
    int capacity;    // Вместимость массива
    void resize();   // Расширение памяти при переполнении

public:
    Keeper();
    ~Keeper();

    void add(Base* item);          // Добавление элемента
    void remove(int index);        // Удаление элемента
    void printAll() const;         // Вывод всех элементов
    void saveToFile(const std::string& filename) const;   // Сохранение в файл
    void loadFromFile(const std::string& filename);     // Загрузка из файла
};

#endif // KEEPER_H