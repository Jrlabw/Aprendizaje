#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* codigo BFS (breath first search)
descripciomn: recorrer un grafo nivel por nivel
parametros:
    -strart: nodo desde comenzar
    adj: lista de adyacencia del grafo
    complejidad O(V + E) donde v=vectices, E=aristas
*/

void BFS(int start, const vector<vector<int>>&adj){
    //paso 1: obtener numeros de nodos
     int n = adj.size();
    

    //paso 2: crear structura de datos
    vector<bool>visited(n,false); //para mercar nodos visitados
    queue<int>q; //cola para BFS

    //paso 3: manejo de nodo incial
    cout << "iniciando bfs desde el nodo" << start << endl;

    //marcar el nodo inicial como visitado 
    visited[start] = true;

    //agregar el nodo inicial a la cola
    q.push(start);

    //paso 4: procesar cola
    int nivel = 0; // para mostrar los niveles
    while(!q.empty()){
        //mostrar nivel que estamos
        cout << "nivel" << nivel << endl;

        //procesar todos los nodos del nivel actual
        int nodoEnEsteNivel = q.size();

        for(int i = 0; i < nodoEnEsteNivel;i++){
            //sacar el primer nodo de la cola
            int nodoActual = q.front();
            q.pop();
            //procesar el nodo (en este caso,imprimirlo)
            cout << nodoActual << " " ;

            //paso 5: visitar todos los vecinos
            //recorrer todos los nodos conectados del nodo actual
            for(int vecino : adj[nodoActual]){
                //si el vecino no ha sido visitado
                if(!visited[vecino]){
                    //marcalo como visitado(importante: hacerlo antes de encolar)
                    visited[vecino] = true;
                    //agregar al final de la cola
                    q.push(vecino);
                }
            }

        }
        cout << endl;
        nivel++;
    }
    cout << " bfs completado, total niveles: " << nivel - 1 <<endl;
}


//funcion para mostrar un grafo
void mostrarGrafo(const vector<vector<int>>&adj){
    cout << " grafo(lista de adyacencia)";
    for(int i = 0; i < adj.size();i++){
        cout << "nodo " << i << " -> ";
        for(int vecino : adj[i]){
            cout << vecino << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    // EJEMPLO 1: GRAFO SIMPLE
    cout << "=== EJEMPLO 1 ===" << endl;
    
    /*
        Grafo:
            0
           / \
          1   2
         / \   \
        3   4   5
    */
    
    vector<vector<int>> grafo1 = {
        {1, 2},      // Nodo 0 conectado a 1 y 2
        {0, 3, 4},   // Nodo 1 conectado a 0, 3 y 4
        {0, 5},      // Nodo 2 conectado a 0 y 5
        {1},         // Nodo 3 conectado a 1
        {1},         // Nodo 4 conectado a 1
        {2}          // Nodo 5 conectado a 2
    };
    
    mostrarGrafo(grafo1);
    BFS(0, grafo1);
    
    cout << "\n" << string(50, '-') << "\n\n";
    
    // EJEMPLO 2: GRAFO CON CICLO
    cout << "=== EJEMPLO 2 ===" << endl;
    
    /*
        Grafo:
            0
           / \
          1---2
           \ /
            3
    */
    
    vector<vector<int>> grafo2 = {
        {1, 2},      // Nodo 0
        {0, 2, 3},   // Nodo 1
        {0, 1, 3},   // Nodo 2
        {1, 2}       // Nodo 3
    };
    
    mostrarGrafo(grafo2);
    BFS(0, grafo2);
    
    return 0;
}



void bfs(vector<vector<int>>&graph)