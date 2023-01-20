#pragma once

#include <string>
#include "ClassList.h"

#define add    0
#define remove 1
#define find   2
#define exit   3

int UserChoice(const std::string& text);

struct Person{
    std::string NAME;
    std::string ADDRESS;
    std::string PHONE;
    std::string SNILS;

    bool operator == (const Person &p2) const
    {
        return (NAME == p2.NAME);
    }

    Person(const std::string &name, const std::string &address, const std::string &phone, const std::string &snils){
        NAME += name;
        ADDRESS += address;
        PHONE += phone;
        SNILS += snils;
    }
    Person(Person const &copy){
        NAME += copy.NAME;
        ADDRESS += copy.ADDRESS;
        PHONE += copy.PHONE;
        SNILS += copy.SNILS;
    }
};

int HashMidSquare(const std::string& s, int table_size);



