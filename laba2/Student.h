#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

class Student {
private:
    char* fullName;
    int* grades;
    int gradeCount;

public:
    Student();
    Student(const char* name, const int* gr, int count);
    Student(const Student& other);
    ~Student();

    Student& operator=(const Student& other);

    // Геттеры и сеттеры
    const char* getFullName() const;
    void setFullName(const char* name);

    const int* getGrades() const;
    int getGradeCount() const;
    void setGrades(const int* gr, int count);

    double getAverageGrade() const;

    // Перегрузка потоков
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

#endif