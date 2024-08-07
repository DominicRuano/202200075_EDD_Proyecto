#include <iostream>
#include <string>
using namespace std;

class avion{
public:
    string vuelo;
    string numDeRegistro;
    string modelo;
    int capacidad;
    string ciudadDestino;
    string estado;  
    avion(string vuelo, 
            string numDeRegistro, 
            string modelo, 
            int capacidad, 
            string ciudadDestino, 
            string estado);
    avion(){}
    avion(string nRegistro){ numDeRegistro = nRegistro;}
    ~avion();

    void print();
    string getVuelo(){return vuelo;}
    string getNumDeRegistro()const{return numDeRegistro;}
    string getEstado(){return estado;}
    string getDestino(){return ciudadDestino;}
    avion* copy(){return new avion(vuelo, numDeRegistro, modelo, capacidad, ciudadDestino, estado);}
};

avion::avion(string vuelo, string numDeRegistro, string modelo, int capacidad, string ciudadDestino, string estado){
    this->vuelo = vuelo;
    this->numDeRegistro = numDeRegistro;
    this->modelo = modelo;
    this->capacidad = capacidad;
    this->ciudadDestino = ciudadDestino;
    this->estado = estado;
}

avion::~avion(){
    
}

void avion::print(){
    cout << "Vuelo: " << vuelo << endl;
    cout << "Numero de Registro: " << numDeRegistro << endl;
    cout << "Modelo: " << modelo << endl;
    cout << "Capacidad: " << capacidad << endl;
    cout << "Ciudad Destino: " << ciudadDestino << endl;
    cout << "Estado: " << estado << endl;
}