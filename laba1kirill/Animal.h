
#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>

class Animal {
protected:
    char* breed;
    char* color;

    static char* copyText(const char* text);

public:
    Animal();
    Animal(const char* breed, const char* color);
    Animal(const Animal& other);
    virtual ~Animal();

    void setBreed(const char* breed);
    void setColor(const char* color);

    const char* getBreed() const;
    const char* getColor() const;

    virtual const char* getType() const = 0;
    virtual void print() const = 0;

    Animal& operator=(const Animal& other);

    friend std::ostream& operator<<(std::ostream& out,
                                    const Animal& animal);
};

#endif
