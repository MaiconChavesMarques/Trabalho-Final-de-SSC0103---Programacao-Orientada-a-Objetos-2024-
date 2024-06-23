#ifndef BUSCARREGISTRO_H
    #define BUSCARREGISTRO_H

    #include <stdio.h>
    #include <stdlib.h>
    #include "registro.h"
    #include <stdbool.h>
    #include <string.h>
    #include "cabecalho.h"


    REGISTRO *buscarRegistro(char *chave, char *operacao, CABECALHO *cabecalho, FILE *file);

#endif