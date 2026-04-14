#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack(push,1)  // evita padding en las lecturas binarias

struct Datos {
    uint16_t cadena;      
    uint32_t estudiantes; 
    uint32_t cursos;      
    uint32_t matriculas;  
};

struct Estudiantes {
    uint32_t id_estudiante; 
    uint8_t  banderas;      
    char     nombre_est[23]; 
    uint32_t edad;          
};
struct Cursos{
    uint32_t id_curso;
    char nomb_curso[32];
    uint32_t hor_cred;
};
struct Matricula{
    uint32_t id_estudiante;
    uint32_t id_curso;
    uint32_t anio;
    uint32_t semestre;
};

#pragma pack(pop)

void calcular_promedio_por_curso(struct Estudiantes *estudiantes, int num_est,
                                  struct Cursos *cursos, int num_cursos,
                                  struct Matricula *matriculas, int num_mat) {
    
    for(int i = 0; i < num_cursos; i++) {
        double suma_edad = 0;
        int contador = 0;
        
 
        for(int j = 0; j < num_mat; j++) {
            if(matriculas[j].id_curso == cursos[i].id_curso) {
                for(int k = 0; k < num_est; k++) {
                    if(estudiantes[k].id_estudiante == matriculas[j].id_estudiante) {
                        suma_edad += estudiantes[k].edad;
                        contador++;
                        break;
                    }
                }
            }
        }
        
        if(contador > 0) {
            double promedio = suma_edad / contador;
            printf("%-32s %.1f\n", cursos[i].nomb_curso, promedio);
        } else {
            printf("%-32s N/A\n", cursos[i].nomb_curso);
        }
    }
}

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("uso: %s <archivo bin>", argv[0]);
        return 1;
    }

    const char* filename = argv[1];

    struct Datos datos;
    FILE * fp = fopen("archivo.bin", "rb");
    if(fp == NULL){
        perror("no se ha podido abrir el archivo");
        return 1;
    } 

    if(fread(&datos, sizeof(datos), 1, fp) !=1){
        perror("error leyendo el encabezado");
        return 1;
    }

    struct Estudiantes estudiantes[(size_t) datos.estudiantes];
    if(fread(&estudiantes, sizeof(struct Estudiantes),datos.estudiantes, fp ) != datos.estudiantes){
        perror("error leyendo estudiantes");
        return 1;
    }

    struct Cursos cursos[(size_t) datos.cursos];
    if(fread(&cursos, sizeof(struct Cursos), datos.cursos, fp) !=datos.cursos){
        perror("error leyendo cursos");
        return 1;
    }

    struct Matricula matricula[(size_t)datos.matriculas];
    if(fread(&matricula, sizeof(struct Matricula), datos.matriculas,fp) != datos.matriculas)
{
    perror("no se ha podido leer matricula");
    return 1;
}
    printf("%-32s %-32s\n", "Cursos", "Edad promedio");

    calcular_promedio_por_curso(estudiantes, datos.estudiantes,
                                 cursos, datos.cursos,
                                 matricula, datos.matriculas);



    fclose(fp);

    return 0;
}

