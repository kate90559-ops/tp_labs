#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <cstring>

class Base {
protected:
    char* fullName; // Dynamic string for Full Name

public:
    Base();
    Base(const char* name);
    Base(const Base& other);
    virtual ~Base();

    Base& operator=(const Base& other);

    const char* getFullName() const;
    void setFullName(const char* name);

    virtual void print() const = 0;
    virtual void input() = 0;
    virtual void edit() = 0;
    virtual void save(std::ofstream& fout) const = 0;
    virtual void load(std::ifstream& fin) = 0;
};

#endif // BASE_H