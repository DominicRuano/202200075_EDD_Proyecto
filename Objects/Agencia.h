#include "./nodo.h"
#include "./avion.h"
#include "./Pasajero.h"
#include "./Piloto.h"
#include "../Structs/CircularDoublyLinkedList.h"
#include "../Structs/Queue.h"
#include "../Structs/Stack.h"
#include "../Structs/DoublyLinkedList.h"
#include "../Structs/Btree.h"
#include "../Structs/ArbolBB.h"
#include "../Structs/HashTable.h"

class Agencia{
private:
    ArbolB<avion> *BtreeAvionesDisponibles;                      /*Guarda aviones disponibles.*/
    CircularDoublyLinkedList<avion> *listaAvionesMantenimiento;  /*Guarda aviones en mantenimiento.*/
    ArbolBB<Piloto> *ArbolBBPilotos;                            /*Guarda los Pilotos en un arbol binario de busqueda. */
    HashTable<Piloto> *HashTablePilotos;                              /*Guarda los  Pilotos en una tabla hash*/
    DoublyLinkedList<Pasajero> *listaPasajeros;                  /*Guarda en una lista a los pasajeros. */
public:
    Agencia(/* args */);
    ~Agencia();

    ArbolB<avion>& getBtreeAvionesDisponibles(){return *BtreeAvionesDisponibles;}
    CircularDoublyLinkedList<avion>& getListAvionesMantenimiento(){return *listaAvionesMantenimiento;}
    ArbolBB<Piloto>& getArbolBBPilotos(){return *ArbolBBPilotos;}
    HashTable<Piloto>& getHashTablePilotos(){return *HashTablePilotos;}
    DoublyLinkedList<Pasajero>& getListPasajeros(){return *listaPasajeros;}
    void GraficarAvionesDisponibles();

};

Agencia::Agencia(/* args */){
    this->BtreeAvionesDisponibles = new ArbolB<avion>(5);
    this->listaAvionesMantenimiento = new CircularDoublyLinkedList<avion>();
    this->ArbolBBPilotos = new ArbolBB<Piloto>();
    this->HashTablePilotos = new HashTable<Piloto>();
    this->listaPasajeros = new DoublyLinkedList<Pasajero>();
}
Agencia::~Agencia(){
    delete BtreeAvionesDisponibles;
    delete listaAvionesMantenimiento;
    delete ArbolBBPilotos;
    delete HashTablePilotos;
    delete listaPasajeros;
}

void Agencia::GraficarAvionesDisponibles(){
    ofstream file;
    file.open("Reporte.dot");
    file << "digraph G {" << endl;
    file << "rankdir=TB;" << endl;
    file << "node [margin=0, style=filled, fillcolor=beige, shape=box];" << endl;
    file << "agencia [label =\"Grafico de todas las estructuras de datos.\"]" << endl;
    file << "labelloc=t;" << endl;
    file << "labeljust=l;" << endl;
    this->BtreeAvionesDisponibles->generateDot(file, "A", "Arbol B de aviones disponibles");
    file << "agencia -> node0[style=dotted];" << endl;
    file << "agencia -> structB0[style=dotted];" << endl;
    this->listaAvionesMantenimiento->graph(file, "B", "Lista circular de aviones en mantenimiento");
    this->ArbolBBPilotos->graph(file, "C", "ArbolBB de pilotos");
    this->HashTablePilotos->graph(file, "D", "Tabla hash de pilotos");
    file << "agencia -> structD0[style=dotted];" << endl;
    file << "agencia -> structE0[style=dotted];" << endl;
    this->listaPasajeros->graph(file, "E", "Lista doblemente enlazada de pasajeros");
    file << "}" << endl;
    file.close();
    system("dot -Tpng Reporte.dot -o Reporte.png");
    system("Reporte.png");
}