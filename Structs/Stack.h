#include "../Objects/nodo.h"

template <class T>
class Stack{
private:
    Nodo<T> *Top;
    int length = 0;
public:
    Stack(/* args */);
    ~Stack();

    void push(T &value);
    T pop();
    int getLength(){return length;}
    void Print();
    void graph(ofstream &file, string ID, string str);
};

template <class T>
Stack<T>::Stack(/* args */){
    Top = nullptr;
}

template <class T>
Stack<T>::~Stack(){
    // Pendiente de implementar
}

template<class T>
void Stack<T>::push(T &value){
    Nodo<T> *NuevoNodo = new Nodo<T>(value);
    if (!Top)
        Top = NuevoNodo;
    else{
        Nodo<T> *current = Top;
        Top = NuevoNodo;
        NuevoNodo->prev = current;
    }
    length++;
}

template<class T>
T Stack<T>::pop(){
    if (!Top)
        out_of_range("La pila esta vacia!");
    T val = Top->data;
    Nodo<T> *Temp = Top;
    Top = Top->prev;
    delete Temp;
    length --;
    return val;
}

template<class T>
void Stack<T>::Print(){
    if (!Top){
        cout << "La pila esta vacia!" << endl;
    }else {
        Nodo<T> *Current = Top;
        for (int i = 0; i < length; i++){
            Current->data.print();
            cout << "----------------------------------" << endl;
            Current = Current->prev;
        }
    }
}

template<class T>
void Stack<T>::graph(ofstream &file, string ID, string str){
    Nodo<T> *current = Top;
    file << "subgraph cluster" << ID << "{" << endl;
    file << "label = \"" << str << "\";" << endl;
    file << "\tcolor=green;" << endl;
    if (length > 0){
        for (int i = 0; i < length; i++){
            file << "\tstruct" << ID << i << " [label=\"No.Pasaporte: " << current->data.getPasaporte() << "\\nNombre: " << current->data.getNombre() << "\\nEquipaje: " << current->data.getEquipaje() << "\\nVuelo: " << current->data.getVuelo() << "\\nAsiento: " << current->data.getAsiento() << "\"]" << endl;
            if (i > 0)
                file << "struct"<< ID << i - 1 << " -> struct" << ID << i << ";" << endl;
            current = current->prev;
        }
        file << "head" << ID << "0 [label=\"Top\", margin=0, style=filled, color=none, fillcolor=none]" << endl;
        file << "{rank=same;struct" << ID << "0;head" << ID << "0;}" << endl;
        file << "head" << ID << "0 -> struct"<< ID <<"0;" << endl;
    }else{
        file <<"node [margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl; 
        file << "\tstruct" << ID << "0 [label=\"Pila Vacia!\", margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl;
    }
    file << "}" << endl;
}