#ifndef STUDENT_H
#define STUDENT_H

#include "Base.h"

class Student : public Base {
private:
    char* group;
    char* specialty;
    int course;
    double averageGrade;

public:
    Student();
    Student(const char* name, const char* grp, const char* spec, int crs, double avg);
    Student(const Student& other);
    ~Student() override;

    Student& operator=(const Student& other);

    void print() const override;
    void input() override;
    void edit() override;
    void save(std::ofstream& fout) const override;
    void load(std::ifstream& fin) override;
};

#endif // STUDENT_H