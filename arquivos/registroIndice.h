#ifndef REGISTROINDICE_H
    #define REGISTROINDICE_H
        #include <stdio.h>
        #include <stdlib.h>
        #include <stdbool.h>

        typedef struct _registro_indice REGISTRO_INDICE;

        REGISTRO_INDICE *criarRegistroIndice();
        void apagarRegistroIndice(REGISTRO_INDICE *registro);
        void setIndexRegistroIndice(REGISTRO_INDICE *registro, int index);
        void setByteOffsetRegistroIndice(REGISTRO_INDICE *registro, long long int byteOffset);
        int getIndexRegistroIndice(REGISTRO_INDICE *registro);
        long long int getByteOffsetRegistroIndice(REGISTRO_INDICE *registro);
#endif