#include "Utils.h"


int HashMidSquare(const std::string &s, int table_size) {
    int hash_result = 0;
    for (auto &el:s)
    {
        hash_result += el;
    }
    hash_result *= hash_result;
    hash_result >>= 11;
    hash_result %= 1024;

    return hash_result % table_size;
}

int UserChoice(const std::string& text) {
    std::string base[]{"print", "add", "remove", "find", "exit"};
    for(int i=0; i < base->size(); i++){
        if(text==base[i]) return i;
    }
    return -1;
}

std::string FormatStr(const std::string &str) {
    std::string tmp;
    unsigned long side = (TABLE_ELEM_LENTH-str.size())/2;
    if(str.size()>TABLE_ELEM_LENTH){
        tmp = str.substr(0, TABLE_ELEM_LENTH);
        return tmp;
    }
    for(unsigned long i=0; i<TABLE_ELEM_LENTH; i++){
        if(i == side){
            tmp += str;
            i+=str.size()-1;
        }else
            tmp += " ";
    }
    return tmp;
}

std::string MakeTableRow(const std::string &name, const std::string &address, const std::string &phone, const std::string &snils) {
    std::string tmp("|");
    tmp+= FormatStr(name)+"|"+ FormatStr(address)+"|"+ FormatStr(phone)+"|"+ FormatStr(snils)+"|\n";
    for(int i=0; i<(TABLE_COLUMNS*TABLE_ELEM_LENTH)+TABLE_DELIM_CNT;i++){
        tmp+="_";
    }
    tmp+="\n";
    return tmp;
}
