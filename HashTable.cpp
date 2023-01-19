#include "HashTable.h"

void HashTable::Resize() {
    int past_buffer_size = m_buffer_size;
    m_buffer_size *= 2;
    m_size_all_non_nullptr = 0;
    m_size = 0;
    Item** arr2 = new Item * [m_buffer_size];
    for (int i = 0; i < m_buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(m_arr, arr2);
    for (int i = 0; i < past_buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->m_state)
            Add(arr2[i]->m_value->NAME, *arr2[i]->m_value);
    }
    for (int i = 0; i < past_buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
}


void HashTable::Rehash() {
    m_size_all_non_nullptr = 0;
    m_size = 0;
    Item** arr2 = new Item * [m_buffer_size];
    for (int i = 0; i < m_buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(m_arr, arr2);
    for (int i = 0; i < m_buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->m_state)
            Add(arr2[i]->m_value->NAME, *arr2[i]->m_value);
    }
    for (int i = 0; i < m_buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
}


HashTable::HashTable() {
    m_buffer_size = DEFAULT_SIZE;
    m_size = 0;
    m_size_all_non_nullptr = 0;
    m_arr = new Item*[m_buffer_size];
    for (int i = 0; i < m_buffer_size; ++i)
        m_arr[i] = nullptr;
    Add("Name", *new Person("Address", "Phone", "SNILS"));
}


HashTable::~HashTable() {
    for (int i = 0; i < m_buffer_size; ++i)
        if (m_arr[i])
            delete m_arr[i];
    delete[] m_arr;
}


bool HashTable::Add(const std::string &key, Person &value) {
    if (m_size + 1 > int(REHASH_SIZE * m_buffer_size))
        Resize();
    else if (m_size_all_non_nullptr > 2 * m_size)
        Rehash();
    int hash = HashMidSquare(key, m_buffer_size);
    int i = 0;
    int first_deleted = -1;

    // разрешение коллизий (метод цепочек)
    while (m_arr[hash] != nullptr && i < m_buffer_size)
    {
        if (*m_arr[hash]->m_value == value && m_arr[hash]->m_state)
            return false;
        if (!m_arr[hash]->m_state && first_deleted == -1)
            first_deleted = hash;
        hash %= m_buffer_size;
        ++i;
    }
    if (first_deleted == -1)
    {
        m_arr[hash] = new Item(value);
        m_arr[hash]->m_value->NAME=key;
        m_keys.PushBack(hash);
        ++m_size_all_non_nullptr;
    }
    else
    {
        *m_arr[first_deleted]->m_value = value;
        m_arr[first_deleted]->m_value->NAME = key;
        m_arr[first_deleted]->m_state = true;
        m_keys.PushBack(first_deleted);
    }
    ++m_size;
    return true;
}

bool HashTable::Remove(const T &key) {
    int hash = HashMidSquare(key, m_buffer_size);
    int i = 0;
    while (m_arr[hash] != nullptr && i < m_buffer_size)
    {
        if (m_arr[hash]->m_value.NAME == key && m_arr[hash]->m_state)
        {
            m_arr[hash]->m_state = false;

            --m_size;
            m_keys.RemoveAt(m_keys.FindValue(hash));
            return true;
        }
        hash %= m_buffer_size;
        ++i;
    }
    return false;
}


bool HashTable::Find(const T &value) {
    int hash = HashMidSquare(value, m_buffer_size);
    int i = 0;
    while (m_arr[hash] != nullptr && i < m_buffer_size)
    {
        if (m_arr[hash]->m_key == value && m_arr[hash]->m_state)
            return true;
        hash %= m_buffer_size;
        ++i;
    }
    return false;
}


void HashTable::Print() {
    for (int i=0; i<m_keys.GetSize();i++){
        std::cout << std::setprecision(10) << m_arr[m_keys.Ind(i)]->m_value.NAME << " | ";
        std::cout << std::setprecision(10) << m_arr[m_keys.Ind(i)]->m_value.ADDRESS << " | ";
        std::cout << std::setprecision(10) << m_arr[m_keys.Ind(i)]->m_value.PHONE << " | ";
        std::cout << std::setprecision(10) << m_arr[m_keys.Ind(i)]->m_value.SNILS << " | ";
        std::cout<<std::endl;

    }
}

