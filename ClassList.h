#pragma once

#include <fstream>
#include <iostream>


template<typename T>
class List
{
public:
    //Конструкторы
    List();

    List(const List<T>  &); //copy
    List<T> &operator=(const List<T> &);

    List(List<T> &&) noexcept; //move
    List<T> &operator=(List<T> &&) noexcept;

    //Деструктор
    ~List();

    //Методы
    void PushBack(T&);

    T PopFront();

    [[nodiscard]] int GetSize() const;

    [[nodiscard]] T& Ind(int index) const;

    void Clear();

    int FindValue(T value);

    void RemoveAt(int index);

private:
    class Node
    {
    public:
        Node *m_pNext;
        T &m_data;

        explicit Node(T &data, Node *pNext = nullptr): m_data(data)
        {
            m_pNext = pNext;
        }
    };

    int size;
    Node *head;
};

// Конструкторы

//default
template<typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
}

//copy
template<typename T>
List<T>::List(const List<T> &other)
{
    size = 0;
    head = nullptr;
    for (int i = 0; i < other.size; i++)
    {
        PushBack(other.Ind(i));
    }
}

template<typename T>
List<T> &List<T>::operator=(const List<T> &other)
{
    if (&other != this)
    {
        Clear();
        for (int i = 0; i < other.size; i++)
        {
            PushBack(other.Ind(i));
        }
    }
    return *this;
}


//move
template<typename T>
List<T>::List(List<T> &&other) noexcept
{
    size = other.size;
    head = other.head;
}

template<typename T>
List<T> &List<T>::operator=(List<T> &&other) noexcept
{
    if (&other != this)
    {
        Clear();
        size = other.size;
        head = other.head;
    }
    return *this;
}


// Деструктор
template<typename T>
List<T>::~List()
{
    Clear();
}

template<typename T>
void List<T>::PushBack(T &data)
{
    if (head == nullptr)
    {
        head = new Node(data);
    } else
    {
        Node *current = this->head;
        while (current->m_pNext != nullptr)
        {
            current = current->m_pNext;
        }
        current->m_pNext = new Node(data);
    }
    size++;
}


template<typename T>
int List<T>::GetSize() const{
    return this->size;
}



template<typename T>
T List<T>::PopFront()
{
    T value = head->m_data;
    Node *temp = head;
    head = head->m_pNext;
    delete temp;
    size--;
    return value;
}


template<typename T>
void List<T>::Clear()
{
    while (size)
    {
        this->PopFront();
    }
}


template<typename T>
T& List<T>::Ind(int index) const
{
    int counter{0};
    Node *current = this->head;
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->m_data;
        }
        current = current->m_pNext;
        counter++;
    }
    throw std::exception();
}


//  поиск по значению, при отсутствии элемента вернет -1, иначе индекс элемента
template<typename T>
int List<T>::FindValue(T value){
    int index=0;
    Node* tmp = head;
    while(tmp != nullptr){
        if (tmp->m_data == value) return index;
        tmp=tmp->m_pNext;
        index++;
    }
    return -1;
}

template<typename T>
void List<T>::RemoveAt(int index)
{
    if (index > size - 1)
    {
        throw std::exception();
    }

    if (index == 0)
    {
        PopFront();
    } else
    {
        Node *previous = this->head;
        for (int i = 0; i < index - 1; i++)
        {
            previous = previous->m_pNext;
        }
        Node *temp = previous->m_pNext;
        previous->m_pNext = temp->m_pNext;
        delete[] temp;
    }
    size--;
}
