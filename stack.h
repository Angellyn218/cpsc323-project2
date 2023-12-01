#include <stdexcept>

#ifndef STACK_H
#define STACK_H

struct FullStackError : public std::runtime_error
{
    FullStackError() : std::runtime_error("invalid operation on a full stack") {}
    FullStackError(const std::string& msg) : std::runtime_error(msg) {}
};

struct EmptyStackError : public std::runtime_error
{
    EmptyStackError() : std::runtime_error("invalid operation on an empty stack") {}
    EmptyStackError(const std::string& msg) : std::runtime_error(msg) {}
};

template<typename T, size_t S>
class Stack 
{
public:
    // bool empty() Returns true if stack is empty or false otherwise
    bool empty() { return top == 0; }

    // void push(T item) Adds item at top of the stack or throws error if stack full
    void push(const T& item)
    {
        if(top == S) throw FullStackError();
        store[top++] = item;
    }

    // void pop() Removes item at top of the stack or throws error if stack empty
    void pop()
    {
        if(empty()) throw EmptyStackError();
        --top;
    }

    // T peek() Returns item at top of stack or throws error if stack empty
    T peek() 
    { 
        if(empty()) throw EmptyStackError();
        return store[top - 1]; 
    }
    
private:
    T store[S];
    size_t top{0};
};

#endif