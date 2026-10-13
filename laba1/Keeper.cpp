#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include <stdexcept>

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
        throw std::out_of_range("Ошибка: индекс за пределами диапазона!");
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
        throw std::runtime_error("Ошибка открытия файла для записи!");
    }
    fout << size << "\n";
    for (int i = 0; i < size; ++i) {
        data[i]->save(fout);
    }
    std::cout << "Данные успешно сохранены в файл.\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("Ошибка открытия файла для чтения!");
    }
    
    int loadedSize;
    fin >> loadedSize;
    if (fin.fail()) return;

    // Очищаем старые данные перед загрузкой новых
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    size = 0;

    std::string type;
    for (int i = 0; i < loadedSize; ++i) {
        fin >> type;
        Base* newItem = nullptr;
        if (type == "Student") {
            newItem = new Student();
        } else if (type == "Teacher") {
            newItem = new Teacher();
        } else if (type == "Staff") {
            newItem = new Staff();
        }

        if (newItem != nullptr) {
            newItem->load(fin);
            if (size >= capacity) {
                resize();
            }
            data[size++] = newItem;
        }
    }
    std::cout << "Данные успешно загружены из файла.\n";
}