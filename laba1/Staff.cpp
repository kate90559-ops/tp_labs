#include "Staff.h"
#include <string>

char* copyString(const char* str);

Staff::Staff() : Base() {
    position = copyString("");
    phone = copyString("");
    responsibility = copyString("");
    std::cout << "[Staff] Default constructor called\n";
}

Staff::Staff(const char* name, const char* pos, const char* ph, const char* resp) : Base(name) {
    position = copyString(pos);
    phone = copyString(ph);
    responsibility = copyString(resp);
    std::cout << "[Staff] Parameterized constructor called\n";
}

Staff::Staff(const Staff& other) : Base(other) {
    position = copyString(other.position);
    phone = copyString(other.phone);
    responsibility = copyString(other.responsibility);
    std::cout << "[Staff] Copy constructor called\n";
}

Staff::~Staff() {
    std::cout << "[Staff] Destructor called\n";
    delete[] position;
    delete[] phone;
    delete[] responsibility;
}

Staff& Staff::operator=(const Staff& other) {
    if (this != &other) {
        Base::operator=(other);
        delete[] position;
        delete[] phone;
        delete[] responsibility;
        position = copyString(other.position);
        phone = copyString(other.phone);
        responsibility = copyString(other.responsibility);
        std::cout << "[Staff] Assignment operator called\n";
    }
    return *this;
}

void Staff::print() const {
    std::cout << "[Staff] Full Name: " << fullName 
              << ", Position: " << position 
              << ", Phone: " << phone 
              << ", Responsibility: " << responsibility << "\n";
}

void Staff::input() {
    std::string temp;
    std::cout << "Enter Full Name: ";
    std::cin >> std::ws;
    std::getline(std::cin, temp);
    setFullName(temp.c_str());

    std::cout << "Enter position: ";
    std::getline(std::cin, temp);
    delete[] position;
    position = copyString(temp.c_str());

    std::cout << "Enter phone: ";
    std::getline(std::cin, temp);
    delete[] phone;
    phone = copyString(temp.c_str());

    std::cout << "Enter responsibility area: ";
    std::getline(std::cin, temp);
    delete[] responsibility;
    responsibility = copyString(temp.c_str());
}

void Staff::edit() {
    std::cout << "--- Edit Staff ---\n";
    input();
}

void Staff::save(std::ofstream& fout) const {
    fout << "Staff\n" << fullName << "\n" << position << "\n" << phone << "\n" << responsibility << "\n";
}

void Staff::load(std::ifstream& fin) {
    std::string temp;
    fin >> std::ws;
    std::getline(fin, temp);
    setFullName(temp.c_str());

    std::getline(fin, temp);
    delete[] position;
    position = copyString(temp.c_str());

    std::getline(fin, temp);
    delete[] phone;
    phone = copyString(temp.c_str());

    std::getline(fin, temp);
    delete[] responsibility;
    responsibility = copyString(temp.c_str());
}