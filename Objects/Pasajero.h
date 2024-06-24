#include <iostream>
using namespace std;

class Pasajero{
private:
    string nombre;
    string nacionalidad;
    string numeroPasaporte;
    string vuelo;
    int asiento;
    string destino;
    string origen;
    int equipaje;
public:
    Pasajero(string nombre, 
            string nacionalidad, 
            string numeroPasaporte, 
            string vuelo,
            int asiento, 
            string destino, 
            string origen, 
            int equipaje);
    ~Pasajero();

    void print();
    string getVuelo(){return vuelo;}
    int getAsiento(){return asiento;}
    int getEquipaje(){return equipaje;}
    string getPasaporte(){return numeroPasaporte;}
    string getNombre(){return nombre;}

};

Pasajero::Pasajero(string nombre, string nacionalidad, string numeroPasaporte,string vuelo, int asiento, string destino, string origen, int equipaje){
    this->nombre = nombre;
    this->nacionalidad = nacionalidad;
    this->numeroPasaporte = numeroPasaporte;
    this->asiento = asiento;
    this->destino = destino;
    this->origen = origen;
    this->equipaje = equipaje;
    this->vuelo = vuelo;
}

Pasajero::~Pasajero(){
    // Pendiente de implementar
}

void Pasajero::print(){
    cout << "Nombre: " << nombre << endl;
    cout << "Nacionalidad: " << nacionalidad << endl;
    cout << "Numero de Pasaporte: " << numeroPasaporte << endl;
    cout << "Vuelo: " << vuelo << endl;
    cout << "Asiento: " << asiento << endl;
    cout << "Destino: " << destino << endl;
    cout << "Origen: " << origen << endl;
    cout << "Equipaje: " << equipaje << endl;
}