#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack (push,1)
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

int buscar_estudiante(struct Estudiantes *estudiantes, uint32_t num_estudiantes, uint32_t id) {
    for (uint32_t i = 0; i < num_estudiantes; i++) {
        if (estudiantes[i].id_estudiante == id) {
            return i;
        }
    }
    return -1;
}


int es_mujer(uint8_t banderas) {
    return (banderas & 0x80) != 0;  
}


int es_posgrado(uint8_t banderas) {
    return (banderas & 0x40) != 0;  
}


void procesar_semestre(uint32_t anio, uint32_t semestre,struct Matricula *matriculas, uint32_t num_matriculas,
                struct Estudiantes *estudiantes, uint32_t num_estudiantes)
 {

    int hombres_pregrado = 0;
    int mujeres_pregrado = 0;
    int hombres_posgrado = 0;
    int mujeres_posgrado = 0;
    
    int *contados = calloc(num_estudiantes, sizeof(int));
    if (contados == NULL) {
        printf("Error: No se pudo asignar memoria\n");
        return;
    }
    

    for (uint32_t i = 0; i < num_matriculas; i++) {
        if (matriculas[i].anio == anio && matriculas[i].semestre == semestre) {
            uint32_t id_est = matriculas[i].id_estudiante;
            
           
            int idx_est = buscar_estudiante(estudiantes, num_estudiantes, id_est);
            
            if (idx_est >= 0 && !contados[idx_est]) {
                contados[idx_est] = 1;
                
                uint8_t banderas = estudiantes[idx_est].banderas;
                
                int mujer = es_mujer(banderas);     
                int posgrado = es_posgrado(banderas);
                if (posgrado) {
                    if (mujer) {
                        mujeres_posgrado++;
                    } else {
                        hombres_posgrado++;
                    }
                } else { 
                    if (mujer) {
                        mujeres_pregrado++;
                    } else {
                        hombres_pregrado++;
                    }
                }
            }
        }
    }
    
    printf("%-6u %-10u %-18d %-20d %-16d %-18d\n",
           anio,
           semestre,
           hombres_pregrado,
           mujeres_pregrado,
           hombres_posgrado,
           mujeres_posgrado);
    
    free(contados);
}


int encontrar_semestres_unicos(struct Matricula *matriculas,uint32_t num_matriculas,uint32_t **anios_out,uint32_t **semestres_out) 
{

    uint32_t *anios = malloc(sizeof(uint32_t) * num_matriculas);
    uint32_t *semestres = malloc(sizeof(uint32_t) * num_matriculas);
    int cuenta = 0;
    
    if (anios == NULL || semestres == NULL) {
        free(anios);
        free(semestres);
        return 0;
    }
    
  
    for (uint32_t i = 0; i < num_matriculas; i++) {
        uint32_t anio = matriculas[i].anio;
        uint32_t semestre = matriculas[i].semestre;
        

        int ya_existe = 0;
        for (int j = 0; j < cuenta; j++) {
            if (anios[j] == anio && semestres[j] == semestre) {
                ya_existe = 1;
                break;
            }
        }
        
        if (!ya_existe) {
            anios[cuenta] = anio;
            semestres[cuenta] = semestre;
            cuenta++;
        }
    }
    

    for (int i = 0; i < cuenta - 1; i++) {
        for (int j = 0; j < cuenta - i - 1; j++) {
            if (anios[j] > anios[j + 1] || 
                (anios[j] == anios[j + 1] && semestres[j] > semestres[j + 1])) {
                uint32_t temp = anios[j];
                anios[j] = anios[j + 1];
                anios[j + 1] = temp;
                temp = semestres[j];
                semestres[j] = semestres[j + 1];
                semestres[j + 1] = temp;
            }
        }
    }
    
    *anios_out = anios;
    *semestres_out = semestres;
    return cuenta;
}



int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("%s <archivo.bin>",argv[0]);
        return 1;
    }

    const char *Filename = argv[1];

    struct Datos datos;

    FILE * fp = fopen("archivo.bin", "rb");
    if(fp == NULL){
        perror("no se pudo abrir el archivo");
        return 1;
    }

    

    if(fread(&datos, sizeof(datos),1,fp) !=1){
        perror("no se ha podido leer el encabezado");
        return 1;
    }  


    struct Estudiantes *estudiantes = malloc(sizeof(struct Estudiantes) * datos.estudiantes);
    if (estudiantes == NULL) {
        perror("Error al asignar memoria para estudiantes");
        fclose(fp);
        return 1;
    }

    if (fread(estudiantes, sizeof(struct Estudiantes), datos.estudiantes, fp) != datos.estudiantes) {
        printf("Error: No se pudieron leer estudiantes\n");
        free(estudiantes);
        fclose(fp);
        return 1;
    }


    struct Cursos *cursos = malloc(sizeof(struct Cursos) * datos.cursos);
    if (cursos == NULL) {
        perror("Error al asignar memoria para cursos");
        free(estudiantes);
        fclose(fp);
        return 1;
    }


    if (fread(cursos, sizeof(struct Cursos), datos.cursos, fp) != datos.cursos) {
        printf("Error: No se pudieron leer cursos\n");
        free(estudiantes);
        free(cursos);
        fclose(fp);
        return 1;
    }


    struct Matricula *matriculas = malloc(sizeof(struct Matricula) * datos.matriculas);
    if (matriculas == NULL) {
        perror("Error al asignar memoria para matrículas");
        free(estudiantes);
        free(cursos);
        fclose(fp);
        return 1;
    }


    if (fread(matriculas, sizeof(struct Matricula), datos.matriculas, fp) != datos.matriculas) {
        printf("Error: No se pudieron leer matrículas\n");
        free(estudiantes);
        free(cursos);
        free(matriculas);
        fclose(fp);
        return 1;
    }
    fclose(fp);
    
    
    
    
    uint32_t *anios;
    uint32_t *semestres;
    int num_semestres = encontrar_semestres_unicos(matriculas, datos.matriculas, &anios, &semestres);
    
    if (num_semestres == 0) {
        printf("No se encontraron semestres\n");
        free(estudiantes);
        free(cursos);
        free(matriculas);
        return 1;
    }
    

    printf("%-6s %-10s %-18s %-20s %-16s %-18s\n",
           "Year", "Semester", "Undergrad Males", "Undergrad Females", "Grad Males", "Grad Females");
    printf("---------------------------------------------------------------------------------------------\n");
    

    for (int i = 0; i < num_semestres; i++) {
        procesar_semestre(
            anios[i], 
            semestres[i],
            matriculas, 
            datos.matriculas,
            estudiantes, 
            datos.estudiantes
        );
    }

      free(anios);
    free(semestres);
    free(estudiantes);
    free(cursos);
    free(matriculas);

    return 0;
}


    
    
