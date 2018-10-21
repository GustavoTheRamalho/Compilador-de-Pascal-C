#include "Simbolo.h"
#include "No.h"
#ifndef TABELADESIMBOLO_H
#define TABELADESIMBOLO_H

//IMPLEMENTAR M�TODOS QUE RETORNEM O TIPO DE RETORNO DO IDENTIFICADOR E A QUANTIDADE DE PAR�METROS

class TabelaDeSimbolo
{
    public:
        TabelaDeSimbolo();
        void guarde(Simbolo) throw();
        void elimineNivel(int);
        char* toString();
        Simbolo getSimbolo(char*) throw(int);
        int existeSimbolo(char*) throw();
        ~TabelaDeSimbolo() throw();
        TabelaDeSimbolo(const TabelaDeSimbolo&) throw();
        TabelaDeSimbolo& operator=(const TabelaDeSimbolo&) throw();

    protected:

    private:
        No* head;
};

#endif // TABELADESIMBOLO_H

