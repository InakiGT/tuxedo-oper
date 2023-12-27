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