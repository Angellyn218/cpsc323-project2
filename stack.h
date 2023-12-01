#include <stdexcept>
#include <string>
#include <sstream>

#ifndef STACK_H
#define STACK_H

template<typename S>
struct Node
{
    S item;
    Node<S>* next{nullptr};
}; // end node

template<typename T>
class Stack
{
public:
    ~Stack() { while(!empty()) pop(); }

    bool empty() { return head == nullptr; }
    
    void push(const T& item) { head = new Node<T>{item, head}; }
    
    void pop()
    {
        if (empty()) throw std::runtime_error("invalid pop operation on empty stack");
        Node<T>* tmp{head};
        head = head->next;
        delete tmp;
    }

    T peek()
    {
        if (empty()) throw std::runtime_error("invalid peek on empty stack");
        return head->item;
    }

    std::string getString()
    {
        std::stringstream str;
        Node<T>* ptr{head};

        while (ptr != nullptr)
        {
            str << ptr->item << " ";
            ptr = ptr->next;
        }

        return str.str();
    }

private:
    Node<T>* head{nullptr};
}; // end stack

#endif