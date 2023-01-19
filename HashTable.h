#pragma once

#include <iostream>
#include <iomanip>

#include "ClassList.h"
#include "Utils.h"


template<typename T=Person>
class HashTable
{
    static const int DEFAULT_TABLE_SIZE = 8;
    constexpr static const double RESIZE_TABLE_FACTOR = 0.75;
    struct Item
    {
        T value;
        explicit Item(const T& value_) : value(value_) {}
    };

    int m_allCnt;
    int m_tableSize;
    int m_validCnt;

    Item** m_items;
    List<Item>* m_buckets;

    void Resize()
    {
        int previousTableSize = m_tableSize;
        m_tableSize *= 2;
        m_allCnt = 0;
        m_validCnt = 0;
        Item** arr2 = new Item * [m_tableSize];
        for (int i = 0; i < m_tableSize; ++i)
            arr2[i] = nullptr;
        std::swap(m_items, arr2);
        for (int i = 0; i < previousTableSize; ++i)
        {
            if (arr2[i] && arr2[i]->state)
                Add(arr2[i]->value);
        }
        for (int i = 0; i < previousTableSize; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

    void Rehash()
    {
        m_allCnt = 0;
        m_validCnt = 0;
        Item** arr2 = new Item * [m_tableSize];
        for (int i = 0; i < m_tableSize; ++i)
            arr2[i] = nullptr;
        std::swap(m_items, arr2);
        for (int i = 0; i < m_tableSize; ++i)
        {
            if (arr2[i] && arr2[i]->state)
                Add(arr2[i]->value);
        }
        for (int i = 0; i < m_tableSize; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

    void HandleCollision(int index, Item item) {
        List<Item> *head = m_buckets[index];
        if (head == nullptr) {
            // We need to create the list
            head = new List<Item>(item);
            m_buckets[index] = head;
            return;
        } else {
            // Insert to the list
            m_buckets[index].PushBack(item);
            return;
        }
    }


public:
    HashTable()
    {
        m_tableSize = DEFAULT_TABLE_SIZE;
        m_validCnt = 0;
        m_allCnt = 0;

        m_items = new Item*[m_tableSize];
        for (int i = 0; i < m_tableSize; ++i)
            m_items[i] = nullptr;

        m_buckets = new List<Item>[m_tableSize];
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

    void Add(const std::string & key, const T& value)
    {
        if (m_validCnt + 1 > int(RESIZE_TABLE_FACTOR * m_tableSize))
            Resize();
        else if (m_allCnt > 2 * m_validCnt)
            Rehash();

        // Create the item
        Item* item = new Item(key, value);

        // Compute the index
        int index = HashMidSquare(key, m_tableSize);

        if (m_items[index] == NULL) {
            // Key does not exist.
                       // Insert directly
            m_items[index] = item;
            m_validCnt++;
            m_allCnt++;
        }

        else {
            // Scenario 1: We only need to update value
            if (m_items[index]->value.NAME ==  key) {
                m_items[index]->value = value;
//                m_items[index]->value.NAME = key;
                return;
            }

            else {
                // Scenario 2: Collision
                HandleCollision(index, item);
                return;
            }
        }
    }


    void Remove(const std::string &key)
    {
        int index = HashMidSquare(key, m_tableSize);
        Item *item = m_items[index];
        List<Item> *bucketHead = m_buckets[index];

        // Если бакет пуст
        if (item == nullptr) {
            return;
        }
        else {
            if ((bucketHead == nullptr) && (item->value.NAME== key)) {
                // Нет коллизий. Удаляем item
                m_items[index] = nullptr;
                delete[] item;
                m_validCnt--;
                return;
            }
            else if (bucketHead != nullptr) {
                // Существует цепочка коллизий
                if (item->value.NAME== key) {
                    // удаляем item и меняем "голову" связного списка

                    delete[] item;
                    m_validCnt--;
                    Item *tmp = bucketHead->PopFront();
                    m_items[index] = new Item(tmp->value);
                    return;
                }
                for(int i=0; i<bucketHead->GetSize(); i++){
                    if(bucketHead->Ind(i).value.NAME == key){
                        bucketHead->RemoveAt(i);
                        m_validCnt--;
                        return;
                    }

                }

            }
        }
    }

    T* Find(const std::string &key)
    {
        // Searches the key in the hashtable
        // and returns NULL if it doesn't exist
        int index = HashMidSquare(key, m_tableSize);
        Item *item = m_items[index];
        List<Item> *bucketHead = m_buckets[index];

        // Ensure that we move to items which are not NULL
        if (item != nullptr) {
            if (item->value.NAME == key)
                return item->value;
            if (bucketHead == nullptr)
                return nullptr;
            for (int i=0; i < bucketHead->GetSize(); i++){
                if(bucketHead->Ind(i).value.NAME == key) return bucketHead->Ind(i).value;
            }
        }
        return nullptr;
    }
};

