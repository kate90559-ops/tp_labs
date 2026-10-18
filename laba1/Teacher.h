#ifndef TEACHER_H
#define TEACHER_H

#include "Base.h"

class Teacher : public Base {
private:
    char* groups;
    char* subjects;

public:
    Teacher();
    Teacher(const char* name, const char* grps, const char* subjs);
    Teacher(const Teacher& other);
    ~Teacher() override;

    Teacher& operator=(const Teacher& other);

    void print() const override;
    void input() override;
    void edit() override;
    void save(std::ofstream& fout) const override;
    void load(std::ifstream& fin) override;
};

#endif // TEACHER_H