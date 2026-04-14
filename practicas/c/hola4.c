#include <stdio.h>


int main(int argc, char const *argv[])
{
  int opcion;
  char letras[50] = 'a-zA-Z';
  printf("menu\n");

  do{
    printf("seleccion una opcion [1/5]: \n");
    scanf("%d", &opcion);
    printf("has elegido %d\n", opcion);
    if (opcion == (letras)){
      printf("no se permite letras");
      return 1;
    }
  }while (opcion < 1 || opcion > 5);






  // FILE * archivo = fopen("WAZA.txt", "r+b");
  // if (archivo == NULL){
  //   printf("Su archivo no se ha podido leer");
  // }
  // // para leer todo el archivo
  // char tamanio[80];
  // do{
  //       if (fgets(tamanio, 80, archivo)){
  //           printf("%s", tamanio);
  //       }

  // }while (!feof(archivo));



  // para leer caracter por caracter
//   do{
//     int lectura = fgetc(archivo);
//     if (!feof(archivo)){
//         printf("%c", (char)lectura);
//     } else {
//         printf("==FIN==");
//     }
//     }while(!feof(archivo));

    return 0;
}
