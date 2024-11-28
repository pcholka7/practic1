#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template<typename T>
struct ListNode
{
    T data;
    ListNode<T>* next;
    ListNode<T>* previous;

    ListNode(T data) : data(data), next(nullptr), previous(nullptr) {}
};

template<typename T>
class LinkedList
{
private:
    int listSize;
    ListNode<T>* head;
    ListNode<T>* tail;

public:
    LinkedList() : listSize(0), head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList()
    {
        while (!isEmpty())
        {
            removeHead();
        }
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void addHead(T value)
    {
        ListNode<T>* newNode = new ListNode<T>(value);
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }
        listSize++;
    }

    void addTail(T value)
    {
        ListNode<T>* newNode = new ListNode<T>(value);
        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        listSize++;
    }

    void removeHead()
    {
        if (isEmpty())
        {
            throw runtime_error("List is empty");
        }
        ListNode<T>* nextNode = head->next;
        delete head;
        head = nextNode;
        if (head)
        {
            head->previous = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        listSize--;
    }

    void removeTail()
    {
        if (isEmpty())
        {
            throw runtime_error("List is empty");
        }
        ListNode<T>* previousNode = tail->previous;
        delete tail;
        tail = previousNode;
        if (tail)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        listSize--;
    }

    void removeValue(T value)
    {
        if (isEmpty())
        {
            throw runtime_error("List is empty");
        }

        ListNode<T>* currentNode = head;
        while (currentNode != nullptr)
        {
            if (currentNode->data == value)
            {
                if (currentNode == head)
                {
                    removeHead();
                }
                else if (currentNode == tail)
                {
                    removeTail();
                }
                else
                {
                    currentNode->previous->next = currentNode->next;
                    currentNode->next->previous = currentNode->previous;
                    delete currentNode;
                    listSize--;
                }
                return;
            }
            currentNode = currentNode->next;
        }
        cout << "Element \"" << value << "\" not found in the list!" << "\n";
    }

    bool contains(T value)
    {
        ListNode<T>* currentNode = head;
        while (currentNode != nullptr)
        {
            if (currentNode->data == value)
            {
                cout << "Element \"" << currentNode->data << "\" found in the list!" << "\n";
                return true;
            }
            currentNode = currentNode->next;
        }
        return false;
    }

    T get(int index) const
    {
        if (isEmpty())
        {
            throw runtime_error("List is empty");
        }

        if (index < 0 || index >= listSize)
        {
            throw runtime_error("Index out of bounds");
        }

        ListNode<T>* currentNode = head;
        for (int currentIndex = 0; currentIndex < index; currentIndex++)
        {
            currentNode = currentNode->next;
        }
        return currentNode->data;
    }

    int size() const
    {
        return listSize;
    }

    void print() const
    {
        ListNode<T>* currentNode = head;
        while (currentNode != nullptr)
        {
            cout << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }
};
