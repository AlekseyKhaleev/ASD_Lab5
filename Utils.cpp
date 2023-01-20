#include "Utils.h"
#include "ClassList.h"

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
    std::string base[]{"add", "remove", "find", "exit"};
    for(int i=0; i < text.size(); i++){
        if(text==base[i]) return i;
    }
    return -1;
}
