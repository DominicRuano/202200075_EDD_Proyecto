#pragma once

template <typename T>
class Nodo{
private:
    T data;
    int fila, columna;
    Nodo<T>* next;
    Nodo<T>* prev;
    Nodo<T>* down;
    Nodo<T>* up;

public:
    Nodo(const T& value) : data(value), next(nullptr), prev(nullptr) {}

    T getData() const {return data;}
    void setData(const T& value) {data = value;}

    int getFila() const {return fila;}
    void setFila(int value) {fila = value;}

    int getColumna() const {return columna;}
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
