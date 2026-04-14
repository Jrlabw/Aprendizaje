#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack(push, 1)
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

struct Cursos {
    uint32_t id_curso;
    char nomb_curso[32];
    uint32_t hor_cred;
};

struct Matricula {
    uint32_t id_estudiante;
    uint32_t id_curso;
    uint32_t anio;
    uint32_t semestre;
};
#pragma pack(pop)

// ========== FUNCIONES HELPER ==========

// Buscar estudiante por ID
int buscar_estudiante(struct Estudiantes *estudiantes, uint32_t num_estudiantes, uint32_t id) {
    for (uint32_t i = 0; i < num_estudiantes; i++) {
        if (estudiantes[i].id_estudiante == id) {
            return i;
        }
    }
    return -1;
}

// Verificar si es mujer (bit 7 = 1)
int es_mujer(uint8_t banderas) {
    return (banderas & 0x80) != 0;  // 0x80 = 10000000 en binario
}

// Verificar si es posgrado (bit 6 = 1)
int es_posgrado(uint8_t banderas) {
    return (banderas & 0x40) != 0;  // 0x40 = 01000000 en binario
}

// ========== FUNCIÓN PRINCIPAL: PROCESAR SEMESTRE ==========
/*
 * Esta función hace TODO el trabajo:
 * 1. Busca todas las matrículas de un semestre específico
 * 2. Cuenta estudiantes DISTINTOS
 * 3. Los clasifica por género y tipo
 * 4. Imprime el resultado
 */
void procesar_semestre(
    uint32_t anio, 
    uint32_t semestre,
    struct Matricula *matriculas, 
    uint32_t num_matriculas,
    struct Estudiantes *estudiantes, 
    uint32_t num_estudiantes
) {
    // Contadores para este semestre
    int hombres_pregrado = 0;
    int mujeres_pregrado = 0;
    int hombres_posgrado = 0;
    int mujeres_posgrado = 0;
    
    // Array para marcar estudiantes ya contados
    // calloc inicializa todo en 0 automáticamente
    int *contados = calloc(num_estudiantes, sizeof(int));
    if (contados == NULL) {
        printf("Error: No se pudo asignar memoria\n");
        return;
    }
    
    // Recorrer TODAS las matrículas
    for (uint32_t i = 0; i < num_matriculas; i++) {
        // ¿Esta matrícula pertenece al semestre que estamos procesando?
        if (matriculas[i].anio == anio && matriculas[i].semestre == semestre) {
            uint32_t id_est = matriculas[i].id_estudiante;
            
            // Buscar el índice del estudiante en el array
            int idx_est = buscar_estudiante(estudiantes, num_estudiantes, id_est);
            
            // Si encontramos al estudiante Y no lo hemos contado aún
            if (idx_est >= 0 && !contados[idx_est]) {
                // MARCAR como contado
                contados[idx_est] = 1;
                
                // Obtener las banderas del estudiante
                uint8_t banderas = estudiantes[idx_est].banderas;
                
                // Extraer género y tipo usando máscaras de bits
                int mujer = es_mujer(banderas);      // bit 7
                int posgrado = es_posgrado(banderas); // bit 6
                
                // Clasificar en la categoría correcta
                if (posgrado) {
                    if (mujer) {
                        mujeres_posgrado++;
                    } else {
                        hombres_posgrado++;
                    }
                } else {  // pregrado
                    if (mujer) {
                        mujeres_pregrado++;
                    } else {
                        hombres_pregrado++;
                    }
                }
            }
        }
    }
    
    // Imprimir resultado para este semestre
    printf("%-6u %-10u %-18d %-20d %-16d %-18d\n",
           anio,
           semestre,
           hombres_pregrado,
           mujeres_pregrado,
           hombres_posgrado,
           mujeres_posgrado);
    
    // Liberar memoria
    free(contados);
}

// ========== FUNCIÓN: ENCONTRAR SEMESTRES ÚNICOS ==========
/*
 * Esta función encuentra todos los pares (año, semestre) únicos
 * Retorna cuántos semestres únicos encontró
 */
int encontrar_semestres_unicos(
    struct Matricula *matriculas,
    uint32_t num_matriculas,
    uint32_t **anios_out,      
    uint32_t **semestres_out   
) {
 
    uint32_t *anios = malloc(sizeof(uint32_t) * num_matriculas);
    uint32_t *semestres = malloc(sizeof(uint32_t) * num_matriculas);
    int count = 0;
    
    if (anios == NULL || semestres == NULL) {
        free(anios);
        free(semestres);
        return 0;
    }
    
    // Buscar semestres únicos
    for (uint32_t i = 0; i < num_matriculas; i++) {
        uint32_t anio = matriculas[i].anio;
        uint32_t semestre = matriculas[i].semestre;
        
        // ¿Ya vimos este semestre?
        int ya_existe = 0;
        for (int j = 0; j < count; j++) {
            if (anios[j] == anio && semestres[j] == semestre) {
                ya_existe = 1;
                break;
            }
        }
        
        // Si es nuevo, agregarlo
        if (!ya_existe) {
            anios[count] = anio;
            semestres[count] = semestre;
            count++;
        }
    }
    
    // Ordenar por año y luego por semestre (bubble sort simple)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            // Si año[j] > año[j+1] O (mismo año pero semestre[j] > semestre[j+1])
            if (anios[j] > anios[j + 1] || 
                (anios[j] == anios[j + 1] && semestres[j] > semestres[j + 1])) {
                // Intercambiar años
                uint32_t temp = anios[j];
                anios[j] = anios[j + 1];
                anios[j + 1] = temp;
                
                // Intercambiar semestres
                temp = semestres[j];
                semestres[j] = semestres[j + 1];
                semestres[j + 1] = temp;
            }
        }
    }
    
    *anios_out = anios;
    *semestres_out = semestres;
    return count;
}

// ========== MAIN ==========

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo.bin>\n", argv[0]);
        return 1;
    }

    // Abrir archivo usando el argumento correcto
    FILE *fp = fopen("archivo.bin", "rb");
    if (fp == NULL) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    // Leer encabezado
    struct Datos datos;
    if (fread(&datos, sizeof(datos), 1, fp) != 1) {
        perror("No se pudo leer el encabezado");
        fclose(fp);
        return 1;
    }


    // Asignar memoria para estudiantes
    struct Estudiantes *estudiantes = malloc(sizeof(struct Estudiantes) * datos.estudiantes);
    if (estudiantes == NULL) {
        perror("Error al asignar memoria para estudiantes");
        fclose(fp);
        return 1;
    }

    // Leer estudiantes
    if (fread(estudiantes, sizeof(struct Estudiantes), datos.estudiantes, fp) != datos.estudiantes) {
        printf("Error: No se pudieron leer estudiantes\n");
        free(estudiantes);
        fclose(fp);
        return 1;
    }

    // Asignar memoria para cursos
    struct Cursos *cursos = malloc(sizeof(struct Cursos) * datos.cursos);
    if (cursos == NULL) {
        perror("Error al asignar memoria para cursos");
        free(estudiantes);
        fclose(fp);
        return 1;
    }

    // Leer cursos
    if (fread(cursos, sizeof(struct Cursos), datos.cursos, fp) != datos.cursos) {
        printf("Error: No se pudieron leer cursos\n");
        free(estudiantes);
        free(cursos);
        fclose(fp);
        return 1;
    }

    // Asignar memoria para matrículas
    struct Matricula *matriculas = malloc(sizeof(struct Matricula) * datos.matriculas);
    if (matriculas == NULL) {
        perror("Error al asignar memoria para matrículas");
        free(estudiantes);
        free(cursos);
        fclose(fp);
        return 1;
    }

    // Leer matrículas
    if (fread(matriculas, sizeof(struct Matricula), datos.matriculas, fp) != datos.matriculas) {
        printf("Error: No se pudieron leer matrículas\n");
        free(estudiantes);
        free(cursos);
        free(matriculas);
        fclose(fp);
        return 1;
    }

    fclose(fp);

    // ========== PROCESAR DATOS ==========
    
    // Paso 1: Encontrar todos los semestres únicos
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
    
    // Paso 2: Imprimir encabezado
    printf("%-6s %-10s %-18s %-20s %-16s %-18s\n",
           "Year", "Semester", "Undergrad Males", "Undergrad Females", "Grad Males", "Grad Females");
    printf("---------------------------------------------------------------------------------------------\n");
    
    // Paso 3: Procesar cada semestre
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

    // Liberar toda la memoria
    free(anios);
    free(semestres);
    free(estudiantes);
    free(cursos);
    free(matriculas);

    return 0;
}