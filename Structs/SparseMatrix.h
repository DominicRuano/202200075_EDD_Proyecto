#include "../Objects/nodo.h"
#include <string>
using namespace std;

template <class T>
class SparseMatrix{
private:
    Nodo<T>* head;
public:
    SparseMatrix(/* args */);
    ~SparseMatrix();

    Nodo<T>* getHead(){return head;}

    Nodo<T>* BuscarFil(string fila);
    Nodo<T>* BuscarCol(string columna);
    Nodo<T>* CrearFil(string fila);
    Nodo<T>* CrearCol(string columna);
    void Insertar(string fila, string columna, T data);
};

/*
    Inserta un nodo en la matriz.
*/
template <class T>
void SparseMatrix<T>::Insertar(string fila, string columna, T data){
    Nodo<T>* New = new Nodo<T>(data);
    New->setColumna(columna);
    Nodo<T>* CurrentFil = BuscarFil(fila);
    Nodo<T>* CurrentCol = BuscarCol(columna);
    
    if (CurrentFil == nullptr && CurrentCol == nullptr){
        CurrentFil = CrearFil(fila);
        CurrentCol = CrearCol(columna);
        New->setUp(CurrentCol);
        New->setPrev(CurrentFil);
        CurrentFil->setNext(New);
        CurrentCol->setDown(New);
    } else if (CurrentFil == nullptr && CurrentCol != nullptr){
        CurrentFil = CrearFil(fila);
        New->setUp(CurrentCol);
        New->setPrev(CurrentFil);
        CurrentFil->setNext(New);
        CurrentCol->setDown(New);
    } else if (CurrentFil != nullptr && CurrentCol == nullptr){
        CurrentCol = CrearCol(columna);
        New->setUp(CurrentCol);
        New->setPrev(CurrentFil);
        CurrentFil->setNext(New);
        CurrentCol->setDown(New);
    } else {
        New->setUp(CurrentCol);
        New->setPrev(CurrentFil);
        CurrentFil->setNext(New);
        CurrentCol->setDown(New);
    }
}

/*
    Inserta un nodo en la matriz y retorna el nodo insertado.
*/
template <class T>
Nodo<T>* SparseMatrix<T>::CrearCol(string columna){
    Nodo<T>* Current = head;
    while (Current->getNext() != nullptr)
        Current = Current->getNext();
    Nodo<string>* New = new Nodo<string>("-1",columna);
    New->setFila(-1);
    New->setColumna(columna);
    New->setNext(Current->getNext());
    Current->setNext(New);
    return New;
}

/*
    Inserta un nodo en la matriz y retorna el nodo insertado.
*/
template <class T>
Nodo<T>* SparseMatrix<T>::CrearFil(string fila){
    Nodo<T>* Current = head;
    while (Current->getDown() != nullptr)
        Current = Current->getDown();
    Nodo<string>* New = new Nodo<string>(fila, "-1");
    New->setFila(fila);
    New->setColumna(-1);
    New->setDown(Current->getDown());
    Current->setDown(New);
    return New;
}

/*
    Retorna el nodo que se encuentra en la fila indicada o nullptr si no existe.
*/
template <class T>
Nodo<T>* SparseMatrix<T>::BuscarCol(string columna){
    Nodo<T>* Current = head;
    while (Current->getNext() != nullptr)
        if (Current->getColumna() == columna)
            return Current;
        Current = Current->getNext();
    return nullptr;
}

/*
    Retorna el nodo que se encuentra en la columna indicada o nullptr si no existe.
*/
template <class T>
Nodo<T>* SparseMatrix<T>::BuscarFil(string fila){
    Nodo<T>* Current = head;
    while (Current->getDown() != nullptr)
        if (Current->getFila() == fila)
            return Current;
        Current = Current->getDown();
    return nullptr;
}

template <class T>
SparseMatrix<T>::SparseMatrix(/* args */){
    head = Nodo<string>("-1","-1");
}

template <class T>
SparseMatrix<T>::~SparseMatrix(){
    Nodo<string>* Current = head;
    while (Current != nullptr){
        Nodo<T>* temp = Current->getNext();
        while (temp != nullptr){
            Nodo<T>* temp2 = temp->getNext();
            delete temp;
            temp = temp2;
        }
        Nodo<T>* temp3 = Current->getDown();
        delete Current;
        Current = temp3;
    }
}