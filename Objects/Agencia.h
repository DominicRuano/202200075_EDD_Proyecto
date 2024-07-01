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
#include "../Structs/Grafo.h"
#include "../Structs/SparseMatrix.h"
#include <string>
#include <iostream>

class Agencia{
private:
    ArbolB<avion> *BtreeAvionesDisponibles;                         /*Guarda aviones disponibles.*/
    CircularDoublyLinkedList<avion> *listaAvionesMantenimiento;     /*Guarda aviones en mantenimiento.*/
    ArbolBB<Piloto> *ArbolBBPilotos;                                /*Guarda los Pilotos en un arbol binario de busqueda. */
    HashTable<Piloto> *HashTablePilotos;                            /*Guarda los  Pilotos en una tabla hash.*/
    Grafo<string> *GrafoRutas;                                      /*Guarda en un Grafo las rutas. */
    SparseMatrix<Piloto> *Matrix;                                   /*Guarda los Pilotos en una matriz. */

public:
    Agencia(/* args */);
    ~Agencia();

    ArbolB<avion>& getBtreeAvionesDisponibles(){return *BtreeAvionesDisponibles;}
    CircularDoublyLinkedList<avion>& getListAvionesMantenimiento(){return *listaAvionesMantenimiento;}
    ArbolBB<Piloto>& getArbolBBPilotos(){return *ArbolBBPilotos;}
    HashTable<Piloto>& getHashTablePilotos(){return *HashTablePilotos;}
    Grafo<string>& getGrafoRutas(){return *GrafoRutas;}
    SparseMatrix<Piloto>& getMatrix(){return *Matrix;}

    bool MatrixIsReady(){return AvionesCargados && PilotosCargados && RutasCargadas;}

    void Generarmatrix();
    void GraficarAvionesDisponibles();

    bool AvionesCargados;
    bool PilotosCargados;
    bool RutasCargadas;
};

Agencia::Agencia(/* args */){
    this->BtreeAvionesDisponibles = new ArbolB<avion>(5);
    this->listaAvionesMantenimiento = new CircularDoublyLinkedList<avion>();
    this->ArbolBBPilotos = new ArbolBB<Piloto>();
    this->HashTablePilotos = new HashTable<Piloto>();
    this->GrafoRutas = new Grafo<string>(300);
    this->Matrix = new SparseMatrix<Piloto>();

    this->AvionesCargados = false;
    this->PilotosCargados = false;
    this->RutasCargadas = false;
}

Agencia::~Agencia(){
    delete BtreeAvionesDisponibles;
    delete listaAvionesMantenimiento;
    delete ArbolBBPilotos;
    delete HashTablePilotos;
    delete GrafoRutas;
}

void Agencia::GraficarAvionesDisponibles(){
    //if (MatrixIsReady()){ Generarmatrix(); }
    
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
    this->getGrafoRutas().generarReporte(file, "F", "Grafo de rutas");
    file << "}" << endl;
    file.close();
    system("dot -Tpng Reporte.dot -o Reporte.png");
    system("Reporte.png");
}

void Agencia::Generarmatrix(){
    DoublyLinkedList<Piloto>* Pilotos = ArbolBBPilotos->getPilotos();
    Nodo<Piloto>* Current = Pilotos->getHead();

    while (Current != nullptr){
        string Vuelo = Current->getData().getVuelo();
        avion* CurrentAvion = BtreeAvionesDisponibles->find(Vuelo);
        //string Destino = CurrentAvion->ciudadDestino;
        if (CurrentAvion != nullptr){
            cout << "Vuelo: " << Vuelo << " Destino: " << CurrentAvion->ciudadDestino << " Piloto: " << Current->getData().getNombre() << endl;
            Matrix->Insertar(Vuelo, CurrentAvion->ciudadDestino, Current->getData());
        }
        Current = Current->getNext();
    }
}