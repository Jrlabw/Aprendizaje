#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
typedef int Dato;

class Nodo{
public:
    Dato dato;
    Nodo *siguiente;

    void agregarpila(Nodo *&, int);
    void sacarpila(Nodo *&, int &);
};

int main()
{
    Nodo nodo;
    Nodo *pila = NULL;
    int dato;
    cout << "agregar un nuevo numero: " <<endl;
    cin >> dato;
    nodo.agregarpila(pila,dato); 

    cout <<"digite otro nuevo: " <<endl;
    cin >> dato;
    nodo.agregarpila(pila,dato);

    cout <<"eliminar elemtos de la pila" <<endl;
    while(pila != NULL){ //mientras no sea el final de la pila
        nodo.sacarpila(pila, dato);
        if(pila !=NULL){
            cout << dato << " , ";
        } else {
            cout << dato << " . ";
        }
    }
    return 0;
}

//Sacar elemtos de la pila
void Nodo::sacarpila(Nodo *&pila,int &n){ //se necesita tambien pasar el dato por referencia
    Nodo* aux = pila; //hacemos un objeto auxiliar para poder eliminarlo despues
    n = aux->dato;
    pila = aux->siguiente; //hacemos que pila apunte al siguiente dato pq vamos a eliminar el aux
    delete aux; //eliminamose el auxiliar

}

void Nodo::agregarpila(Nodo *&pila, int n){
    Nodo* nuevoNodo = new Nodo(); //crear un espacio para almacenar en memoria
    nuevoNodo->dato = n;//cargar el valor dentro del nodo(dato)
    nuevoNodo->siguiente = pila;//cargar el puntero pila dentro del nodo(*siguiente)
    pila = nuevoNodo;//asignar el nuevo nodo a pila
    cout << "elemento agregado" << n << endl;
}



