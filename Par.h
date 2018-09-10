#ifndef PAR_H
#define PAR_H
#include "Elemento.h"

    typedef void *Par;
    Par createPar(Elemento e1, Elemento e2);
    Elemento getElementoPar(Par p);
#endif