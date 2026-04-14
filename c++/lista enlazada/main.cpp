#include <iostream>
#include <string>
#include "hola.h"
using namespace std;


int main(){
    Dato d;
    lista Lista;
    cout << "elementos de la lista, termina en -1 " <<endl;
    do {
        cin >> d;
        Lista.insertarcabezalista(d);
    }while(d != -1);
    //recorre la lista para escribir sus elementos
    cout << "elementos de la lista generados al azar " << endl;
    Lista.visualizar();
    return 0;



}