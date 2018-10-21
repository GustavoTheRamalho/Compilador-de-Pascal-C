#include <stdio.h>

#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H


typedef enum TipoPedaco
{
    Se=0, Enquanto,
    Incio, Fim,
    DoTipo /* 4 */,
    Recebe,
    Maior, Menor, MaiorIgual, MenorIgual, E /* 10 */, Ou, DiferenteDe,
    Variaveis, AbreParenteses /* 14 */, FechaParenteses,
    Escreva, Procedimento, Funcao, Inteiro /* 19 */, Booleano,
    PontoEVirgula, Virgula, Entao, Faca, Leia, Nao, Aspas /* 27 */,
    Mais, Menos, Vezes, Dividido, Mod, True, False, Programa, EhIgual, Senao, Numero, Identificador /* 39 */, EndOfFile, Desconhecido
} TipoPedaco;

class AnalisadorLexico
{
    public:
        AnalisadorLexico(char *);
        TipoPedaco ProximoPedaco() throw();
        TipoPedaco ProximoPedacoSemConsumir() throw();
        //int ehCadeiaParaPrint() throw();
        char TemMaisPedaco() throw();
        char* getIdentificador() throw();
        TipoPedaco identificaTipo(char*) throw();
        ~AnalisadorLexico() throw();
        AnalisadorLexico(const AnalisadorLexico&) throw();
        AnalisadorLexico& operator=(const AnalisadorLexico&) throw();


    protected:

    private:
        FILE* arquivo;
        char* pedaco;
        char*PalavrasReservadas[38] = {"if", "while", "begin", "end", ":", ":=", ">",
         "<", ">=", "<=", "and", "or", "<>", "var", "(", ")", "write", "procedure", "function", "integer", "boolean", ";", ",",
         "then", "do", "readln", "not", "?", "+", "-", "*", "/", "%", "true", "false", "program", "=", "else"};

};

#endif // ANALISADORLEXICO_H
