#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <atmi.h>
#include <userlog.h>
#include <fml32.h>
#include "biblioOper.fml.h"

tpsvrinit (int argc, char *argv[]) {
    userlog("Iniciando srvTuxedoOper");
    return(0);
}

void servCalcAreaTriaEqu(TPSVCINFO *rqst) {
    float fvL_base;
    float fvL_altura;
    float fvL_resul;
    FBFR32* fbfr = (FBFR32*) rqst->data;

    userlog("Servicio servCaclAreaTriaEqu Invocado.");

    if (Fget32(fbfr, OPERUN, 0, (char *)&fvL_base, 0) < 0) {
        userlog("No se leyo la base");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERDO, 0, (char *)&fvL_altura, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    userlog("Base: [%f]", fvL_base);
    userlog("Altura: [%f]", fvL_altura);

    fvL_resul = ( fvL_base * fvL_altura ) / 2;

    Fadd32 (fbfr, RESUL, (char *)&fvL_resul, 0);
    userlog("Resultado de la suma es: [%f]", fvL_resul);

    tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}


void servCalcDistDosPtos(TPSVCINFO *rqst) {
    float fvL_p1_x;
    float fvL_p1_y;
    float fvL_p1_z;
    float fvL_p2_x;
    float fvL_p2_y;
    float fvL_p2_z;
    float fvL_resul;
    FBFR32* fbfr = (FBFR32*) rqst->data;

    userlog("Servicio servCaclAreaTriaEqu Invocado.");

    if (Fget32(fbfr, OPERUN, 0, (char *)&fvL_p1_x, 0) < 0) {
        userlog("No se leyo la base");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERDO, 0, (char *)&fvL_p1_y, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERTRE, 0, (char *)&fvL_p1_z, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERCUA, 0, (char *)&fvL_p2_x, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERCIN, 0, (char *)&fvL_p2_y, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERSEI, 0, (char *)&fvL_p2_z, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    userlog("Punto 1 (%f, %f, %f)", fvL_p1_x, fvL_p1_y, fvL_p1_z);
    userlog("Punto 2 (%f, %f %f)", fvL_p2_x, fvL_p2_y, fvL_p2_z);

    float num = ((fvL_p1_x - fvL_p2_x) * (fvL_p1_x - fvL_p2_x)) + ((fvL_p1_y - fvL_p2_y) * (fvL_p1_y - fvL_p2_y)) + ((fvL_p1_z - fvL_p2_z) * (fvL_p1_z - fvL_p2_z));
    float x = 1;
    float y = (x + num / x) / 2;
    float error_margin = 0.0001;
    while (x - y > error_margin || y - x > error_margin) {
        x = y;
        y = (x + num / x) / 2;
    }
    fvL_resul = y;

    Fadd32 (fbfr, RESUL, (char *)&fvL_resul, 0);
    userlog("Resultado de la suma es: [%f]", fvL_resul);

    tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}

void servCalcProdCruz(TPSVCINFO *rqst) {
    float fvL_a_x;
    float fvL_a_y;
    float fvL_b_x;
    float fvL_b_y;
    float fvL_resul;
    FBFR32* fbfr = (FBFR32*) rqst->data;

    userlog("Servicio servCaclAreaTriaEqu Invocado.");

    if (Fget32(fbfr, OPERUN, 0, (char *)&fvL_a_x, 0) < 0) {
        userlog("No se leyo la base");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERDO, 0, (char *)&fvL_a_y, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERTRE, 0, (char *)&fvL_b_x, 0) < 0) {
        userlog("No se leyo la base");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    if (Fget32(fbfr, OPERCUA, 0, (char *)&fvL_b_y, 0) < 0) {
        userlog("No se leyo la altura");
        tpreturn(TPFAIL, 0, (char *)fbfr, 0L, 0);
    }

    userlog("Vector A: (%f, %f)", fvL_a_x, fvL_a_y);
    userlog("Vector B: (%f, %f)", fvL_b_x, fvL_b_y);

    fvL_resul = fvL_a_x * fvL_b_y - fvL_b_x * fvL_a_y;

    Fadd32 (fbfr, RESUL, (char *)&fvL_resul, 0);
    userlog("Resultado de la suma es: [%f]", fvL_resul);

    tpreturn(TPSUCCESS, 0, rqst->data, 0L, 0);
}