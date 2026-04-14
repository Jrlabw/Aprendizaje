#include<stdlib.h>
#include<stdio.h>
// #include<string.h>

void swap(int *a, int *b) {
    // cambio de posicion en un array
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printArrayReverse(int arr[], int size) {
    //imprimir array al contrario con for pero al reves jeje
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void printArray(int arreglo[], int tamano);


int main()
{
    int cantidad;
    int *array;
    int i;

    printf("ingrese el tamaño de su array\n");
    scanf("%i", &cantidad);
    //memoria dinamica
    array = (int*)malloc(sizeof(int) * cantidad);
    if (array == NULL){
        printf("no se puedo asignar memoria\n");
        return 1;
    }
    //para tener los datos del array
     for (i= 0; i < cantidad; i++){
        printf("ingrese los datos del array: %i\n", i);
        scanf("%i", &array[i]);
    }
    printArrayReverse(array, cantidad);

    

  
    //imprimir contenido del array pero como la funcion ya la imprime no paja nada
    // printf("contenido del array: \n");
    // for (i=0; i<cantidad; i++){
    //     printf(" %i\n", array[i]);
    // }
    // printf("\n");

    free (array);



   
    return 0;
}


