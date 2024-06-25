#include "../Objects/nodo.h"
using namespace std;

template <typename T>
class ArbolBB{
private:
    Nodo<T>* root;
public:
    ArbolBB(/* args */);
    ~ArbolBB();

    bool estaVacion(){return root == nullptr;}
    
    void Insertar(T dato);
    Nodo<T>* Insertar(Nodo<T>* nodo, T dato);
    void InOrden(Nodo<T>* nodo);
    void PreOrden(Nodo<T>* nodo);
    void PostOrden(Nodo<T>* nodo);
};

template <typename T>
ArbolBB<T>::ArbolBB(/* args */){
    root = nullptr;
}

template <typename T>
ArbolBB<T>::~ArbolBB(){

}

template <typename T>
void ArbolBB<T>::Insertar(T dato){
    root = Insertar(root, dato);
}

template <typename T>
Nodo<T>* ArbolBB<T>::Insertar(Nodo<T>* nodo, T dato){
    if(nodo == nullptr)
        return new Nodo<T>(dato);
    if(dato.getHorasDeVuelo() < nodo->data.getHorasDeVuelo())
        nodo->left = Insertar(nodo->left, dato);
    else if(dato.getHorasDeVuelo() > nodo->data.getHorasDeVuelo())
        nodo->right = Insertar(nodo->right, dato);
    else{
        cout << "Nodo:\n" << dato << "\n\tNo insertado." << endl;
    }
    return nodo;
}

template <typename T>
void ArbolBB<T>::InOrden(Nodo<T>* nodo){
    if(nodo == nullptr){ return; }
    InOrden(nodo->left);
    cout << nodo->data << endl;
    InOrden(nodo->right);
}

template <typename T>
void ArbolBB<T>::PreOrden(Nodo<T>* nodo){
    if(nodo == nullptr)
        return;
    cout << nodo->data << endl;
    PreOrden(nodo->left);
    PreOrden(nodo->right);
}

template <typename T>
void ArbolBB<T>::PostOrden(Nodo<T>* nodo){
    if(nodo == nullptr)
        return;
    PostOrden(nodo->left);
    PostOrden(nodo->right);
    cout << nodo->data << endl;
}

