#include "AnalisadorLexico.h"
#include "Simbolo.h"
#include "TabelaDeSimbolo.h"
#include <stdexcept>
#ifndef ANALISADORSINTATICO_H
#define ANALISADORSINTATICO_H


class AnalisadorSintatico
{

    public:
        AnalisadorSintatico(char*);

        void compilaDeclaracaoDeProcedimento() throw(int, int, int, int, int, int, int, int);
        void compilaDeclaracaoDeFuncao() throw(int, int, int, int, int, int, int, int, int);
        void compilaIf(int) throw(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
        void compilaWhile() throw(int);
        void compilaDeclaracaoDeVariavel() throw(int, int, int, int, int, int, int, int, int, int, int);  //OK
        void compilaProgramaPrincipal() throw(int, int, int, int, int, int, int, int);
        void compilaComandoComposto() throw(int, int, int, int, int, int, int, int, int, int, int, int, int, int);
        void compilaParametro() throw(int, int, int, int, int, int, int, int, int, int, int);
        void compilaPrintNaTela() throw(int, int, int, int, int, int, int, int);
        //void compilaLeituraDoTeclado() throw(int, int, int, int, int, int);
        void compilaOperacaoComVariavel() throw(int, int, int, int, int, int, int/*, int, int*/);
        void compilaExpressaoBooleana() throw(int, int, int, int, int, int, int, int);
        void compilaChamadaDeProcOuFuncao(char*) throw(int, int, int, int, int, int, int, int, int, int, int);
        int  identificadorEhValido(int, char*) throw();
        int temElse() throw();
        ~AnalisadorSintatico() throw();
        AnalisadorSintatico(const AnalisadorSintatico&) throw();
        AnalisadorSintatico& operator=(const AnalisadorSintatico&) throw();
        AnalisadorLexico* getAl() const throw();
        TabelaDeSimbolo* getTS() const throw();
        char* tstring();

    protected:

    private:
        AnalisadorLexico* al;
        Simbolo prox;
        int nivelAtual;
        TabelaDeSimbolo* ts;
        //int (*parametros);
        char** parametros;
        int qtsParametros;
        int indParams;


};

#endif // ANALISADORSINTATICO_H
