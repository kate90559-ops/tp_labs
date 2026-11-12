#ifndef KEEPER_H
#define KEEPER_H

#include "Animal.h"

class Keeper {
private:
    Animal** animals;
    int count;
    int capacity;

    void resize(int newCapacity);
    void clear();

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);

    void add(Animal* animal);
    void remove(int index);
    void showAll() const;
    void edit(int index);

    int getCount() const;
    Animal* getAnimal(int index) const;
    Animal* operator[](int index) const;

    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);
};

#endif