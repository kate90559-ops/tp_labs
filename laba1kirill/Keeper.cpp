#include "Keeper.h"
#include "Fish.h"
#include "Bird.h"
#include "Cat.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <limits>

using namespace std;

namespace {
    const char FILE_MAGIC[8] = { 'A', 'N', 'I', 'M', 'K', 'P', 'R', '1' };
    const uint32_t MAX_RECORDS = 100000;
    const uint32_t MAX_TEXT_LENGTH = 1024 * 1024;

    void writeUInt32(ofstream& out, uint32_t value) {
        out.write(reinterpret_cast<const char*>(&value), sizeof(value));
        if (!out) throw runtime_error("Ошибка записи числа в файл.");
    }

    uint32_t readUInt32(ifstream& in) {
        uint32_t value = 0;
        in.read(reinterpret_cast<char*>(&value), sizeof(value));
        if (!in) throw runtime_error("Файл поврежден или данные закончились неожиданно.");
        return value;
    }

    void writeText(ofstream& out, const char* text) {
        if (text == nullptr) throw invalid_argument("Нельзя сохранить пустой указатель на текст.");
        size_t length = 0;
        while (text[length] != '\0') ++length;
        if (length > MAX_TEXT_LENGTH) throw length_error("Слишком длинное текстовое поле.");
        writeUInt32(out, static_cast<uint32_t>(length));
        out.write(text, static_cast<streamsize>(length));
        if (!out) throw runtime_error("Ошибка записи текста в файл.");
    }

    char* readText(ifstream& in) {
        uint32_t length = readUInt32(in);
        if (length > MAX_TEXT_LENGTH) throw runtime_error("Недопустимая длина текстового поля в файле.");

        char* text = new char[static_cast<size_t>(length) + 1];
        in.read(text, static_cast<streamsize>(length));
        if (!in) {
            delete[] text;
            throw runtime_error("Файл поврежден: не удалось прочитать текст.");
        }
        text[length] = '\0';
        return text;
    }

    Animal* copyAnimal(const Animal* animal) {
        if (const Fish* fish = dynamic_cast<const Fish*>(animal)) return new Fish(*fish);
        if (const Bird* bird = dynamic_cast<const Bird*>(animal)) return new Bird(*bird);
        if (const Cat* cat = dynamic_cast<const Cat*>(animal)) return new Cat(*cat);
        throw runtime_error("Неизвестный производный тип животного при копировании.");
    }

    void writeAnimal(ofstream& out, const Animal* animal) {
        if (const Fish* fish = dynamic_cast<const Fish*>(animal)) {
            writeUInt32(out, 1);
            writeText(out, fish->getBreed());
            writeText(out, fish->getColor());
            writeText(out, fish->getFoodType());
        } else if (const Bird* bird = dynamic_cast<const Bird*>(animal)) {
            writeUInt32(out, 2);
            writeText(out, bird->getBreed());
            writeText(out, bird->getColor());
            writeText(out, bird->getFood());
            writeText(out, bird->getHabitat());
        } else if (const Cat* cat = dynamic_cast<const Cat*>(animal)) {
            writeUInt32(out, 3);
            writeText(out, cat->getBreed());
            writeText(out, cat->getColor());
            writeText(out, cat->getOwner());
            writeText(out, cat->getName());
        } else {
            throw runtime_error("Нельзя сохранить неизвестный тип животного.");
        }
    }

    Animal* readAnimal(ifstream& in) {
        uint32_t type = readUInt32(in);
        char* breed = nullptr;
        char* color = nullptr;
        char* extra1 = nullptr;
        char* extra2 = nullptr;

        try {
            breed = readText(in);
            color = readText(in);
            extra1 = readText(in);

            Animal* result = nullptr;
            if (type == 1) {
                result = new Fish(breed, color, extra1);
            } else if (type == 2) {
                extra2 = readText(in);
                result = new Bird(breed, color, extra1, extra2);
            } else if (type == 3) {
                extra2 = readText(in);
                result = new Cat(breed, color, extra1, extra2);
            } else {
                throw runtime_error("В файле обнаружен неизвестный тип животного.");
            }

            delete[] breed;
            delete[] color;
            delete[] extra1;
            delete[] extra2;
            return result;
        } catch (...) {
            delete[] breed;
            delete[] color;
            delete[] extra1;
            delete[] extra2;
            throw;
        }
    }
}

Keeper::Keeper() : animals(nullptr), count(0), capacity(2) {
    animals = new Animal*[capacity];
    for (int i = 0; i < capacity; ++i) animals[i] = nullptr;
    cout << "Keeper: конструктор без параметров" << endl;
}

Keeper::Keeper(const Keeper& other)
    : animals(nullptr), count(0), capacity(other.capacity) {
    animals = new Animal*[capacity];
    for (int i = 0; i < capacity; ++i) animals[i] = nullptr;

    try {
        for (int i = 0; i < other.count; ++i) {
            animals[i] = copyAnimal(other.animals[i]);
            ++count;
        }
    } catch (...) {
        clear();
        throw;
    }
    cout << "Keeper: конструктор копирования" << endl;
}

Keeper::~Keeper() {
    cout << "Keeper: деструктор" << endl;
    clear();
}

void Keeper::clear() {
    for (int i = 0; i < count; ++i) {
        delete animals[i];
        animals[i] = nullptr;
    }
    delete[] animals;
    animals = nullptr;
    count = 0;
    capacity = 0;
}

void Keeper::resize(int newCapacity) {
    if (newCapacity < count) throw invalid_argument("Новая вместимость меньше количества животных.");
    if (newCapacity < 1) newCapacity = 1;

    Animal** newAnimals = new Animal*[newCapacity];
    for (int i = 0; i < newCapacity; ++i) newAnimals[i] = nullptr;
    for (int i = 0; i < count; ++i) newAnimals[i] = animals[i];

    delete[] animals;
    animals = newAnimals;
    capacity = newCapacity;
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this == &other) {
        cout << "Keeper: оператор присваивания (самоприсваивание)" << endl;
        return *this;
    }

    Keeper temporary(other);

    Animal** oldAnimals = animals;
    int oldCount = count;

    animals = temporary.animals;
    count = temporary.count;
    capacity = temporary.capacity;

    temporary.animals = oldAnimals;
    temporary.count = oldCount;
    temporary.capacity = (oldAnimals == nullptr ? 0 : capacity);

    // Swap capacity correctly using a temporary variable.
    int oldCapacity = temporary.capacity;
    temporary.capacity = capacity;
    capacity = oldCapacity;

    cout << "Keeper: оператор присваивания" << endl;
    return *this;
}

void Keeper::add(Animal* animal) {
    if (animal == nullptr) throw invalid_argument("Нельзя добавить пустой указатель на животное.");

    if (count == capacity) {
        int newCapacity = (capacity == 0) ? 2 : capacity * 2;
        resize(newCapacity);
    }

    animals[count++] = animal;
    cout << "Keeper: животное добавлено." << endl;
}

void Keeper::remove(int index) {
    if (index < 1 || index > count) throw out_of_range("Неверный номер животного для удаления.");

    int position = index - 1;
    delete animals[position];

    for (int i = position; i < count - 1; ++i) animals[i] = animals[i + 1];
    animals[--count] = nullptr;

    cout << "Keeper: животное удалено." << endl;
}

void Keeper::showAll() const {
    if (count == 0) {
        cout << "Список животных пуст." << endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        cout << "\n===== ЖИВОТНОЕ №" << i + 1 << " =====" << endl;
        cout << *animals[i] << endl;
    }
}

void Keeper::edit(int index) {
    if (index < 1 || index > count) throw out_of_range("Неверный номер животного для редактирования.");

    Animal* animal = animals[index - 1];
    char value[256];

    cout << "\nРедактирование: " << animal->getType() << endl;
    cout << "Новая порода: ";
    cin.getline(value, 256);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Слишком длинная порода.");
    }
    animal->setBreed(value);

    cout << "Новый окрас: ";
    cin.getline(value, 256);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Слишком длинный окрас.");
    }
    animal->setColor(value);

    if (Fish* fish = dynamic_cast<Fish*>(animal)) {
        cout << "Новый тип питания: ";
        cin.getline(value, 256);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Слишком длинный тип питания.");
        }
        fish->setFoodType(value);
    } else if (Bird* bird = dynamic_cast<Bird*>(animal)) {
        cout << "Чем питается: ";
        cin.getline(value, 256);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Слишком длинное значение питания.");
        }
        bird->setFood(value);

        cout << "Где обитает: ";
        cin.getline(value, 256);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Слишком длинное место обитания.");
        }
        bird->setHabitat(value);
    } else if (Cat* cat = dynamic_cast<Cat*>(animal)) {
        cout << "ФИО владельца: ";
        cin.getline(value, 256);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Слишком длинное ФИО владельца.");
        }
        cat->setOwner(value);

        cout << "Кличка: ";
        cin.getline(value, 256);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Слишком длинная кличка.");
        }
        cat->setName(value);
    } else {
        throw runtime_error("Неизвестный тип животного.");
    }

    cout << "Данные животного изменены." << endl;
}

int Keeper::getCount() const {
    return count;
}

Animal* Keeper::getAnimal(int index) const {
    if (index < 1 || index > count) throw out_of_range("Неверный номер животного.");
    return animals[index - 1];
}

Animal* Keeper::operator[](int index) const {
    if (index < 0 || index >= count) throw out_of_range("Индекс животного вне диапазона.");
    return animals[index];
}

void Keeper::saveToFile(const char* filename) const {
    if (filename == nullptr || filename[0] == '\0') {
        throw invalid_argument("Имя файла не должно быть пустым.");
    }

    ofstream out(filename, ios::binary | ios::trunc);
    if (!out) throw runtime_error("Не удалось открыть файл для сохранения.");

    out.write(FILE_MAGIC, sizeof(FILE_MAGIC));
    if (!out) throw runtime_error("Ошибка записи заголовка файла.");

    writeUInt32(out, static_cast<uint32_t>(count));
    for (int i = 0; i < count; ++i) writeAnimal(out, animals[i]);

    out.close();
    if (!out) throw runtime_error("Ошибка завершения записи файла.");

    cout << "Keeper: данные сохранены в файл \"" << filename << "\"." << endl;
}

void Keeper::loadFromFile(const char* filename) {
    if (filename == nullptr || filename[0] == '\0') {
        throw invalid_argument("Имя файла не должно быть пустым.");
    }

    ifstream in(filename, ios::binary);
    if (!in) throw runtime_error("Не удалось открыть файл для загрузки.");

    char magic[sizeof(FILE_MAGIC)];
    in.read(magic, sizeof(magic));
    if (!in || !equal(magic, magic + sizeof(magic), FILE_MAGIC)) {
        throw runtime_error("Неверный формат файла или поврежден заголовок.");
    }

    uint32_t fileCount = readUInt32(in);
    if (fileCount > MAX_RECORDS) throw runtime_error("В файле слишком много записей.");

    Keeper loaded;
    if (fileCount > static_cast<uint32_t>(loaded.capacity)) {
        loaded.resize(static_cast<int>(fileCount));
    }

    for (uint32_t i = 0; i < fileCount; ++i) {
        Animal* animal = readAnimal(in);
        try {
            loaded.add(animal);
        } catch (...) {
            // add() only takes ownership after successful insertion.
            delete animal;
            throw;
        }
    }

    // Replace current data only after the entire file was read successfully.
    Animal** oldAnimals = animals;
    int oldCount = count;
    int oldCapacity = capacity;

    animals = loaded.animals;
    count = loaded.count;
    capacity = loaded.capacity;

    loaded.animals = oldAnimals;
    loaded.count = oldCount;
    loaded.capacity = oldCapacity;

    cout << "Keeper: данные восстановлены из файла \"" << filename << "\"." << endl;
}
