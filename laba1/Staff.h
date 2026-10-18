#ifndef STAFF_H
#define STAFF_H

#include "Base.h"

class Staff : public Base {
private:
    char* position;
    char* phone;
    char* responsibility;

public:
    Staff();
    Staff(const char* name, const char* pos, const char* ph, const char* resp);
    Staff(const Staff& other);
    ~Staff() override;

    Staff& operator=(const Staff& other);

    void print() const override;
    void input() override;
    void edit() override;
    void save(std::ofstream& fout) const override;
    void load(std::ifstream& fin) override;
};

#endif // STAFF_H