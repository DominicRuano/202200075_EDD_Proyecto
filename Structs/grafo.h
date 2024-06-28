#include "../Objects/nodo.h"
#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class Grafo{
private:
    int numVertices;
    int maxVertices;
    Nodo<T>* vertices;
    int** matrizAdy;

    ofstream archivo;
    string arco;
public:
    Grafo(int max);
    ~Grafo();

    int getNumVertices(){return this->numVertices;}
    void setNumVertices(int n){this->numVertices = n;}

    void nuevoVertice(string nombre);
    int existeVertice(string nombre);
    void nuevoArco(string nom1, string nom2);
    void imprimirMatriz();
    void generarReporte();
};

template <class T>
Grafo<T>::Grafo(int max){
    numVertices = 0;
    maxVertices = max;
    vertices = new Vertice[max];
    matrizAdy = new int*[max];

    for (int i = 0; i < max; i++)
        matrizAdy[i] = new int[max];
    for (int i = 0; i < maxVertices; i++)
        for (int j = 0; j < maxVertices; j++)
            matrizAdy[i][j] = 0;
}

template <class T>
Grafo<T>::~Grafo(){

}

template <class T>
void Grafo<T>::nuevoVertice(string nombre){
    bool existe = (existeVertice(nombre) >= 0);
    if (!existe){
        Vertice nuevo = Vertice(nombre,numVertices);
        vertices[numVertices] = nuevo;
        numVertices++;
    }
}

template <class T>
int Grafo<T>::existeVertice(string nombre){
    int i = 0;
    bool encontrado = false;
    while (i < numVertices && !encontrado){
        encontrado = vertices[i].esIgual(nombre);
        if (!encontrado)
            i++;
    }
    return (i < numVertices) ? i : -1;
}

template <class T>
void Grafo<T>::nuevoArco(string nom1, string nom2){
    int vertice1, vertice2;
    vertice1 = existeVertice(nom1);
    vertice2 = existeVertice(nom2);
    if (vertice1 >= 0 && vertice2 >= 0)
        matrizAdy[vertice1][vertice2] = 1;  
    else
        cout << "Error, uno de los vértices no existe\n";
}

template <class T>
void Grafo<T>::imprimirMatriz(){
    for (int i = 0; i < maxVertices; i++){
        for (int j = 0; j < maxVertices; j++)
            cout << " " << matrizAdy[i][j] << " ";
        cout << endl;
    }
}

template <class T>
void Grafo<T>::generarReporte(){
    if (getNumVertices() == 0) {
        cout << "Grafo vacío\n";
    }else{
        archivo.open("grafo.dot",ios::out);
        archivo << "digraph G { " << endl;

        for (int i = 0; i < maxVertices; i++)
            for (int j = 0; j < maxVertices; j++)
                if (matrizAdy[i][j] == 1){
                    arco += vertices[i].getNombre() + " -> " + vertices[j].getNombre() + ";\n";
                    archivo << arco;
                    arco.clear();
                }

        archivo << "}";
        archivo.close();
        system("dot -Tpng grafo.dot -o grafo.png");
        system("start grafo.png");
    }
}
