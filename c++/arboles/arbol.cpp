#include <iostream>
#include <string>
using namespace std;

struct nodo{
    int dato;
    nodo *izq;
    nodo *dere;
};
//prototipos
nodo *crearnodo(int);
void insertar(nodo *&,int);
void menu();
nodo *arbol = nullptr;

int main()
{
    menu();
    return 0;
}


void menu(){
    int dato, opcion;
    do
    {
    cout << "MENU" <<endl;  
    cout << "1. Insertar un nuevo nodo" << endl;
    cout << "2. salir" <<endl;  
    cout << "opcion: " <<endl;
    cin >> opcion;
    switch (opcion)
    {
    case 1:
        cout << "ingrese su dato "<< endl;
        cin >> dato;
        insertar(arbol,dato); //insertamos un nuevo nodo
        cout << endl;
        system("pause");
        break;
    

    } 
    system("cls");
}while (opcion != 2);
    
}
//funcion para crear un nuevo nodo
nodo *crearnodo(int n){
    nodo *nuevonodo = new nodo();
    nuevonodo->dato = n;
    nuevonodo->dere = nullptr;
    nuevonodo->izq = nullptr;
    return nuevonodo;
}

//funcion para insertar nodos en el arbol
void insertar(nodo *&arbol, int n){
    if(arbol == nullptr){ //si el arbol esta vacio, crear un nuevo nodo
        nodo *nuevonodo = crearnodo(n);
        arbol = nuevonodo;  
    } else { // si el arbol tiene un nodo o mas
        int raiz = arbol->dato; //obtenenmos valor de la raiz
        if(n < raiz){
            insertar(arbol->izq, n); //si el elemento es menor  a la raiz, insertamos en el lado izquierdo
        } else {
            insertar(arbol->dere,n); //si el elemento es mayor insertamos en el lado derecho
        }
    }
}