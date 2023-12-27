#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atmi.h>
#include <userlog.h>
#include <fml32.h>
#include "biblioOper.fml.h"

int cliCalcAreaEquOper(float fvA_base, float fvA_operaDos, float *fvA_resul);

typedef int (*opera) (float fvA_base, float fvA_altura, float *fvA_resul);
opera selecOperacion(int ivA_oper);

int main(int argc, char **argv) {
    int ivL_oper;
    float fvL_base;
    float fvL_altura;
    float fvL_resul;
    opera svL_obtOpera;

    if (argc != 4) {
        printf("Modo de uso: cliTuxedoOper OPERACION OPER1 OPER2");
    }

    ivL_oper = atoi(argv[1]);
    fvL_base = (float) atof(argv[2]);
    fvL_altura = (float) atof(argv[3]);

    svL_obtOpera = selecOperacion(ivL_oper);
    svL_obtOpera(fvL_base, fvL_altura, &fvL_resul);
    printf("Resultado de la operación: %f \n", fvL_resul);

    return 0;
}

opera selecOperacion(int ivA_oper) {
    opera svL_obtOpera;
    switch (ivA_oper)
    {
    case 1:
        svL_obtOpera = cliCalcAreaEquOper;
        break;
    default:
        break;
    }

    return svL_obtOpera;
}

int cliCalcAreaEquOper(float fvA_base, float fvA_altura, float *fvA_resul) {
    int lvL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;

    printf("Conectamos la aplicación\n");
    if (tpinit((TPINIT *) NULL) == -1) {
        printf("Error en la conexo+on con la aplicación, tperrno = %d\n", tperrno);
        return (1);
    }

    printf("Reservamos espacio para el buffer FML\n");
    if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL) {
        printf("Error Reservando espacio para el Buffer FML\n");
        tpterm();
        return (1);
    }

    printf("Insertamos datos en buffer FML\n");
    if (Fadd32 (fbfr, OPERUN, (char *) &fvA_base, 0) < 0) {
        printf("Error insertando campo FML (OPERUN)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return 0;
    }
    if (Fadd32 (fbfr, OPERUN, (char *) &fvA_altura, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return 0;
    }

    printf("Llamamos al servicio 'servCalcAreaTriaEqu'\n");
    if (tpcall("servCalcAreaTriaEqu", (char *)fbfr, 0, (char **)&fbfr, &lvL_tamLongt, 0L) == -1) {
        printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return 0;
    }

    if (Fget32(fbfr, RESUL, 0, (char *)&fvL_recValor, 0) < 0) {
        userlog("No se leyo el resultado\n");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    *fvA_resul = fvL_recValor;
    printf("Liberamos buffer y desconectamos de la aplicación\n");
    tpfree((char *)fbfr);
    tpterm();
    return 0;
}
