#pragma once

#include <string>
#include "ClassList.h"

#define add    0
#define remove 1
#define find   2
#define exit   3

int UserChoice(std::string text);

struct Person{
    std::string NAME;
    std::string ADDRESS;
    std::string PHONE;
    std::string SNILS;

    bool operator == (const Person &p2) const
    {
        return (NAME == p2.NAME);
    }

    Person(std::string name, std::string address, std::string phone, std::string snils){
        NAME = name;
        ADDRESS = address;
        PHONE = phone;
        SNILS = snils;
    }
    Person(Person &copy){
        NAME = copy.NAME;
        ADDRESS = copy.ADDRESS;
        PHONE = copy.ADDRESS;
        SNILS = copy.SNILS;
    }
};

int HashMidSquare(const std::string& s, int table_size);



