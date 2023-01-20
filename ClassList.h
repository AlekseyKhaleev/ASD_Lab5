#pragma once

#include <fstream>
#include <iostream>

#include "Utils.h"

namespace ClassList {
    template<typename T>
    struct Node {
        Node *m_pNext;
        T m_data;

        explicit Node(const T &data, Node *pNext = nullptr) : m_data(data) {
            m_pNext = pNext;
        }
    };




    template<typename T>
    class List {
    public:
        Node<T> *head;

        //Конструкторы
        List();

        List(const List<T> &); //copy
        List<T> &operator=(const List<T> &);

        List(List<T> &&) noexcept; //move
        List<T> &operator=(List<T> &&) noexcept;

        //Деструктор
        ~List();

        //Методы
        void PushBack(T &);

        T PopFront();

        [[nodiscard]] int GetSize() const;

        [[nodiscard]] T &Ind(int index) const;

        void Clear();

        void RemoveAt(int index);

        void RemoveValue(const std::string &value);

        bool IsEmpty();

    private:

        int size;
    };

// Конструкторы

//default
    template<typename T>
    List<T>::List() {
        size = 0;
        head = nullptr;
    }

//copy
    template<typename T>
    List<T>::List(const List<T> &other) {
        size = 0;
        head = nullptr;
        for (int i = 0; i < other.size; i++) {
            PushBack(other.Ind(i));
        }
    }

    template<typename T>
    List<T> &List<T>::operator=(const List<T> &other) {
        if (&other != this) {
            Clear();
            for (int i = 0; i < other.size; i++) {
                PushBack(other.Ind(i));
            }
        }
        return *this;
    }


//move
    template<typename T>
    List<T>::List(List<T> &&other) noexcept {
        size = other.size;
        head = other.head;
    }

    template<typename T>
    List<T> &List<T>::operator=(List<T> &&other) noexcept {
        if (&other != this) {
            Clear();
            size = other.size;
            head = other.head;
        }
        return *this;
    }


// Деструктор
    template<typename T>
    List<T>::~List() {
        Clear();
    }

    template<typename T>
    void List<T>::PushBack(T &data) {
        if (head == nullptr) {
            head = new Node(data);
        } else {
            Node<T> *current = this->head;
            while (current->m_pNext != nullptr) {
                current = current->m_pNext;
            }
            current->m_pNext = new Node(data);
        }
        size++;
    }


    template<typename T>
    int List<T>::GetSize() const {
        return this->size;
    }


    template<typename T>
    T List<T>::PopFront() {
        T value = head->m_data;
        Node<T> *temp = head;
        head = head->m_pNext;
        delete temp;
        size--;
        return value;
    }


    template<typename T>
    void List<T>::Clear() {
        while (size) {
            this->PopFront();
        }
    }


    template<typename T>
    T &List<T>::Ind(int index) const {
        int counter{0};
        Node<T> *current = this->head;
        while (current != nullptr) {
            if (counter == index) {
                return current->m_data;
            }
            current = current->m_pNext;
            counter++;
        }
        throw std::exception();
    }


    template<typename T>
    void List<T>::RemoveAt(int index) {
        if (index > size - 1) {
            throw std::exception();
        }

        if (index == 0) {
            PopFront();
        } else {
            Node<T> *previous = this->head;
            for (int i = 0; i < index - 1; i++) {
                previous = previous->m_pNext;
            }
            Node<T> *temp = previous->m_pNext;
            previous->m_pNext = temp->m_pNext;
            delete temp;
        }
        size--;
    }

    template<typename T>
    bool List<T>::IsEmpty() {
        return (head == nullptr);
    }

    template<typename T>
    void List<T>::RemoveValue(const std::string &value) {
        Node<T> *previous = this->head;
        if (previous->m_data == value) PopFront();
        else {
            while (previous != nullptr) {
                if (previous->m_pNext->m_data == value) {
                    Node<T> *temp = previous->m_pNext;
                    previous->m_pNext = temp->m_pNext;
                    delete temp;
                    size--;
                    return;
                }
                previous = previous->m_pNext;
            }
        }
    }
}