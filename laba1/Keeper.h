#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <string>

class Keeper {
private:
    Base** data;
    int size;
    int capacity;

    void resize();

public:
    Keeper();
    ~Keeper();

    void add(Base* item);
    void remove(int index);
    void editElement(int index);
    void printAll() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    int getSize() const;
};

#endif // KEEPER_H