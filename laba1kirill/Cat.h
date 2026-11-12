
#ifndef CAT_H
#define CAT_H

#include "Animal.h"

class Cat : public Animal {
private:
    char* owner;
    char* name;

public:
    Cat();
    Cat(const char* breed, const char* color,
        const char* owner, const char* name);
    Cat(const Cat& other);
    ~Cat() override;

    void setOwner(const char* owner);
    void setName(const char* name);

    const char* getOwner() const;
    const char* getName() const;

    const char* getType() const override;
    void print() const override;

    Cat& operator=(const Cat& other);
};

#endif
