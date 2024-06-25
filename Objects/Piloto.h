#include <iostream>
using namespace std;

class Piloto{
private:
    string Nombre;
    string Nacionalidad;
    string NumeroDeID;
    string Vuelo;
    int HorasDeVuelo;
    string TipoDeLicencia;
public:
    Piloto(string Nombre, string Nacionalidad, string NumeroDeID, string Vuelo, int HorasDeVuelo, string TipoDeLicencia);
    ~Piloto();

    void print();
    string getNombre(){return Nombre;}
    string getNacionalidad(){return Nacionalidad;}
    string getNumeroDeID(){return NumeroDeID;}
    string getVuelo(){return Vuelo;}
    int getHorasDeVuelo(){return HorasDeVuelo;}
    string getTipoDeLicencia(){return TipoDeLicencia;}

    friend ostream& operator<<(ostream& os, const Piloto& piloto);
};

Piloto::Piloto(string Nombre, string Nacionalidad, string NumeroDeID, string Vuelo, int HorasDeVuelo, string TipoDeLicencia){
    this->Nombre = Nombre;
    this->Nacionalidad = Nacionalidad;
    this->NumeroDeID = NumeroDeID;
    this->Vuelo = Vuelo;
    this->HorasDeVuelo = HorasDeVuelo;
    this->TipoDeLicencia = TipoDeLicencia;
}

Piloto::~Piloto(){
    
}

void Piloto::print(){
    cout << "\tNombre: " << Nombre << endl;
    cout << "\tNacionalidad: " << Nacionalidad << endl;
    cout << "\tNumero de ID: " << NumeroDeID << endl;
    cout << "\tVuelo: " << Vuelo << endl;
    cout << "\tHoras de Vuelo: " << HorasDeVuelo << endl;
    cout << "\tTipo de Licencia: " << TipoDeLicencia << endl;
}

ostream& operator<<(ostream& os, const Piloto& piloto) {
    os << "\tNombre: " << piloto.Nombre << endl;
    os << "\tNacionalidad: " << piloto.Nacionalidad << endl;
    os << "\tNumero de ID: " << piloto.NumeroDeID << endl;
    os << "\tVuelo: " << piloto.Vuelo << endl;
    os << "\tHoras de Vuelo: " << piloto.HorasDeVuelo << endl;
    os << "\tTipo de Licencia: " << piloto.TipoDeLicencia << endl;
    return os;
}