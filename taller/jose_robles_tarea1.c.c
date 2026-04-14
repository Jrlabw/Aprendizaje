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

#pragma pack(pop)

void filtro_edad(struct Estudiantes *estudiantes, int min, int max, uint32_t num_estudiantes){
    for (uint32_t i = 0; i < num_estudiantes; i++){
        if(estudiantes[i].edad >= min && estudiantes[i].edad <= max){
            uint8_t genero = (estudiantes[i].banderas & 0x80) >> 7;       // 4 bits más significativos
            // uint8_t posgrado = (estudiantes[i].banderas & 0x40) >> 6;     // 4 bits menos significativos
            printf("%-23s %-10d %s\n", estudiantes[i].nombre_est, estudiantes[i].edad, genero?"Femenino":"Masculino");
        }
    }
}

int main(int argc, char* argv[]){
    if (argc != 4){
        printf("Uso: %s <archivo.bin> <edad_min> <edad_max>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    struct Datos datos;

    FILE *fp = fopen("archivo.bin", "rb"); // usa argv[1]
    if (fp == NULL) {
        perror("Error abriendo archivo");
        return 1;
    }

    // Lee header
    if (fread(&datos, sizeof datos, 1, fp) != 1) {
        fprintf(stderr, "Error leyendo encabezado\n");
        fclose(fp);
        return 1;
    }

    // Arreglo basado en el conteo del header (VLA, válido en GCC/MinGW)
    struct Estudiantes estudiantes[/*VLA*/ (size_t)datos.estudiantes];

    // Lee estudiantes
    if (fread(estudiantes, sizeof(struct Estudiantes), datos.estudiantes, fp)
        != datos.estudiantes) {
        fprintf(stderr, "Error leyendo estudiantes\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);


    printf("%-23s %-10s %s\n", "Name", "Age", "Gender");
    filtro_edad(estudiantes, min, max, datos.estudiantes);

    return 0;
}