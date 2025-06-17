#pragma once
#include "Stack.h"

template <typename T>
Stack<T>::Stack() : top(-1) {}

template <typename T>
bool Stack<T>::push(const T& item) {
    if (top >= MAX_STACK_SIZE - 1) return false;
    data[++top] = item;
    return true;
}

template <typename T>
bool Stack<T>::pop(T& item) {
    if (top < 0) return false;
    item = data[top--];
    return true;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top < 0;
}

template <typename T>
void Stack<T>::clear() {
    top = -1;
}