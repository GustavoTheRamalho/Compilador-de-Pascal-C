#include "Simbolo.h"
#ifndef NO_H
#define NO_H


class No
{
    public:
        No(Simbolo);
        Simbolo valor;
        No* proximo;
        ~No();

    protected:

    private:

};

#endif // NO_H
