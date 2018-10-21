#include "AnalisadorLexico.h"
#ifndef SIMBOLO_H
#define SIMBOLO_H


class Simbolo
{
    public:
       // void setNome(char[255]) throw();
        void setTipo(TipoPedaco) throw();
        char* getNome() throw();
        TipoPedaco getTipo() const throw();
        int getNivel() const throw();
        Simbolo() throw();
        Simbolo (TipoPedaco, char*, int, int, int, char**) throw();
        int getRetorno() const throw();
        int getQtsParams() throw();
        char* getProximoParametro() throw();
        ~Simbolo() throw();
        Simbolo(const Simbolo&) throw();
        Simbolo& operator=(const Simbolo&) throw();

    protected:

    private:
        int nivel;
        TipoPedaco tipo;
        char* nome;
        int retorno; //caso seja 0, é procedure, 1 é inteiro e 2 é boolean
        //int (*parametros);
        char** parametros;
        int qtsParametros;
        //Dados dados;

};

#endif // SIMBOLO_H
