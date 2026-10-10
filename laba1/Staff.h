#ifndef STAFF_H
#define STAFF_H

#include "Base.h"

class Staff : public Base {
private:
    std::string position;
    std::string phone;
    std::string responsibility;

public:
    Staff();
    Staff(std::string pos, std::string ph, std::string resp);
    Staff(const Staff& other);
    ~Staff() override;

    void print() const override;
    void input() override;
    void save(std::ofstream& fout) const override;
    void load(std::ifstream& fin) override;
};

#endif // STAFF_H