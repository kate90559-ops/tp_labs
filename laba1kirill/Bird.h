
#ifndef BIRD_H
#define BIRD_H

#include "Animal.h"

class Bird : public Animal {
private:
    char* food;
    char* habitat;

public:
    Bird();
    Bird(const char* breed, const char* color,
         const char* food, const char* habitat);
    Bird(const Bird& other);
    ~Bird() override;

    void setFood(const char* food);
    void setHabitat(const char* habitat);

    const char* getFood() const;
    const char* getHabitat() const;

    const char* getType() const override;
    void print() const override;

    Bird& operator=(const Bird& other);
};

#endif
