#include <iostream>
#include <string>
using namespace std;

// Esto es lo que vamos a guardar (puede ser int, string, etc.)
typedef int Dato;
// CLASE NODO: Un eslabón de la cadena
class nodo{
private:
    nodo* siguiente; // Puntero al siguiente nodo
    Dato dato;  // El número o dato que guardamos
public:
    //constructor 
    nodo(Dato t){
        dato = t;
        siguiente= NULL; // Al principio no apunta a nadie
    }
    nodo(Dato p, nodo* n){
        dato = p;
        siguiente = n;
    }
    
    Dato datonodo ( ) const {return dato;} //estos son los getters
    nodo* enlacenodo() const {return siguiente;} //otro getters
    void ponerenlace(nodo *sgt) { 
        siguiente = sgt;
    } // Método para cambiar a quién apunta (setter)

};
// CLASE LISTA: La cadena completa
class lista{
protected:
    nodo*primero;  // Apunta al primer nodo (inicio de la lista)
public:
    lista() {   primero = nullptr;} // Constructor: crear una lista vacía
    void crearlista(); // Métodos que vamos a implementar
    void insertarcabezalista(Dato entrada);
    void visualizar();

};




