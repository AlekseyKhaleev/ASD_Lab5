#pragma once

#include <fstream>
#include <iostream>


template<typename T>
class List
{
public:
    //Конструкторы
    List();

    List(List<T> const &); //copy
    List<T> &operator=(const List<T> &);

    List(List<T> &&) noexcept; //move
    List<T> &operator=(List<T> &&) noexcept;

    //Деструктор
    ~List();

    //Методы
    void PushBack(T);

    T PopFront();

    void Swap(int firstInd, int secondInd);

    [[nodiscard]] int GetSize() const;

    [[nodiscard]] T Ind(int index) const;

    void Clear();

    int FindValue(T value);

    void RemoveAt(int index);

private:
    class Node
    {
    public:
        Node *pNext;
        T *data;

        explicit Node(T *data, Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
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
void List<T>::PushBack(T data)
{
    if (head == nullptr)
    {
        head = new Node(data);
    } else
    {
        Node *current = this->head;
        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node(data);
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
    T value = head->data;
    Node *temp = head;
    head = head->pNext;
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
void List<T>::Swap(int firstInd, int secondInd)
{
    Node *p1, *prev_p1, *p2, *prev_p2, *tmp_pos;
    if(firstInd){
        prev_p2 = head;
        for(int i = 1; i < firstInd; i++)
            prev_p2 = prev_p2->pNext;
        p2 = prev_p2->pNext;}
    else{
// если индекс равен нулю, то предыдущий указатель 0
        prev_p2=0;p2=head;}

    if(secondInd){
        prev_p1 = head;
        for(int i = 1; i < secondInd; i++)
            prev_p1 = prev_p1->pNext;
        p1 = prev_p1->pNext;}
    else{
// если индекс равен нулю, то предыдущий указатель 0
        prev_p1=0;p1=head;}

    if(p2->pNext == p1){
// если элементы находятся рядом, то обмен делаем по-другому
        p2->pNext = p1->pNext;
        p1->pNext=p2;
// проверяем, есть-ли предыдущий
        if(prev_p2)prev_p2->pNext=p1;}

    else

    if(p1->pNext == p2){
// если элементы находятся рядом, то обмен делаем по-другому
        p1->pNext = p2->pNext;
        p2->pNext =p1;
// проверяем, есть-ли предыдущий
        if(prev_p1)prev_p1->pNext=p2;}

    else{
// стандартный обмен
        tmp_pos = p1->pNext;
        p1->pNext = p2->pNext;
        p2->pNext = tmp_pos;
// проверяем, есть-ли предыдущий
        if(prev_p1)          prev_p1->pNext = p2;
        if(prev_p2)          prev_p2->pNext = p1; }

// если индекс был в начале, то меняем начало в классе
    if(firstInd == 0)head = p1;
    if(secondInd == 0)head = p2;

}


template<typename T>
T List<T>::Ind(int index) const
{
    int counter{0};
    Node *current = this->head;
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->pNext;
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
        if (tmp->data == value) return index;
        tmp=tmp->pNext;
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
            previous = previous->pNext;
        }
        Node *temp = previous->pNext;
        previous->pNext = temp->pNext;
        delete[] temp;
    }
    size--;
}
