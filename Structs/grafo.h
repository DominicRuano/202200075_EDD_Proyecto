#include "../Objects/nodo.h"
#include <iostream>
#include <fstream>
using namespace std;

template <class T>
class Grafo{
private:
    int numVertices;
    int maxVertices;
    Nodo<T>** vertices;
    int** matrizAdy;

    string arco;
public:
    Grafo(int max);
    ~Grafo();

    int getNumVertices(){return this->numVertices;}
    void setNumVertices(int n){this->numVertices = n;}

    void nuevoVertice(T nombre);
    int existeVertice(string nombre);
    void nuevoArco(string nom1, string nom2, int peso);
    void imprimirMatriz();
    void generarReporte(ofstream &file, string ID, string str);
    void CaminoMasCorto(string origen, string destino);
    int minDistancia(int dist[], bool sptSet[]);
};

template <class T>
Grafo<T>::Grafo(int max){
    numVertices = 0;
    maxVertices = max;
    matrizAdy = new int*[max];
    vertices = new Nodo<T>*[max]; // Inicializa el arreglo de punteros a nodos
    for (int i = 0; i < max; ++i) {
            vertices[i] = nullptr;
    }

    for (int i = 0; i < max; i++)
        matrizAdy[i] = new int[max];
    for (int i = 0; i < maxVertices; i++)
        for (int j = 0; j < maxVertices; j++)
            matrizAdy[i][j] = -1;
}

template <class T>
Grafo<T>::~Grafo(){

}

template <class T>
void Grafo<T>::nuevoVertice(T nombre){
    bool existe = (existeVertice(nombre) >= 0);
    if (!existe){
        Nodo<T>* nuevo = new Nodo<T>(nombre);
        vertices[numVertices] = nuevo;
        numVertices++;
    }
}

template <class T>
int Grafo<T>::existeVertice(string nombre){
    int i = 0;
    bool encontrado = false;
    while (i < numVertices && !encontrado){
        encontrado = vertices[i]->data == nombre;
        if (!encontrado)
            i++;
    }
    return (i < numVertices) ? i : -1;
}

template <class T>
void Grafo<T>::nuevoArco(string nom1, string nom2, int peso){
    int vertice1, vertice2;
    vertice1 = existeVertice(nom1);
    vertice2 = existeVertice(nom2);
    if (vertice1 >= 0 && vertice2 >= 0)
        matrizAdy[vertice1][vertice2] = peso;  
    else
        cout << "Error, uno de los vértices no existe\n";
}

template <class T>
void Grafo<T>::imprimirMatriz(){
    for (int i = 0; i < maxVertices; i++){
        for (int j = 0; j < maxVertices; j++)
            cout << "[#]" << matrizAdy[i][j] << " ";
        cout << endl;
    }
}

template <class T>
void Grafo<T>::generarReporte(ofstream &file, string ID, string str){
    file << "subgraph cluster_" << ID << " {" << endl;
    file << "\tlabel=\"" << str << "\"; \n\tnode [shape=hexagon, style=filled, fillcolor=lightblue];" << endl;
    file << "\tcolor=green;" << endl;
    if (getNumVertices() == 0) {
        file << "\tstruct" << ID << "0 [label=\"Grafo vacío\", margin=0, shape=box, style=filled, color=none, fillcolor=none];\n}" << endl;
        file << "agencia -> structF0[style=dotted];" << endl;
        return;
    }else{
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                if (matrizAdy[i][j] >= 0){
                    arco += "\t" + vertices[i]->data + " -> " + vertices[j]->data + "[label = \"" + to_string(matrizAdy[i][j])  + "\", style=dashed];\n";
                    file << arco;
                    arco.clear();
                }
    }
    file << "}" << endl;
    file << "agencia -> " << vertices[0]->data <<"[style=dotted];" << endl;
}

template <class T>
void Grafo<T>::CaminoMasCorto(string origen1, string destino1){
    int origen = existeVertice(origen1);
    int destino = existeVertice(destino1);

    int* dist = new int[maxVertices];
    bool* sptSet = new bool[maxVertices];
    int* parent = new int[maxVertices];

    for (int i = 0; i < maxVertices; i++) {
        dist[i] = 99999;      // define distancia inf o maxima para los vertices.
        sptSet[i] = false;      // indica que aun no se revisa.
        parent[i] = -1;         // indica que no hay padre aun.
    }

    dist[origen] = 0;           // define 0 del origen al origen.

    for (int count = 0; count < maxVertices - 1; count++) {
        int u = minDistancia(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < maxVertices; v++) {
            if (!sptSet[v] && matrizAdy[u][v] != -1 && dist[u] != 99999 && dist[u] + matrizAdy[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + matrizAdy[u][v];
            }
        }
    }

    string path, auxiliar;
    for (int v = destino; v != -1; v = parent[v]) {
        auxiliar = vertices[v]->data;
        path = auxiliar + " -> " + path;
    }

    delete[] dist;
    delete[] sptSet;
    delete[] parent;

    cout << "El camino más corto es: " << path << endl;
}

template <class T>
int Grafo<T>::minDistancia(int dist[], bool sptSet[]) {
    int min = 99999, min_index;
    for (int v = 0; v < maxVertices; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}