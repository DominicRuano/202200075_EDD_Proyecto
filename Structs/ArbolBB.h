#include "../Objects/nodo.h"
using namespace std;

template <typename T>
class ArbolBB{
private:
    Nodo<T>* root;
public:
    ArbolBB(/* args */);
    ~ArbolBB();

    bool estaVacion();
    
};

template <typename T>
bool ArbolBB<T>::estaVacion(){
    return root == nullptr;
}

template <typename T>
ArbolBB<T>::ArbolBB(/* args */){
    root = nullptr;
}

template <typename T>
ArbolBB<T>::~ArbolBB(){
    
}