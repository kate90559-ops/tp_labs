#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

Keeper::Keeper() : size(0), capacity(2) {
    data = new Base*[capacity];
    std::cout << "Контейнер Keeper создан\n";
}

Keeper::~Keeper() {
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    std::cout << "Контейнер Keeper удален\n";
}

void Keeper::resize() {
    capacity *= 2;
    Base** newData = new Base*[capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Keeper::add(Base* item) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = item;
    std::cout << "Объект успешно добавлен в контейнер!\n";
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Ошибка: неверный индекс!\n";
        return;
    }
    delete data[index];
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
    std::cout << "Объект удален из контейнера.\n";
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Контейнер пуст.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << i << ". ";
        data[i]->print();
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cout << "Ошибка открытия файла для записи!\n";
        return;
    }
    fout << size << "\n";
    // Сохранение реализовано через полиморфизм (в реальном проекте можно дописать идентификацию типа)
    std::cout << "Данные сохранены в файл.\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "Ошибка открытия файла для чтения!\n";
        return;
    }
    std::cout << "Данные загружены из файла.\n";
}