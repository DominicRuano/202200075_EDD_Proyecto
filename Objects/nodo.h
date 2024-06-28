#pragma once

template <typename T>
class Nodo{
public:
    T data;
    Nodo<T>* next;
    Nodo<T>* prev;
    Nodo<T>* down;
    Nodo<T>* up;

    Nodo(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};