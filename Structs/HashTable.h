//#include "./DoublyLinkedList.h"
#include <string>
using namespace std;

template <class T>
class HashTable{
private:
    int size;
    int numElements;
    DoublyLinkedList<T> *table;

public:
    HashTable(/* args */);
    ~HashTable();

    int hashFunction(string key);
    void insert(T &val);
    T* search(string key);
    void graph(ofstream &file, string ID, string str);
};

template <class T>
HashTable<T>::HashTable(/* args */){
    size = 18;
    numElements = 0;
    table = new DoublyLinkedList<T>[size];
}

template <class T>
HashTable<T>::~HashTable(){
    delete[] table;
}

template <class T>
int HashTable<T>::hashFunction(string key){
    int llv = 0;
    for (int i = 0; i < key.length(); i++)
        llv += key[i];
    return llv % size;
}

template <class T>
void HashTable<T>::insert(T &val){
    int index = hashFunction(val.getNumeroDeID());
    table[index].addEnd(val);
}

template <class T>
T* HashTable<T>::search(string key){
    int index = hashFunction(key);
    Nodo<T> *current = table[index].getHead();
    while (current != nullptr){
        if (current->data.getNumeroDeID() == key)
            return &current->data;
        current = current->next;
    }
    return nullptr;
}

template <class T>
void HashTable<T>::graph(ofstream &file, string ID, string str){
    int aux = 0;
    file << "subgraph cluster_" << ID << " {" << endl;
    file << "\tlabel=\"" << str << "\"; \n\tnode [shape=hexagon, style=filled, fillcolor=lightblue];" << endl;
    file << "\tcolor=green;" << endl;
    for (int i = 0; i < size; i++){
        if (table[i].getHead() != nullptr){
            file << "\tstruct" << ID << i << "[label=\"" << i << "\"];" << endl;
            Nodo<T> *current = table[i].getHead();
            while (current != nullptr){
                file << "\tstruct" << ID << i << " -> " << current->data.getNumeroDeID() << endl;
                current = current->next;
                aux++;
            }
        }
    }
    if (aux == 0)
        file << "\tstruct" << ID << "0 [label=\"Tabla vacía\", margin=0, shape=box, style=filled, color=none, fillcolor=none];" << endl;
    file << "}" << endl;
}