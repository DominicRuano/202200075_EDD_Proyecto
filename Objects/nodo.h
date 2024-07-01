#pragma once

#include <string>
using namespace std;

template <typename T>
class Nodo{
public:
    T data;
    string fila, columna;
    Nodo<T>* next;
    Nodo<T>* prev;
    Nodo<T>* down;
    Nodo<T>* up;

    Nodo(){}
    Nodo(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    Nodo(const string F, string C) : fila(F), columna(C) , next(nullptr), prev(nullptr) {}

    T getData() const {return data;}
    void setData(const T& value) {data = value;}

    string getFila() const {return fila;}
    void setFila(int value) {fila = value;}

    string getColumna() const {return columna;}
    void setColumna(int value) {columna = value;}

    Nodo<T>* getNext() const {return next;}
    void setNext(Nodo<T>* node) {next = node;}

    Nodo<T>* getPrev() const {return prev;}
    void setPrev(Nodo<T>* node) {prev = node;}

    Nodo<T>* getDown() const {return down;}
    void setDown(Nodo<T>* node) {down = node;}

    Nodo<T>* getUp() const {return up;}
    void setUp(Nodo<T>* node) {up = node;}
};
