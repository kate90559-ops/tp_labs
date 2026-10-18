#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Keeper::Keeper() : size(0), capacity(2) {
    data = new Base*[capacity];
}

Keeper::~Keeper() {
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
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
    if (size == capacity) {
        resize();
    }
    data[size++] = item;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Error: Index out of bounds!");
    }
    delete data[index];
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

void Keeper::editElement(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Error: Index out of bounds!");
    }
    data[index]->edit();
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Keeper is empty.\n";
        return;
    }
    std::cout << "--- ALL RECORDS ---\n";
    for (int i = 0; i < size; ++i) {
        std::cout << i << ". ";
        data[i]->print();
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing!");
    }
    fout << size << "\n";
    for (int i = 0; i < size; ++i) {
        data[i]->save(fout);
    }
    fout.close();
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("Error: Could not open file for reading!");
    }

    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    size = 0;

    int count;
    if (!(fin >> count)) {
        fin.close();
        return;
    }

    std::string type;
    for (int i = 0; i < count; ++i) {
        fin >> type;
        Base* item = nullptr;
        if (type == "Student") {
            item = new Student();
        } else if (type == "Teacher") {
            item = new Teacher();
        } else if (type == "Staff") {
            item = new Staff();
        }

        if (item) {
            item->load(fin);
            add(item);
        }
    }
    fin.close();
}

int Keeper::getSize() const {
    return size;
}