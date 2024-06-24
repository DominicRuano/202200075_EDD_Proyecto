#include <iostream>
using namespace std;

class avion{
private:
    string vuelo;
    string numDeRegistro;
    string modelo;
    string fabricante;
    int anioDeFabricacion;
    int capacidad;
    int pesoMaximo;
    string aerolinea;
    string estado;  
public:
    avion(string vuelo, 
            string numDeRegistro, 
            string modelo, 
            string fabricante, 
            int anioDeFabricacion, 
            int capacidad, 
            int pesoMaximo, 
            string aerolinea, 
            string estado);
    ~avion();

    void print();
    string getVuelo(){return vuelo;}
    string getNumDeRegistro(){return numDeRegistro;}
    string getEstado(){return estado;}
};

avion::avion(string vuelo, string numDeRegistro, string modelo, string fabricante, int anioDeFabricacion, int capacidad, int pesoMaximo, string aerolinea, string estado){
    this->vuelo = vuelo;
    this->numDeRegistro = numDeRegistro;
    this->modelo = modelo;
    this->fabricante = fabricante;
    this->anioDeFabricacion = anioDeFabricacion;
    this->capacidad = capacidad;
    this->pesoMaximo = pesoMaximo;
    this->aerolinea = aerolinea;
    this->estado = estado;
}

avion::~avion(){
    
}

void avion::print(){
    cout << "Vuelo: " << vuelo << endl;
    cout << "Numero de Registro: " << numDeRegistro << endl;
    cout << "Modelo: " << modelo << endl;
    cout << "Fabricante: " << fabricante << endl;
    cout << "Anio de Fabricacion: " << anioDeFabricacion << endl;
    cout << "Capacidad: " << capacidad << endl;
    cout << "Peso Maximo: " << pesoMaximo << endl;
    cout << "Aerolinea: " << aerolinea << endl;
    cout << "Estado: " << estado << endl;
}