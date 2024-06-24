#include <iostream>
#include <conio.h>  // Para getch()
#include <limits>
#include <fstream>
#include <regex>
#include "./librerias/json.hpp"
#include "./Objects/Agencia.h"
using namespace std;

using json = nlohmann::json;

template <typename T>
void GetOp(T &input);
void Menu(int &input);
void FindByPasaPorte(DoublyLinkedList<Pasajero> &listaPasajeros);
json ReadJson(string filePath);
bool CargaAviones(CircularDoublyLinkedList<avion> &listaAviones, CircularDoublyLinkedList<avion> &listaAviones2);
bool EncolarClientes(Queue<Pasajero> &colaPasajeros);
bool CargarMovimientos(CircularDoublyLinkedList<avion> &listaAviones, 
                        CircularDoublyLinkedList<avion> &listaAviones2, 
                        Queue<Pasajero> &colaPasajeros, 
                        Stack<Pasajero> &pilaPasajeros, 
                        DoublyLinkedList<Pasajero> &listaPasajeros);

int main(){
    int input;      // Guarda el valor seleccionado por el usuario.
    bool cond;   // Condicion para salir del ciclo.

    Agencia *agencia = new Agencia();

    while (input != 6){
        cond = false;

        Menu(input); /*Recibe el apuntador para recibir un input usado como seleccion en el menu*/
        switch (input){
        case 1:
            while (!CargaAviones(agencia->getListAvionesDisponibles(), agencia->getListAvionesMantenimiento()));
            break;
        case 2:
            while (!EncolarClientes(agencia->getQueuePasajeros()));
            break;
        case 3:
            while (!CargarMovimientos(agencia->getListAvionesDisponibles(), 
                                        agencia->getListAvionesMantenimiento(), 
                                        agencia->getQueuePasajeros(), 
                                        agencia->getStackPasajeros(), 
                                        agencia->getListPasajeros()));
            break;
        case 4:
            FindByPasaPorte(agencia->getListPasajeros());
            break;
        case 5:
            agencia->GraficarAvionesDisponibles();
            break;
        case 6:
            break;
        default:
            break;
        }
    }
    return 0;
}

/*
Funcion para buscar un pasajero por su pasaporte.
Recibe una lista de pasajeros.
*/
void FindByPasaPorte(DoublyLinkedList<Pasajero> &listaPasajeros){
    string pasaporte;
    cout << "\tIngrese el No.Pasaporte a consultar: ";
    GetOp(pasaporte);
    
    if (pasaporte == "exit")
        return;

    listaPasajeros.consultar(pasaporte);
    cout << "Presiona Enter para continuar...";
    _getch();  // Espera a que el usuario presione cualquier tecla
}

/*
Funcion para cargar los movimientos.
aun no recibe parametros.
Retorna un booleano, true si se cargaron los movimientos correctamente, false si hubo un error.
*/
bool CargarMovimientos(CircularDoublyLinkedList<avion> &listaAviones, CircularDoublyLinkedList<avion> &listaAviones2, Queue<Pasajero> &colaPasajeros, Stack<Pasajero> &pilaPasajeros, DoublyLinkedList<Pasajero> &listaPasajeros){
    string path;
    smatch matches;
    regex pattern1(R"(MantenimientoAviones,Ingreso,([^;]+);)");
    regex pattern2(R"(MantenimientoAviones,Salida,([^;]+);)");

    cout << "\tIngrese la ruta del archivo TXT de Movimientos: ";
    GetOp(path);

    if (path == "exit")
        return true;

    try{
        std::ifstream inputFile(path); // Abrir el archivo

        // Verificar si el archivo se abrió correctamente
        if (!inputFile.is_open()) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
            return false; 
        }

        string line;
        // Leer el archivo línea por línea
        while (std::getline(inputFile, line)) {
            if (line.compare("IngresoEquipajes;") == 0){
                try{
                    Pasajero pasajero1 = colaPasajeros.dequeue();
                    if (pasajero1.getEquipaje() > 0)
                        pilaPasajeros.push(pasajero1);
                    listaPasajeros.add(pasajero1);
                    if (pasajero1.getEquipaje() > 0)
                        cout << "\n\tSe ingreso el pasajero " << pasajero1.getNombre() << " con " << pasajero1.getEquipaje() << " equipaje(s) a la lista de pasajeros y a la cola de pasajeros." << endl;
                    else
                        cout << "\n\tSe ingreso el pasajero " << pasajero1.getNombre() << " sin equipaje a la lista de pasajeros." << endl;
                }catch(const std::exception& e){
                    std::cerr << "\t" << e.what() << '\n';
                    cout << "\tPresiona Enter para continuar...";
                    _getch();  // Espera a que el usuario presione cualquier tecla
                }
            }else if (line.compare(0, 29, "MantenimientoAviones,Ingreso,") == 0){
                try{
                    regex_search(line, matches, pattern1);
                    cout << "\n\tSe realizo ingreso de " << matches[1] <<" en mantenimiento de Aviones." << endl;
                    avion avionActual = listaAviones.remove(matches[1]);
                    listaAviones2.insert(avionActual);
                }catch(const std::exception& e){
                    std::cerr << "\t" << e.what() << '\n';
                    cout << "\tPresiona Enter para continuar...";
                    _getch();  // Espera a que el usuario presione cualquier tecla
                }
            }else if (line.compare(0, 28, "MantenimientoAviones,Salida,") == 0){
                try{
                    regex_search(line, matches, pattern2);
                    cout << "\n\tSe realizo salida de " << matches[1] <<" en Mantenimiento de Aviones." << endl;
                    avion avionActual = listaAviones2.remove(matches[1]);
                    listaAviones.insert(avionActual);
                }catch(const std::exception& e){
                    std::cerr << "\t" << e.what() << '\n';
                    cout << "\tPresiona Enter para continuar...";
                    _getch();  // Espera a que el usuario presione cualquier tecla
                }
            }   
        }

        inputFile.close(); // Cerrar el archivo
    }catch(const std::exception& e){
        cout << e.what() << endl;
        cout << "Presiona Enter para continuar...";
        _getch();  // Espera a que el usuario presione cualquier tecla
        return true;
    }

    cout << "Presiona Enter para continuar...";
    _getch();  // Espera a que el usuario presione cualquier tecla
    return true;
}

/*
Funcion para cargar los clientes.
Recibe una cola de pasajeros.
Retorna un booleano, true si se cargaron los clientes correctamente, false si hubo un error.
*/
bool EncolarClientes(Queue<Pasajero> &colaPasajeros){
    string path;
    cout << "\tIngrese la ruta del archivo JSON de Pasajeros: ";
    GetOp(path);

    if (path == "exit")
        return true;

    try{
        json jsonData = ReadJson(path);

        // Acceder a los datos
        for (const auto& item : jsonData) { // Cambiar todo esto por una append a la estructura.
            Pasajero PasajeroActual(item["nombre"], item["nacionalidad"], item["numero_de_pasaporte"], item["vuelo"], item["asiento"], item["destino"], item["origen"], item["equipaje_facturado"]);
            colaPasajeros.enqueue(PasajeroActual);
        }
    }catch(const std::exception& e){
        cout << "Se detecto un error: por favor verifique el path del archivo." << endl;
        return false;
    }
    cout << "\n\tSe tienen (" << colaPasajeros.getLength() << ") Pasajeros en la cola." << endl;

    cout << "Presiona Enter para continuar...";
    _getch();  // Espera a que el usuario presione cualquier tecla
    return true;
}

/*
Funcion para cargar los aviones.
Recibe dos listas de aviones, una para aviones disponibles y otra para aviones en mantenimiento.
Retorna un booleano, true si se cargaron los aviones correctamente, false si hubo un error.
*/
bool CargaAviones(CircularDoublyLinkedList<avion> &listaAviones, CircularDoublyLinkedList<avion> &listaAviones2){
    string path;
    cout << "\tIngrese la ruta del archivo JSON De Aviones: ";
    GetOp(path);

    if (path == "exit")
        return true;

    try{
        json jsonData = ReadJson(path);

        // Acceder a los datos
        for (const auto& item : jsonData) { // Cambiar todo esto por una append a la estructura.
            avion avionActual(item["vuelo"], item["numero_de_registro"], item["modelo"], item["fabricante"], item["ano_fabricacion"], item["capacidad"], item["peso_max_despegue"], item["aerolinea"], item["estado"]);
            if (item["estado"] == "Disponible")
                listaAviones.insert(avionActual);
            else
                listaAviones2.insert(avionActual);
        }
    }catch(const std::exception& e){
        return false;
    }
    cout << "\n\tSe tienen (" << listaAviones.getLength() << ") aviones en la lista de aviones disponibles." << endl;
    cout << "\tSe tienen (" << listaAviones2.getLength() << ") aviones en la lista de aviones en mantenimiento." << endl;

    cout << "Presiona Enter para continuar...";
    _getch();  // Espera a que el usuario presione cualquier tecla
    return true;
}

/* 
Funcion que recibe la ruta(String) de un archivo JSON y retorna un objeto JSON.
*/
json ReadJson(string filePath){
    //string filePath = "./ArchivosEntrada/Aviones.json"; // Ruta del archivo JSON

    // Leer el archivo JSON
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cout << "\tError al cargar el archivo JSON." << endl;
    }

    // Parsear el JSON
    json jsonData;
    inputFile >> jsonData;

    return jsonData;
}

/* 
Funcion que imprime el menu de opciones.
Recibe como parametro un puntero de tipo int, el cual se encarga de recibir el valor del input del usuario.
*/
void Menu(int &input){
    system("cls");
    cout << "------------ MENU -------------- [ingrese \"exit\", para salir de cualquier submenu]" << endl;
    cout << "1. Carga de Aviones." << endl;
    cout << "2. Carga de Pasajeros." << endl;
    cout << "3. Carga de Movimientos." << endl;
    cout << "4. Consulta Pasajeros." << endl;
    cout << "5. Visualizar Reportes." << endl;
    cout << "6. Salir." << endl;

    cout << "Seleccione una opcion: ";
    GetOp(input);
}

/*
Recibe como parametro un puntero de tipo T, el cual se encarga de recibir el valor del input del usuario.
Retorna el valor del input del usuario en el puntero recibido.
*/
template <typename T>
void GetOp(T &input){
    cin >> input;
    // Maneja errores.
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear(); // Clear the error flag
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }
}
