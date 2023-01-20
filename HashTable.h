#pragma once

#include <iostream>
#include <iomanip>

#include "ClassList.h"
#include "Utils.h"

using namespace ClassList;

class HashTable {
    static const int DEFAULT_TABLE_SIZE = 8;
    int m_bucketCnt;
    int m_itemCnt;
    int m_tableSize;

    List<Person> *m_items;

    void Resize() {
        int previousTableSize = m_tableSize;
        m_tableSize *= 2;
        m_bucketCnt = 0;
        m_itemCnt = 0;

        auto *items2 = new List<Person> [m_tableSize];
        std::swap(m_items, items2);
        for (int i = 0; i < previousTableSize; i++) {
            if (!items2[i].IsEmpty()) {
                Node<Person> *current = items2[i].head;
                while(current != nullptr){
                    Add(current->m_data);
                    current = current->m_pNext;
                }
            }
        }
        delete[] items2;
    }

public:
    HashTable() {
        m_tableSize = DEFAULT_TABLE_SIZE;
        m_itemCnt = 0;
        m_bucketCnt = 0;
        m_items = new List<Person> [m_tableSize];
    }

    ~HashTable() {
        delete[] m_items;
    }

    void Add(Person &value) {
        if (m_bucketCnt > m_itemCnt / 2) Resize();

        auto *item = new Person(value); // Create the item
        int index = HashMidSquare(value.NAME, m_tableSize);// Compute the index

        m_items[index].PushBack(*item);
        if(m_items[index].GetSize()>1) m_itemCnt++;
        else m_bucketCnt++;
    }

    void Remove(const std::string &key) {
        int index = HashMidSquare(key, m_tableSize);
        List<Person> &item = m_items[index];

        // если элемента нет в таблице
        if (item.IsEmpty()) {
            return;
        } else
        {
            if (item.GetSize()==1) {
                // Нет коллизий. Удаляем единственный элемент
                item.PopFront();
                m_itemCnt--;
                return;
            } else {
                // Существует цепочка коллизий
                item.RemoveValue(key);
                if(item.GetSize()==1) m_bucketCnt--;
                return;
            }
        }
    }

    const Person *Find(const std::string &key) {

        int index = HashMidSquare(key, m_tableSize);
        List<Person> &item = m_items[index];
        if (!item.IsEmpty()) {
            Node<Person> *current = item.head;
            while (current != nullptr) {
                if (current->m_data.NAME == key) {
                    return &current->m_data;
                }
                current = current->m_pNext;
            }
        }
        return nullptr;
    }

    void Print(const std::string &key = "") {
        std::cout << " | NAME";
        std::cout << " | ADDRESS";
        std::cout << " | PHONE";
        std::cout << " | SNILS";
        std::cout << " |\n";

        if (!key.empty()) {
            const Person *target;
            if ((target = Find(key))) target->Print();
            else std::cout << "Key '" << key << "' not found\n";
        } else {
            for (int i = 0; i < m_tableSize; i++) {
                if (!m_items[i].IsEmpty()) {
                    Node<Person> *current = m_items[i].head;
                    while (current != nullptr) {
                        current->m_data.Print();
                        current = current->m_pNext;

                    }
                }
            }
        }
    }

};