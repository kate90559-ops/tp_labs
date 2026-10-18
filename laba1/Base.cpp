#include "Base.h"

char* copyString(const char* str) {
    if (!str) return nullptr;
    char* res = new char[std::strlen(str) + 1];
    std::strcpy(res, str);
    return res;
}

Base::Base() {
    fullName = copyString("Unknown");
    std::cout << "[Base] Default constructor called for: " << fullName << "\n";
}

Base::Base(const char* name) {
    fullName = copyString(name ? name : "Unknown");
    std::cout << "[Base] Parameterized constructor called for: " << fullName << "\n";
}

Base::Base(const Base& other) {
    fullName = copyString(other.fullName);
    std::cout << "[Base] Copy constructor called for: " << fullName << "\n";
}

Base::~Base() {
    std::cout << "[Base] Destructor called for: " << (fullName ? fullName : "nullptr") << "\n";
    delete[] fullName;
}

Base& Base::operator=(const Base& other) {
    if (this != &other) {
        delete[] fullName;
        fullName = copyString(other.fullName);
        std::cout << "[Base] Assignment operator called for: " << fullName << "\n";
    }
    return *this;
}

const char* Base::getFullName() const {
    return fullName;
}

void Base::setFullName(const char* name) {
    delete[] fullName;
    fullName = copyString(name ? name : "Unknown");
}