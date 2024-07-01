#include "../Objects/nodo.h"
//#include "../Structs/DoublyLinkedList.h"
using namespace std;

template <typename T>
class ArbolBB{
private:
    Nodo<T>* root;
public:
    ArbolBB(/* args */);
    ~ArbolBB();

    bool estaVacion(){return root == nullptr;}
    Nodo<T>* getRoot(){return root;}
    DoublyLinkedList<T>* getPilotos(){return Pilotos;}
    
    void Insertar(T dato);
    Nodo<T>* Insertar(Nodo<T>* nodo, T dato);
    void InOrden();
    void InOrden(Nodo<T>* nodo);
    void PreOrden();
    void PreOrden(Nodo<T>* nodo);
    void PostOrden();
    void PostOrden(Nodo<T>* nodo);
    void graph(ofstream &file, string ID, string str);
    void InOrdenGraficar(Nodo<T>* nodo, ofstream &file, string ID, int& i);

    DoublyLinkedList<T>* Pilotos;


};

template <typename T>
ArbolBB<T>::ArbolBB(/* args */){
    root = nullptr;
    Pilotos = new DoublyLinkedList<T>();
}

template <typename T>
ArbolBB<T>::~ArbolBB(){

}

template <typename T>
void ArbolBB<T>::Insertar(T dato){
    root = Insertar(root, dato);
    Pilotos->addEnd(dato);
}

template <typename T>
Nodo<T>* ArbolBB<T>::Insertar(Nodo<T>* nodo, T dato){
    if(nodo == nullptr)
        return new Nodo<T>(dato);
    if(dato.getHorasDeVuelo() > nodo->data.getHorasDeVuelo())
        nodo->next = Insertar(nodo->next, dato);
    else if(dato.getHorasDeVuelo() < nodo->data.getHorasDeVuelo())
        nodo->prev = Insertar(nodo->prev, dato);
    else{
        cout << "Nodo:\n" << dato << "\n\tNo insertado." << endl;
    }
    return nodo;
}

template <typename T>
void ArbolBB<T>::InOrden(){
    if(root == nullptr){ return; }
    InOrden(root->prev);
    cout << root->data << endl;
    InOrden(root->next);
}

template <typename T>
void ArbolBB<T>::InOrden(Nodo<T>* nodo){
    if(nodo == nullptr){ return; }
    InOrden(nodo->prev);
    cout << nodo->data << endl;
    InOrden(nodo->next);
}

template <typename T>
void ArbolBB<T>::PreOrden(){
    if(root == nullptr)
        return;
    cout << root->data << endl;
    PreOrden(root->prev);
    PreOrden(root->next);
}

template <typename T>
void ArbolBB<T>::PreOrden(Nodo<T>* nodo){
    if(nodo == nullptr)
        return;
    cout << nodo->data << endl;
    PreOrden(nodo->prev);
    PreOrden(nodo->next);
}

template <typename T>
void ArbolBB<T>::PostOrden(){
    if(root == nullptr)
        return;
    PostOrden(root->prev);
    PostOrden(root->next);
    cout << root->data << endl;
}

template <typename T>
void ArbolBB<T>::PostOrden(Nodo<T>* nodo){
    if(nodo == nullptr)
        return;
    PostOrden(nodo->prev);
    PostOrden(nodo->next);
    cout << nodo->data << endl;
}

template <typename T>
void ArbolBB<T>::graph(ofstream &file, string ID, string str){
    int i = 0;
    Nodo<T>* current = root;
    file << "subgraph cluster_" << ID << " {" << endl;
    file << "\tlabel=\"" << str << "\"; \n\tnode [shape=hexagon, style=filled, fillcolor=lightblue];" << endl;
    file << "\tcolor=red;" << endl;
    if (root != nullptr){
        InOrdenGraficar(current, file, ID, i);
    }else{
        file <<"node [margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl; 
        file << "\tstruct" << ID << "0 [label=\"ArbolBB Vacio!\"];\n}\nagencia -> structC0[style=dotted];" << endl;
        return;
    }
    file << "}\n agencia -> \"" << root->data.to_string() << "\" [style=dotted]" << endl;

}

template <typename T>
void ArbolBB<T>::InOrdenGraficar(Nodo<T>* nodo, ofstream &file, string ID, int& i){
    if(nodo == nullptr){return; }
    //file << "\t\""<< nodo->data <<" \"" << endl;
    if(nodo->prev != nullptr){
        file << "\t\""<< nodo->data.to_string() << "\" -> \"" << nodo->prev->data.to_string() <<"\""<< endl;
    }
    if(nodo->next != nullptr){
        file << "\t\""<< nodo->data.to_string() << "\" -> \"" << nodo->next->data.to_string() <<"\""<< endl;
    }
    InOrdenGraficar(nodo->next, file, ID, i);
    InOrdenGraficar(nodo->prev, file, ID, i);
}
