#pragma once

#include <iostream>
#include <iomanip>

#include "ClassList.h"
#include "Utils.h"



class HashTable
{
    static const int DEFAULT_TABLE_SIZE = 8;
    constexpr static const double RESIZE_TABLE_FACTOR = 0.75;
//    struct Item
//    {
//        Person value;
//        explicit Item(Person& value_) : value(value_) {}
//    };

    int m_allCnt;
    int m_tableSize;
    int m_validCnt;

    Person** m_items;
    List<Person>** m_buckets;
    List<int> m_validIndexes;

    void Resize()
    {
        int previousTableSize = m_tableSize;
        m_tableSize *= 2;
        m_allCnt = 0;
        m_validCnt = 0;

        auto** arr2 = new Person * [m_tableSize];
        for (int i = 0; i < m_tableSize; ++i)
            arr2[i] = nullptr;
        std::swap(m_items, arr2);
        for (int i = 0; i < previousTableSize; ++i)        {
            if (arr2[i]) {
                Add(arr2[i]->NAME,*arr2[i]);
            }
        }
        auto** buckets2 = new List<Person>*[m_tableSize];
        for(int i=0;i<m_tableSize;i++){
            buckets2[i] = nullptr;
        }
        std::swap(m_buckets, buckets2);
        for(int i=0; i <previousTableSize; i++){
            if (buckets2[i]){
                for(int j=0; j<buckets2[i]->GetSize(); j++){

                    Add(buckets2[i]->Ind(j).NAME, buckets2[i]->Ind(j));
                }
            }
        }

        for (int i = 0; i < previousTableSize; ++i) {
            delete arr2[i];
        }
        delete[] arr2;

        for (int i = 0; i < previousTableSize; ++i) {
            buckets2[i]->Clear();
            }
        delete[] buckets2;

    }



    void HandleCollision(int index, Person item) {
        List<Person> *head = m_buckets[index];
        if (head == nullptr) {
            // Необходимо создать список
            head = new List<Person>;
            head->PushBack(item);
            m_buckets[index] = head;
            return;
        } else {
            // Добавляем в список
            m_buckets[index]->PushBack(item);
            return;
        }
    }


public:
    HashTable()
    {
        m_tableSize = DEFAULT_TABLE_SIZE;
        m_validCnt = 0;
        m_allCnt = 0;

        m_items = new Person*[m_tableSize];
        for (int i = 0; i < m_tableSize; ++i)
            m_items[i] = nullptr;

        m_buckets = (new List<Person> *[m_tableSize]);
        for (int i=0; i<m_tableSize; i++)
            m_buckets[i] = nullptr;

    }

    ~HashTable()
    {
        for (int i = 0; i < m_tableSize; ++i)
            if (m_items[i])
                delete m_items[i];
        delete[] m_items;

        for (int i = 0; i < m_tableSize; ++i)
            if (m_buckets[i])
                delete m_buckets[i];
        delete[] m_buckets;
    }

    void Add(const std::string & key, Person& value)
    {
        if (m_validCnt + 1 > int(RESIZE_TABLE_FACTOR * m_tableSize)){
            Resize();
        }

        // Create the item
        auto* item = new Person(value);

        // Compute the index
        int index = HashMidSquare(key, m_tableSize);

        if (m_items[index] == nullptr) {
            // Key does not exist.
                       // Insert directly
            m_items[index] = item;
            m_validCnt++;
            m_allCnt++;
        }

        else {
            // Scenario 1: We only need to update value
            if (m_items[index]->NAME ==  key) {
                *m_items[index] = value;
//                m_items[index]->value.NAME = key;
                return;
            }

            else {
                // Scenario 2: Collision
                HandleCollision(index, *item);
                return;
            }
        }
    }


    void Remove(const std::string &key)
    {
        int index = HashMidSquare(key, m_tableSize);
        Person *item = m_items[index];
        List<Person> *bucketHead = m_buckets[index];

        // Если бакет пуст
        if (item == nullptr) {
            return;
        }
        else {
            if ((bucketHead == nullptr) && (item->NAME== key)) {
                // Нет коллизий. Удаляем item
                m_items[index] = nullptr;
                delete[] item;
                m_validCnt--;
                return;
            }
            else if (bucketHead != nullptr) {
                // Существует цепочка коллизий
                if (item->NAME == key) {
                    // удаляем item и меняем "голову" связного списка

                    delete[] item;
                    m_validCnt--;
                    Person tmp = bucketHead->PopFront();
                    m_items[index] = new Person(tmp);
                    return;
                }
                for(int i=0; i<bucketHead->GetSize(); i++){
                    if(bucketHead->Ind(i).NAME == key){
                        bucketHead->RemoveAt(i);
                        m_validCnt--;
                        return;
                    }

                }

            }
        }
    }

    Person* Find(const std::string &key)
    {

        // Searches the key in the hashtable
        // and returns NULL if it doesn't exist
        int index = HashMidSquare(key, m_tableSize);
        Person *item = m_items[index];


        // Ensure that we move to items which are not NULL
        if (item != nullptr) {
            if (item->NAME == key)
                return item;
            if ( m_buckets[index]== nullptr)
                return nullptr;
            for (int i=0; i < m_buckets[index]->GetSize(); i++){
                if(m_buckets[index]->Ind(i).NAME == key) return &m_buckets[index]->Ind(i);
            }
        }
        return nullptr;
    }

    void Print(){
        for(int i=0; i< m_tableSize; i++){
            if (m_items[i] != nullptr){
                std::cout<<" | "<<m_items[i]->NAME;
                std::cout<<" | "<<m_items[i]->ADDRESS;
                std::cout<<" | "<<m_items[i]->PHONE;
                std::cout<<" | "<<m_items[i]->SNILS;
                std::cout<<" |\n";
                if(m_buckets[i] != nullptr){
                    for(int j=0; j<m_buckets[i]->GetSize();j++){
                        std::cout<<" | "<<m_buckets[i]->Ind(j).NAME;
                        std::cout<<" | "<<m_buckets[i]->Ind(j).ADDRESS;
                        std::cout<<" | "<<m_buckets[i]->Ind(j).PHONE;
                        std::cout<<" | "<<m_buckets[i]->Ind(j).SNILS;
                        std::cout<<" |\n";
                    }
                }
            }
        }
    }
};

