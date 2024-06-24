#include "../Objects/nodo.h"

template <class T>
class Queue{
private:
    Nodo<T> *head;
    int length = 0;
public:
    Queue();
    ~Queue();

    void enqueue(T &value); 
    T dequeue();
    int getLength(){return length;}
    void print();
    void graph(ofstream &file, string ID, string str);
};

template <class T>
Queue<T>::Queue(){
    head = nullptr;
}

template <class T>
Queue<T>::~Queue(){
    // Pendiente de implementar
}

template <class T>
void Queue<T>::enqueue(T &value){
    Nodo<T> *NuevoNodo = new Nodo<T>(value);
    if (!head){
        head = NuevoNodo;
    }else{
        Nodo<T> *current = head;
        while (current->next){
            current = current->next;
        }
        current->next = NuevoNodo;
    }
    length++;
}

template <class T>
T Queue<T>::dequeue(){
    if (!head)
        throw out_of_range("La cola esta vacia.");
    T val = head->data;
    Nodo<T> *temp = head;
    head = head->next;
    delete temp;
    length --;
    return val;
}

template <class T>
void Queue<T>::print(){
    Nodo<T> *current = head;
    if (length > 0)
        for (int i = 0; i < length; i++){
            current->data.print();
            cout << "---------------------------" << endl;
            current = current->next;
        }
    else 
        cout << "La cola esta vacia!" << endl;
}

template <class T>
void Queue<T>::graph(ofstream &file, string ID, string str){
    Nodo<T>* current = head;
    file << "subgraph cluster_" << ID << " {" << endl;
    file << "\tlabel=\"" << str << "\";" << endl;
    file << "\tcolor=red;" << endl;
    if (length > 0){
        for (int i = 0; i < length; i++){
            file << "\tstruct" << ID << i << " [label=\"No.Pasaporte: " << current->data.getPasaporte() << "\\nNombre: " << current->data.getNombre() << "\\nEquipaje: " << current->data.getEquipaje() << "\\nVuelo: " << current->data.getVuelo() << "\\nAsiento: " << current->data.getAsiento() << "\"]" << endl;
            if (i > 0)
                file << "\tstruct" << ID << i-1 << " -> struct"<< ID << i << ";" << endl;
            current = current->next;
        }
        file << "head" << ID << "0 [label=\"Front\", margin=0, style=filled, color=none, fillcolor=none]" << endl;
        file << "head" << ID << "1 [label=\"Rear\", margin=0, style=filled, color=none, fillcolor=none]" << endl;
        file << "{rank=same;struct" << ID << "0;head" << ID << "0;}" << endl;
        file << "{rank=same;struct" << ID << length - 1 <<";head" << ID << "1;}" << endl;
        file << "head" << ID << "0 -> struct"<< ID <<"0;" << endl;
        file << "head" << ID << "1 -> struct"<< ID << (length - 1) << ";" << endl;
    }else{
        file <<"node [margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl; 
        file << "\tstruct" << ID << "0 [label=\"Cola Vacia!\", margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl;
    }
    file << "}" << endl;
}