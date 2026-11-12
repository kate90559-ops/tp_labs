#include <iostream>
#include <limits>
#include <exception>

#include "Fish.h"
#include "Bird.h"
#include "Cat.h"
#include "Keeper.h"

using namespace std;

int readInt(const char* message) {
    int value;

    while (true) {
        cout << message;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        if (cin.eof()) throw runtime_error("Ввод завершен.");

        cout << "Ошибка: введите целое число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void readText(const char* message, char* buffer, int size) {
    cout << message;
    cin.getline(buffer, size);

    if (cin.fail()) {
        if (cin.eof()) throw runtime_error("Ввод завершен.");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Слишком длинный текст. Допустимо не более 255 символов.");
    }
}

void addFish(Keeper& keeper) {
    char breed[256], color[256], food[256];
    readText("Порода рыбы: ", breed, 256);
    readText("Окрас рыбы: ", color, 256);
    readText("Тип питания: ", food, 256);
    keeper.add(new Fish(breed, color, food));
}

void addBird(Keeper& keeper) {
    char breed[256], color[256], food[256], habitat[256];
    readText("Порода птицы: ", breed, 256);
    readText("Окрас птицы: ", color, 256);
    readText("Чем питается: ", food, 256);
    readText("Где обитает: ", habitat, 256);
    keeper.add(new Bird(breed, color, food, habitat));
}

void addCat(Keeper& keeper) {
    char breed[256], color[256], owner[256], name[256];
    readText("Порода кошки: ", breed, 256);
    readText("Окрас кошки: ", color, 256);
    readText("ФИО владельца: ", owner, 256);
    readText("Кличка кошки: ", name, 256);
    keeper.add(new Cat(breed, color, owner, name));
}

int main() {
    try {
        Keeper keeper;
        int choice = -1;

        do {
            cout << "\n========== МЕНЮ KEEPER ==========" << endl;
            cout << "1. Добавить рыбу" << endl;
            cout << "2. Добавить птицу" << endl;
            cout << "3. Добавить кошку" << endl;
            cout << "4. Показать всех животных" << endl;
            cout << "5. Удалить животное" << endl;
            cout << "6. Изменить данные животного" << endl;
            cout << "7. Показать количество животных" << endl;
            cout << "8. Сохранить Keeper в файл" << endl;
            cout << "9. Восстановить Keeper из файла" << endl;
            cout << "10. Проверить копирование Keeper" << endl;
            cout << "0. Выход" << endl;

            choice = readInt("Ваш выбор: ");

            try {
                switch (choice) {
                case 1: addFish(keeper); break;
                case 2: addBird(keeper); break;
                case 3: addCat(keeper); break;
                case 4: keeper.showAll(); break;
                case 5:
                    if (keeper.getCount() == 0) {
                        cout << "Список животных пуст." << endl;
                    } else {
                        keeper.showAll();
                        keeper.remove(readInt("Номер животного для удаления: "));
                    }
                    break;
                case 6:
                    if (keeper.getCount() == 0) {
                        cout << "Список животных пуст." << endl;
                    } else {
                        keeper.showAll();
                        keeper.edit(readInt("Номер животного для изменения: "));
                    }
                    break;
                case 7:
                    cout << "Количество животных: " << keeper.getCount() << endl;
                    break;
                case 8: {
                    char filename[256];
                    readText("Имя файла для сохранения (например, animals.dat): ",
                             filename, 256);
                    keeper.saveToFile(filename);
                    break;
                }
                case 9: {
                    char filename[256];
                    readText("Имя файла для загрузки: ", filename, 256);
                    keeper.loadFromFile(filename);
                    break;
                }
                case 10: {
                    Keeper copiedKeeper(keeper);
                    cout << "\nСодержимое копии Keeper:" << endl;
                    copiedKeeper.showAll();
                    break;
                }
                case 0:
                    cout << "Завершение программы." << endl;
                    break;
                default:
                    cout << "Такого пункта меню нет." << endl;
                    break;
                }
            } catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
        } while (choice != 0);
    } catch (const exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
        return 1;
    }

    cout << "Программа завершена." << endl;
    return 0;
}
