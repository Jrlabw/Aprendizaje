#include <stdio.h>
#include <stdlib.h>

void imprimirarray(int * num, int tamanio){
    for(int i = 0; i < tamanio; i++){
        printf("los datos de su array son: %d\n", num[i]);
    }
}

void imprimirdatosalre(int * num, int tamanio){
    for(int i = tamanio - 1; i >= 0; i--){
        printf("los datos de su array al reves son: %d\n", num[i]);
    }
}

void cambiar_datos(int *num1, int *num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
    printf("datos cambiados %d %d", *num1 , *num2);
}

int main(){
    int *ptr_num;
    int cantidad = 5;
    int i;
    int num = *ptr_num;

    ptr_num = (int*)malloc(sizeof(int) * cantidad);

    for( i = 0; i < cantidad; i++){
        printf("ingrese los datos de su array");
        scanf("%d", &ptr_num[i]);
    }

    imprimirdatosalre(ptr_num,cantidad);
    cambiar_datos(&ptr_num[0],&ptr_num[2]);

    

    

}   