#ifndef GROUP_H
#define GROUP_H

#include "Student.h"
#include <iostream>
#include <stdexcept>

class Group {
private:
    int groupNumber;
    Student* students;
    int studentCount;
    int capacity;

    void resize();

public:
    Group();
    Group(int number);
    Group(const Group& other);
    ~Group();

    Group& operator=(const Group& other);

    int getGroupNumber() const;
    void setGroupNumber(int number);

    int getStudentCount() const;
    double getGroupAverage() const;

    void addStudent(const Student& s, int index = -1);
    void removeStudent(int index);
    void editStudent(int index);

    const Student& getStudent(int index) const;

    void printHighAchievers() const;

    friend std::ostream& operator<<(std::ostream& os, const Group& g);
};

#endif