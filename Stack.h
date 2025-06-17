#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    static const int MAX_STACK_SIZE = 100;
    T data[MAX_STACK_SIZE];
    int top;
public:
    Stack();
    bool push(const T& item);
    bool pop(T& item);
    bool isEmpty() const;
    void clear();
};

#include "Stack.cpp"

#endif