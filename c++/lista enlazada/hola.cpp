#include <iostream>
#include <string>
#include "hola.h"
using namespace std;



void lista::crearlista(){
    int  x;
    primero = 0;
    cout << "termina en -1 " << endl;
    do {
        cin >> x;
        if(x != -1){
            primero = new nodo(x, primero); 
        }
    }while(x != -1);
}

void lista::insertarcabezalista(Dato entrada){ // Insertar un elemento AL INICIO de la lista
    nodo* nuevo;
    nuevo = new nodo(entrada);  // 1. Crear un nuevo nodo
    nuevo ->ponerenlace(primero);  // 2. El nuevo nodo apunta al antiguo primero
    primero = nuevo;  // 3. Ahora el nuevo nodo es el primero
}
// Mostrar todos los elementos
void lista::visualizar(){
    nodo* n;
    int k = 0;
    n = primero;
    while(n != NULL){ // Recorrer toda la lista
        char c; 
        k++; c = (k%15 != 0 ? ' ' : '\n');
        cout << n->datonodo() << c;
        n = n->enlacenodo();
    }
}



