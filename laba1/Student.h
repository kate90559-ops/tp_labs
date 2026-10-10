#ifndef STUDENT_H
#define STUDENT_H

#include "Base.h"

class Student : public Base {
private:
    std::string group;
    std::string specialty;
    int course;
    double averageGrade;

public:
    Student();
    Student(std::string name, std::string grp, std::string spec, int crs, double avg);
    Student(const Student& other);
    ~Student() override;

    void print() const override;
    void input() override;
    void save(std::ofstream& fout) const override;
    void load(std::ifstream& fin) override;
};

#endif // STUDENT_H