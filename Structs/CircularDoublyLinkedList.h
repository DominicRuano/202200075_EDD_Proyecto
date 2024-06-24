#include "../Objects/nodo.h"
using namespace std;


template <typename T>
class CircularDoublyLinkedList{
private:
    Nodo<T> *head;
    int length = 0;
    //Nodo<T> *current;
public:
    CircularDoublyLinkedList(/* args */);
    ~CircularDoublyLinkedList();

    void insert(T &value);
    T remove(string vuelo);
    int getLength(){return length;}
    void Print();
    void graph(ofstream &filem, string ID, string str);
};

template <typename T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(/* args */){
    head = nullptr;
}
template <typename T>
CircularDoublyLinkedList<T>::~CircularDoublyLinkedList(){
    // Pendiente de implementar
}

template <typename T>
void CircularDoublyLinkedList<T>::insert(T &Value){
    Nodo<T>* nuevoNodo = new Nodo<T>(Value);
    if (!head){
        head = nuevoNodo;
        head->next = head;
        head->prev = head;
    }else{
        Nodo<T>* ultimoNodo = head->prev;
        ultimoNodo->next = nuevoNodo;
        nuevoNodo->prev = ultimoNodo;
        nuevoNodo->next = head;
        head->prev = nuevoNodo;
    }
    length++;
}

template <typename T>
T CircularDoublyLinkedList<T>::remove(string vuelo) {
    if (length == 0)
        throw std::out_of_range("Lista vacía.\n");

    Nodo<T>* current = head;

    // Encontrar el nodo con el vuelo especificado
    do {
        if (current->data.getNumDeRegistro() == vuelo) {
            T data = current->data;
            // Caso de un solo elemento en la lista
            if (length == 1) {
                head = nullptr;
            } else {
                Nodo<T>* prev = current->prev;
                Nodo<T>* next = current->next;
                prev->next = next;
                next->prev = prev;
                if (current == head) {
                    head = next;
                }
            }
            delete current;
            length--;
            return data;
        }
        current = current->next;
    } while (current != head);

    throw std::out_of_range("Vuelo no encontrado.\n");
}


template <typename T>
void CircularDoublyLinkedList<T>::Print(){
    Nodo<T>* current = head;
    if (length > 0)
        for (int i = 0; i < length; i++){
            current->data.print();
            cout << "---------------------------" << endl;
            current = current->next;
        }
    else 
        out_of_range("Lista vacia.\n");
}

template <typename T>
void CircularDoublyLinkedList<T>::graph(ofstream &file, string ID, string str){
    Nodo<T>* current = head;
    file << "subgraph cluster_" << ID << " {" << endl;
    file << "\tlabel=\"" << str << "\";" << endl;
    file << "\tcolor=blue;" << endl;
    if (length > 0){
        for (int i = 0; i < length; i++){
            file << "\tstruct" << ID << i << " [label=\"Vuelo: " << current->data.getVuelo() << "\\nNo.Registro: " << current->data.getNumDeRegistro() << "\\nEstado: " << current->data.getEstado() << "\"]" << endl;
            if (i > 0){
                file << "\tstruct" << ID << i-1 << " -> struct"<< ID << i << ";" << endl;
                file << "\tstruct" << ID << i << " -> struct" << ID << i-1 << ";" << endl;
            }
            current = current->next;
        }
        file << "\tstruct" << ID << length-1 << " -> struct" << ID << "0;" << endl;
        file << "\tstruct" << ID << "0 -> struct" << ID << length-1 << ";" << endl;
        file << "head" << ID << "0 [label=\"Head\", margin=0, style=filled, color=none, fillcolor=none]" << endl;
        file << "head" << ID << "1 [label=\"Tail\", margin=0, style=filled, color=none, fillcolor=none]" << endl;
        file << "{rank=same;struct" << ID << "0;head" << ID << "0;}" << endl;
        file << "{rank=same;struct" << ID << length - 1 << ";head" << ID << "1;}" << endl;
        file << "head" << ID << "0 -> struct"<< ID <<"0;" << endl;
        file << "head" << ID << "1 -> struct"<< ID << length - 1 << ";" << endl;
    }else{
        file << "node [margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl; 
        file << "\tstruct" << ID << "0 [label=\"Lista Vacia!\", margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl;
    }
    file << "}" << endl;
}