#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atmi.h>
#include <userlog.h>
#include <fml32.h>
#include "biblioOper.fml.h"

int cliCalcAreaEquOper(float fvA_op1, float fvA_op2, float fvA_op3, float fvA_op4, float fvA_op5, float fvA_op6, float *fvA_resul);
int cliCalcDistDosPtos(float fvA_op1, float fvA_op2, float fvA_op3, float fvA_op4, float fvA_op5, float fvA_op6, float *fvA_resul);
int cliCalcProdCruz(float fvA_op1, float fvA_op2, float fvA_op3, float fvA_op4, float fvA_op5, float fvA_op6, float *fvA_resul);

typedef int (*opera) (float fvA_op1, float fvA_op2, float fvA_op3, float fvA_op4, float fvA_op5, float fvA_op6, float *fvA_resul);
opera selecOperacion(int ivA_oper);

int main(int argc, char **argv) {
    int ivL_oper;
    float fvL_op1;
    float fvL_op2;
    float fvL_op3;
    float fvL_op4;
    float fvL_op5;
    float fvL_op6;
    float fvL_resul;
    opera svL_obtOpera;

    if (argc < 4 || argc > 8) {
        printf("Modo de uso: cliTuxedoOper OPERACION OPER1 OPER2");

        return -1;
    }

    ivL_oper = atoi(argv[1]);
    fvL_op1 = (float) atof(argv[2]);
    fvL_op2 = (float) atof(argv[3]);
    fvL_op3 = argc > 5 ? (float) atof(argv[4]) : 0;
    fvL_op4 = argc > 5 ? (float) atof(argv[5]) : 0;
    fvL_op5 = argc > 7 ? (float) atof(argv[6]) : 0;
    fvL_op6 = argc > 7 ? (float) atof(argv[7]) : 0;

    svL_obtOpera = selecOperacion(ivL_oper);
    svL_obtOpera(fvL_op1, fvL_op2, fvL_op3, fvL_op4, fvL_op5, fvL_op6, &fvL_resul);
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
    case 2:
        svL_obtOpera = cliCalcDistDosPtos;
        break;
    case 3:
        svL_obtOpera = cliCalcProdCruz;
        break;
    default:
        break;
    }

    return svL_obtOpera;
}

int cliCalcAreaEquOper (float fvA_op1, float fvA_op2, float fvA_op3, float fvA_op4, float fvA_op5, float fvA_op6, float *fvA_resul) {
    int lvL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;

    printf("Conectamos la aplicación\n");
    if (tpinit((TPINIT *) NULL) == -1) {
        printf("Error en la conexión con la aplicación, tperrno = %d\n", tperrno);
        return -1;
    }

    printf("Reservamos espacio para el buffer FML\n");
    if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL) {
        printf("Error Reservando espacio para el Buffer FML\n");
        tpterm();
        return -1;
    }

    printf("Insertamos datos en buffer FML\n");
    if (Fadd32 (fbfr, OPERUN, (char *) &fvA_op1, 0) < 0) {
        printf("Error insertando campo FML (OPERUN)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }
    if (Fadd32 (fbfr, OPERDO, (char *) &fvA_op2, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    printf("Llamamos al servicio 'servCalcAreaTriaEqu'\n");
    if (tpcall("servCalcAreaTriaEqu", (char *)fbfr, 0, (char **)&fbfr, &lvL_tamLongt, 0L) == -1) {
        printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
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

int cliCalcDistDosPtos (float fvA_op1, float fvA_op2, float fvA_op3, float fvA_op4, float fvA_op5, float fvA_op6, float *fvA_resul) {
    int lvL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;

    printf("Conectamos la aplicación\n");
    if (tpinit((TPINIT *) NULL) == -1) {
        printf("Error en la conexión con la aplicación, tperrno = %d\n", tperrno);
        return -1;
    }

    printf("Reservamos espacio para el buffer FML\n");
    if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL) {
        printf("Error Reservando espacio para el Buffer FML\n");
        tpterm();
        return -1;
    }

    printf("Insertamos datos en buffer FML\n");
    if (Fadd32 (fbfr, OPERUN, (char *) &fvA_op1, 0) < 0) {
        printf("Error insertando campo FML (OPERUN)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERDO, (char *) &fvA_op2, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERTRE, (char *) &fvA_op3, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERCUA, (char *) &fvA_op4, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERCIN, (char *) &fvA_op4, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERSEI, (char *) &fvA_op4, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    printf("Llamamos al servicio 'servCalcDistDosPtos'\n");
    if (tpcall("servCalcDistDosPtos", (char *)fbfr, 0, (char **)&fbfr, &lvL_tamLongt, 0L) == -1) {
        printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
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

int cliCalcProdCruz (float fvA_op1, float fvA_op2, float fvA_op3, float fvA_op4, float fvA_op5, float fvA_op6, float *fvA_resul) {
    int lvL_resLlamd;
    long lvL_tamLongt;
    float fvL_recValor;
    FBFR32 *fbfr;

    printf("Conectamos la aplicación\n");
    if (tpinit((TPINIT *) NULL) == -1) {
        printf("Error en la conexión con la aplicación, tperrno = %d\n", tperrno);
        return -1;
    }

    printf("Reservamos espacio para el buffer FML\n");
    if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 256)) == NULL) {
        printf("Error Reservando espacio para el Buffer FML\n");
        tpterm();
        return -1;
    }

    printf("Insertamos datos en buffer FML\n");
    if (Fadd32 (fbfr, OPERUN, (char *) &fvA_op1, 0) < 0) {
        printf("Error insertando campo FML (OPERUN)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERDO, (char *) &fvA_op2, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERTRE, (char *) &fvA_op3, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    if (Fadd32 (fbfr, OPERCUA, (char *) &fvA_op4, 0) < 0) {
        printf("Error insertando campo FML (OPERDO)\n");
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
    }

    printf("Llamamos al servicio 'servCalcProdCruz'\n");
    if (tpcall("servCalcProdCruz", (char *)fbfr, 0, (char **)&fbfr, &lvL_tamLongt, 0L) == -1) {
        printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        printf("Liberamos buffer y desconectamos de la aplicación\n");
        tpfree((char *)fbfr);
        tpterm();
        return -1;
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