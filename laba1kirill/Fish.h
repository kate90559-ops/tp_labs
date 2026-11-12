
#ifndef FISH_H
#define FISH_H

#include "Animal.h"

class Fish : public Animal {
private:
    char* foodType;

public:
    Fish();
    Fish(const char* breed, const char* color,
         const char* foodType);
    Fish(const Fish& other);
    ~Fish() override;

    void setFoodType(const char* foodType);
    const char* getFoodType() const;

    const char* getType() const override;
    void print() const override;

    Fish& operator=(const Fish& other);
};

#endif
