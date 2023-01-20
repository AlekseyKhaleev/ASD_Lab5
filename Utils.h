#pragma once

#include <string>
#include "ClassList.h"

#define print  0
#define add    1
#define remove 2
#define find   3
#define exit   4

const unsigned long TABLE_ELEM_LENTH = 20;
const int TABLE_COLUMNS = 4;
const int TABLE_DELIM_CNT = 5;

int UserChoice(const std::string& text);

std::string MakeTableRow(const std::string &name, const std::string &address, const std::string &phone, const std::string &snils);;

std::string FormatStr(const std::string &str);

struct Person{
    std::string NAME;
    std::string ADDRESS;
    std::string PHONE;
    std::string SNILS;

    bool operator == (const Person &p2) const {
        return (NAME == p2.NAME);
    }
    bool operator == (const std::string &p2) const {
        return (NAME == p2);
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
    void Print() const{
        std::cout<<MakeTableRow(NAME,ADDRESS,PHONE,SNILS);
    }
};

int HashMidSquare(const std::string& s, int table_size);



