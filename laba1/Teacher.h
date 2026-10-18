#ifndef TEACHER_H
#define TEACHER_H

#include "Base.h"

class Teacher : public Base {
private:
    std::string groups;    // Ведомые группы
    std::string subjects;  // Преподаваемые предметы

public:
    Teacher();
    Teacher(std::string name, std::string grps, std::string subjs);
    Teacher(const Teacher& other);
    ~Teacher() override;

    void print() const override;
    void input() override;
    void save(std::ofstream& fout) const override;
    void load(std::ifstream& fin) override;
};

#endif // TEACHER_H