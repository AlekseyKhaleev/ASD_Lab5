#include <iostream>

#include "HashTable.h"
#include "Utils.h"

int main() {
    auto *table = new HashTable;
    auto *header = new Person("Name", "Address", "Phone", "SNILS");
    table->Add(*header);
    table->Print();
    std::string input;
    std::string separateIn[5];
    bool mark = true;
    while(mark) {
        std::cout<<"\n\nUse these commands to work with the table:\n\n";
        std::cout<<"Add a person       : add 'name' 'address' 'phone' 'snils'\n";
        std::cout<<"Delete a person    : remove 'name'\n";
        std::cout<<"Find person's m_data : find 'name'\n";
        std::cout<<"Exit               : exit\n\n";

        std::getline(std::cin, input);

        std::string  tmp;
        int i=0;
        for(auto &c:input){
            if(c != ' ') tmp +=c;
            else {
                separateIn[i] = tmp;
                i++;
                tmp.clear();
            }
        }
        separateIn[i] = tmp;

        switch (UserChoice(separateIn[0])){
            case add:{
                Person newPerson(separateIn[1],separateIn[2], separateIn[3], separateIn[4]);
                table->Add(newPerson);
                table->Print();
                break;
            }
            case remove:{
                table->Remove(separateIn[1]);
                table->Print();
                break;
            }
            case exit:{
                mark = false;
                break;
            }
        }
    }
    return 0;
}
