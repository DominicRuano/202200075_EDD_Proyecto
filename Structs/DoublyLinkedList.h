#include "../Objects/nodo.h"

template <class T>
class DoublyLinkedList{
private:
    Nodo<T> *head;
    int length = 0;
public:
    DoublyLinkedList(/* args */);
    ~DoublyLinkedList();

    void add(T &val);
    void Print();
    void consultar(string pasaporte);
    void graph(ofstream &file, string ID, string str);
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(/* args */){
    head = nullptr;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    // Pendiente de implementar
}

template <class T>
void DoublyLinkedList<T>::add(T &val) {
    Nodo<T> *NuevoNodo = new Nodo<T>(val);
    if (!head) {
        head = NuevoNodo;
    } else {
        Nodo<T> *current = head;
        while ((current->data.getVuelo() > NuevoNodo->data.getVuelo() ||
                (current->data.getVuelo() == NuevoNodo->data.getVuelo() && current->data.getAsiento() > NuevoNodo->data.getAsiento())) &&
            current->next != nullptr) {
            current = current->next;
        }
        
        if (current->next == nullptr && 
            (current->data.getVuelo() > NuevoNodo->data.getVuelo() ||
            (current->data.getVuelo() == NuevoNodo->data.getVuelo() && current->data.getAsiento() > NuevoNodo->data.getAsiento()))) {
            current->next = NuevoNodo;
            NuevoNodo->prev = current;
        } else {
            if (current->prev != nullptr) {
                current->prev->next = NuevoNodo;
            } else {
                head = NuevoNodo;
            }
            NuevoNodo->prev = current->prev;
            NuevoNodo->next = current;
            current->prev = NuevoNodo;
        }
    }
    length++;
}


template <class T>
void DoublyLinkedList<T>::Print(){
    if (!head)
        cout << "La lista esta vacia!" << endl ;
    else {
        Nodo<T> *current = head;
        for (int i = 0; i < length; i++){
            current->data.print();
            cout << "----------------------------------" << endl;
            current = current->next;
        }
    }
}

template <class T>
void DoublyLinkedList<T>::consultar(string pasaporte){
    if (!head)
        cout << "La lista esta vacia! y no se puede consultar un pasajero." << endl ;
    else {
        Nodo<T> *current = head;
        for (int i = 0; i < length; i++){
            if (current->data.getPasaporte() == pasaporte){
                current->data.print();
                return;
            }
            current = current->next;
        }
        cout << "No se encontro el pasajero con pasaporte: " << pasaporte << endl;
    }
}

template <class T>
void DoublyLinkedList<T>::graph(ofstream &file, string ID, string str){
    Nodo<T>* current = head;
    file << "subgraph cluster_" << ID << " {" << endl;
    file << "\tlabel=\"" << str << "\";" << endl;
    file << "\tcolor=blue;" << endl;
    if (length > 0){
        for (int i = 0; i < length; i++){
            file << "\tstruct" << ID << i << " [label=\"No.Pasaporte: " << current->data.getPasaporte() << "\\nNombre: " << current->data.getNombre() << "\\nEquipaje: " << current->data.getEquipaje() << "\\nVuelo: " << current->data.getVuelo() << "\\nAsiento: " << current->data.getAsiento() << "\"]" << endl;
            if (i > 0){
                file << "\tstruct" << ID << i-1 << " -> struct"<< ID << i << ";" << endl;
                file << "\tstruct" << ID << i << " -> struct" << ID << i-1 << ";" << endl;
            }
            current = current->next;
        }
        file << "head" << ID << "0 [label=\"Head\", margin=0, style=filled, color=none, fillcolor=none]" << endl;
        file << "head" << ID << "1 [label=\"Tail\", margin=0, style=filled, color=none, fillcolor=none]" << endl;
        file << "{rank=same;struct" << ID << "0;head" << ID << "0;}" << endl;
        file << "{rank=same;struct" << ID << length - 1 << ";head" << ID << "1;}" << endl;
        file << "head" << ID << "0 -> struct"<< ID <<"0;" << endl;
        file << "head" << ID << "1 -> struct"<< ID << length - 1 << ";" << endl;
    }else{
        file <<"node [margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl; 
        file << "\tstruct" << ID << "0 [label=\"Lista Vacia!\", margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl;
    }
    file << "}" << endl;
}