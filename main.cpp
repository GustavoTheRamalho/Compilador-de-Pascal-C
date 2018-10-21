#include <iostream>
#include "TabelaDeSimbolo.h"
#include "No.h"
#include "Simbolo.h"
#include "AnalisadorLexico.h"
#include "AnalisadorSintatico.h"
#include "string"
#include <string.h>
#include <stdlib.h>
using namespace std;


int main()
{

    char* nomeArq = "C:\\Temp\\teste.txt";

    AnalisadorLexico al = AnalisadorLexico(nomeArq);
    AnalisadorSintatico a = AnalisadorSintatico(nomeArq);


    TabelaDeSimbolo ts = TabelaDeSimbolo();
    Simbolo s1 = Simbolo(Inteiro, NULL, 1, 1, 0, NULL);
 /*

    while (al.TemMaisPedaco())
    {
        if (al.ProximoPedaco() == 41)
        {
            cout << "Alguma coisa ai nao esta certa..." << endl;
            return 666;
        }
        //cout << al.ProximoPedaco() << endl;
    }

    try
    {
        a.compilaProgramaPrincipal();
        //a.tstring();                       //chama o tostring da tabela de simb
        printf("Deu bom =)");

       a.getTS()->toString();

    }
    catch(int sla)
    {
        //if (sla == 0)
          //  cout << "Deu erro" << endl;

        if (sla == 10)
            cout << "Eh necessario iniciar o programa com a palavra reservada 'program'" << endl;

        if (sla == 20)
            cout << "Esta faltando um identificador" << endl;

        if (sla == 30)
            cout << "Esta faltando um ';'" << endl;

        if (sla == 40)
            cout << "Eh necessario fechar o bloco com um 'end'" << endl;

        if (sla == 50)
            cout << "Uma funcao eh iniciada com a palavra reservada 'function'" << endl;

        if (sla == 60)
            cout << "Eh necessario fechar o parenteses" << endl;

        if(sla == 70)
            cout << "Para identificar o tipo de um identificador eh necessario o uso do ':'" << endl;

        if (sla == 80)
            cout << "Eh necessario identificar o tipo do identificador: 'boolean' ou 'integer'" << endl;

        if (sla == 90)
            cout << "Um procedimento eh iniciado com a palavra reservada 'procedure'" << endl;

        if (sla == 100)
            cout << "Eh necessario abrir o bloco com um 'begin'" << endl;

        if (sla == 110)
            cout << "Nao eh permitido o uso de numeros pelo codigo aleatoriamente" << endl;

        if (sla == 120)
            cout << "Sintaxe incorreta na declaracao de variaveis" << endl;

        if (sla == 130)
            cout << "Sintaxe incorreta na declaracao de parametros" << endl;

        if (sla == 140)
            cout << "Sintaxe incorreta proxima a condicional/loop" << endl;

        if (sla == 150)
            cout << "Sintaxe incorreta proxima ao loop 'while'" << endl;

        if (sla == 160)
            cout << "Eh necessario utilizar ':=' para efetivar uma atribuicao" << endl;

        if (sla == 170)
            cout << "Sintaxe incorreta no lado direito da atribuicao" << endl;

        if (sla == 180)
            cout << "Eh necessario um operador para completar a operacao com variaveis e numeros" << endl;

        if (sla == 190)
            cout << "Eh necessario o uso de um operador logico na sintaxe da condicional/loop" << endl;

        if (sla == 200)
            cout << "Sintaxe incorreta proxima ao comando condicional/loop" << endl;

        if (sla == 210)
            cout << "Sintaxe incorreta na printagem dos dados" << endl;

        if (sla == 220)
            cout << "Sintaxe incorreta perto do comando else" << endl;

        if (sla == 230)
            cout << "Nao se deve colocar ; no end que precede um else" << endl;

        if (sla == 240)
            cout << "Este identificador ja foi usado antes, use outro" << endl;

        if (sla == 250)
            cout << "Esta variavel nao eh acessivel neste nivel" << endl;

        if (sla == 260)
            cout << "Procedimentos nao retornam nada" << endl;

        if (sla == 270)
            cout << "Um integer nao pode receber true ou false" << endl;

        if (sla == 280)
            cout << "Um boolean nao pode receber um integer" << endl;

        if (sla == 290)
            cout << "Identificador invalido" << endl;

        if (sla == 300)
            cout << "Este identificador nao existe!" << endl;

        if (sla == 310)
            cout << "Procedimentos e funcoes nao podem receber valores!" << endl;

        if (sla == 320)
            cout << "Tipos incompativeis" << endl;

        if (sla == 330)
            cout << "A funcao/procedimento nao possui parametros" << endl;

        if (sla == 340)
            cout << "Sintaxe incorreta na chamada da funcao/procedimento" << endl;

        if (sla == 350)
            cout << "Parametros de tipos incompativeis" << endl;

        if (sla == 360)
            cout << "Numero de parametros insuficiente para chamada da funcao/procedimento" << endl;

        if (sla == 370)
            cout << "Eh necessario separar os parametros com ," << endl;

        if (sla == 380)
            cout << "Uma variavel booleana nao pode receber operacoes pois nao existem operacoes com booleanos" << endl;

        if (sla == 390)
            cout << "Nao eh permitido jogar digitos pelo codigo aleatoriamente" << endl;

        if (sla == 400)
            cout << "Procedimentos nao retornam nada" << endl;
    }



*/


   printf("chegou");
    return 0;
}
