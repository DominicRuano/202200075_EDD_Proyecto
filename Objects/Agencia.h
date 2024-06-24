#include "./nodo.h"
#include "./avion.h"
#include "./Pasajero.h"
#include "../Structs/CircularDoublyLinkedList.h"
#include "../Structs/Queue.h"
#include "../Structs/Stack.h"
#include "../Structs/DoublyLinkedList.h"

class Agencia{
private:
    CircularDoublyLinkedList<avion> *listaAvionesDisponibles;    /*Guarda aviones disponibles.*/
    CircularDoublyLinkedList<avion> *listaAvionesMantenimiento;  /*Guarda aviones en mantenimiento.*/
    Queue<Pasajero> *colaPasajeros;                              /*Guarda en una cola a los pasajeros. */
    Stack<Pasajero> *pilaPasajeros;                              /*Guarda en una pila a los pasajeros. */
    DoublyLinkedList<Pasajero> *listaPasajeros;                  /*Guarda en una lista a los pasajeros. */
public:
    Agencia(/* args */);
    ~Agencia();

    CircularDoublyLinkedList<avion> &getListAvionesDisponibles(){return *listaAvionesDisponibles;}
    CircularDoublyLinkedList<avion> &getListAvionesMantenimiento(){return *listaAvionesMantenimiento;}
    Queue<Pasajero> &getQueuePasajeros(){return *colaPasajeros;}
    Stack<Pasajero> &getStackPasajeros(){return *pilaPasajeros;}
    DoublyLinkedList<Pasajero> &getListPasajeros(){return *listaPasajeros;}
    void GraficarAvionesDisponibles();

};

Agencia::Agencia(/* args */){
    this->listaAvionesDisponibles = new CircularDoublyLinkedList<avion>();
    this->listaAvionesMantenimiento = new CircularDoublyLinkedList<avion>();
    this->colaPasajeros = new Queue<Pasajero>();
    this->pilaPasajeros = new Stack<Pasajero>();
    this->listaPasajeros = new DoublyLinkedList<Pasajero>();
}
Agencia::~Agencia(){
    delete listaAvionesDisponibles;
    delete listaAvionesMantenimiento;
    delete colaPasajeros;
    delete pilaPasajeros;
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
    file << "agencia -> structA0[style=dotted];" << endl;
    this->listaAvionesDisponibles->graph(file, "A", "Lista circular de aviones disponibles");
    file << "agencia -> structB0[style=dotted];" << endl;
    this->listaAvionesMantenimiento->graph(file, "B", "Lista circular de aviones en mantenimiento");
    file << "agencia -> structC0[style=dotted];" << endl;
    this->colaPasajeros->graph(file, "C", "Cola de pasajeros");
    file << "agencia -> structD0[style=dotted];" << endl;
    this->pilaPasajeros->graph(file, "D", "Pila de pasajeros");
    file << "agencia -> structE0[style=dotted];" << endl;
    this->listaPasajeros->graph(file, "E", "Lista doblemente enlazada de pasajeros");
    file << "}" << endl;
    file.close();
    system("dot -Tpng Reporte.dot -o Reporte.png");
    system("Reporte.png");
}