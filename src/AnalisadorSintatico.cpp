#include "AnalisadorSintatico.h"
#include "Simbolo.h"
#include "AnalisadorLexico.h"
#include <string.h>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

//O Analisador Sintático está quase pronto, a única coisa que falta é fazer as verificações relacionadas à Tabela de Símbolos
AnalisadorSintatico::AnalisadorSintatico(char* arq)
{
    this->al = new AnalisadorLexico(arq);
    this->nivelAtual = 0;
    this->ts = new TabelaDeSimbolo();
    this->parametros = (char**)malloc(30*sizeof(char*));

    int i;
    for (i=0;i<31;i++)
        this->parametros[i] = (char*)malloc(10*sizeof(char));

    this->indParams = 0;
}

void AnalisadorSintatico::compilaProgramaPrincipal() throw(int, int, int, int, int, int, int, int) //terminar de testar
{
    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 35)
    {
        throw 10;
    }

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != Identificador)
        throw 20;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 21)
        throw 30;

 /*   prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() == 13) //variável
    {
       // prox.setTipo(this->al->ProximoPedaco());
        compilaDeclaracaoDeVariavel();
    }

    while (prox.getTipo() != 40)
    {
        prox.setTipo(this->al->ProximoPedacoSemConsumir());

        if (prox.getTipo() == 17)
        {
            //prox.setTipo(this->al->ProximoPedaco());
            compilaDeclaracaoDeProcedimento();
        }
        else
        if (prox.getTipo() == 18)
        {
            //prox.setTipo(this->al->ProximoPedaco());
            compilaDeclaracaoDeFuncao();
        }
        else
        if (prox.getTipo() == 2)
            compilaComandoComposto();
        else
            throw 40;

        prox.setTipo(this->al->ProximoPedacoSemConsumir());
    }
*/
    prox.setTipo(this->al->ProximoPedacoSemConsumir());
    if (prox.getTipo() == 13) //variável
    {
        prox.setTipo(this->al->ProximoPedaco());
        try
        {
            compilaDeclaracaoDeVariavel();
        }
        catch(int sla)
        {
            throw sla;
        }
    }

    while (prox.getTipo() != 40)
    {
        if (prox.getTipo() == 17)
        {
            //prox.setTipo(this->al->ProximoPedaco());
            try
            {
                compilaDeclaracaoDeProcedimento();
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
        if (prox.getTipo() == 18)
        {
            //prox.setTipo(this->al->ProximoPedaco());
            try
            {
                compilaDeclaracaoDeFuncao();
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
        if (prox.getTipo() == 2)
        {
            try
            {
                compilaComandoComposto();
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
            throw 40;

        prox.setTipo(this->al->ProximoPedacoSemConsumir());
    }
    //free(prox);
    //free(prox);
}

void AnalisadorSintatico::compilaDeclaracaoDeFuncao() throw(int, int, int, int, int, int, int, int, int) //OK
{
    int temParams = 0;
    this->nivelAtual += 1;
    //delete this->parametros;
    //delete &this->qtsParametros;
    this->qtsParametros = 0;
    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 18) //Função
        throw 50;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 39)
        throw 20;

    char* nome = (char*)malloc(31*sizeof(char));
    strcpy(nome, this->al->getIdentificador());

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() == 14) //abre parênteses
    {
        temParams = 1;
        this->parametros = (char**)malloc(30*sizeof(char*));
        int i;
        for (i=0;i<31;i++)
            this->parametros[i] = (char*)malloc(10*sizeof(char));

        try
        {
            compilaParametro();
        }
        catch(int sla)
        {
            throw sla;
        }

        if (prox.getTipo() != 15) //fecha parênteses
            throw 60;

        prox.setTipo(this->al->ProximoPedaco());
    }

    if (prox.getTipo() != 4)
        throw 70;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 19 && prox.getTipo() != 20)
        throw 80;

    if (prox.getTipo() == 19)
    {
        if (temParams == 1)
            this->ts->guarde(Simbolo((TipoPedaco)18, nome, this->nivelAtual-1, 1, this->qtsParametros-1, this->parametros));
        else
        if (temParams == 0)
            this->ts->guarde(Simbolo((TipoPedaco)18, nome, this->nivelAtual-1, 1, 0, NULL));
    }

    if (prox.getTipo() == 20)
    {
        if (temParams == 1)
            this->ts->guarde(Simbolo((TipoPedaco)18, nome, this->nivelAtual-1, 1, this->qtsParametros-1, this->parametros));
        else
        if (temParams == 0)
            this->ts->guarde(Simbolo((TipoPedaco)18, nome, this->nivelAtual-1, 1, 0, NULL));
    }

    free(nome);

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 21)
        throw 30;

    prox.setTipo(this->al->ProximoPedacoSemConsumir());
    if (prox.getTipo() == 13) //variável
    {
        prox.setTipo(this->al->ProximoPedaco());
        try
        {
            compilaDeclaracaoDeVariavel();
        }
        catch(int sla)
        {
            throw sla;
        }
    }

    try
    {
        compilaComandoComposto();
    }
    catch(int sla)
    {
        throw sla;
    }

    //this->ts->elimineNivel(this->nivelAtual);
    this->nivelAtual -= 1;

    //free(prox);
}

void AnalisadorSintatico::compilaDeclaracaoDeProcedimento() throw(int, int, int, int, int, int, int, int) //OK
{
    int temParams = 0;
    this->nivelAtual += 1;
    //int i;
    //for (i=0;i<31;i++)
      //  free(this->parametros[i]);

//    free(this->parametros);
    //delete &this->qtsParametros;
    this->qtsParametros = 0;
    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 17) //procedimento
        throw 90;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 39)
        throw 20;

      char* nome = (char*)malloc(31*sizeof(char));
      strcpy(nome, this->al->getIdentificador());

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() == 14) //abre parênteses
    {
        temParams = 1;
        this->parametros = (char**)malloc(30*sizeof(char*));
        int i;
        for (i=0;i<31;i++)
            this->parametros[i] = (char*)malloc(10*sizeof(char));

        try
        {
            compilaParametro();
        }
        catch(int sla)
        {
            throw sla;
        }

        if (prox.getTipo() != 15) //fecha parênteses
            throw 60;

        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != 21)
            throw 30;
    }
    else
    if (prox.getTipo() != 21) //;
        throw 30;

    //printf("%d\n", this->qtsParametros-1);

    int qts = this->qtsParametros-1;
    if (temParams == 1)
    {
        this->ts->guarde(Simbolo((TipoPedaco)17, nome, this->nivelAtual-1, 0, qts, this->parametros));
        //Simbolo simb = this->ts->getSimbolo(nome);
        //printf("%d\n", simb.getQtsParams());
        //printf("%s\n", simb.getNome());
    }
    else
    if (temParams == 0)
        this->ts->guarde(Simbolo((TipoPedaco)17, nome, this->nivelAtual-1, 0, 0, NULL));

    //Simbolo simb = this->ts->getSimbolo(nome);
    //printf("%d\n", simb.getQtsParams());
    //printf("%s\n", simb.getNome());
    //printf("%d\n", this->qtsParametros);
    //printf("%s\n", nome);
    //printf("%s\n", this->ts->toString());
    free(nome);

    prox.setTipo(this->al->ProximoPedacoSemConsumir());
    if (prox.getTipo() == 13) //variável
    {
        prox.setTipo(this->al->ProximoPedaco());
        try
        {
            compilaDeclaracaoDeVariavel();
        }
        catch(int sla)
        {
            throw sla;
        }
    }

    try
    {
        compilaComandoComposto();
    }
    catch(int sla)
    {
        throw sla;
    }

    //this->ts->elimineNivel(this->nivelAtual);
    this->nivelAtual -= 1;
}

void AnalisadorSintatico::compilaComandoComposto() throw(int, int, int, int, int, int, int, int, int, int, int, int, int, int) //OK
{
    //this->nivelAtual += 1;
    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 2) //begin
        throw 100;

    while (prox.getTipo() != 3) //end
    {
        prox.setTipo(this->al->ProximoPedacoSemConsumir()); //OK
        if (prox.getTipo() == 40) //eof
        {
            throw 40;
        }

        if (prox.getTipo() == 0) //if
        {
            prox.setTipo(this->al->ProximoPedaco());
            try
            {
                compilaIf(0);
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
        if (prox.getTipo() == 1) //while
        {
            prox.setTipo(this->al->ProximoPedaco());
            try
            {
                compilaWhile();
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
        if (prox.getTipo() == 16) //write
        {
            prox.setTipo(this->al->ProximoPedaco());
            try
            {
                compilaPrintNaTela();
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
            /*
        if (prox.getTipo() == 25)
        {
            prox.setTipo(this->al->ProximoPedaco());
            compilaLeituraDoTeclado();
        }
        else*/
        if (prox.getTipo() == 38) //numero, OK
            throw 110;
        else
        if (prox.getTipo() == 39)  //OK
        {
            char* nome = (char*)malloc(31*sizeof(char));
            nome = this->al->getIdentificador();
            //printf("%s\n", nome);

            if (this->ts->existeSimbolo(nome) == 0)
            {
                //printf("aqui");
                throw 300;
            }

            Simbolo simb = this->ts->getSimbolo(nome);
            //printf("%d", (int)simb.getTipo());
            if ((int)simb.getTipo() == 17 || (int)simb.getTipo() == 18)
            {
                //printf("aqui");
                //printf("%s\n", nome);
                prox.setTipo(this->al->ProximoPedaco()); //consome o identificador
                try
                {
                    compilaChamadaDeProcOuFuncao(nome);
                }
                catch(int sla)
                {
                    throw sla;
                }
            }
            else
            {
            //printf("ola");
                if (simb.getNivel() > this->nivelAtual)
                    throw 250; //nivel maior

                prox.setTipo(this->al->ProximoPedaco());
            //printf("%s\n", nome);
                try
                {
                    compilaOperacaoComVariavel();
                }
                catch(int sla)
                {
                    throw sla;
                }
            }
        }
        else
        if (prox.getTipo() == AbreParenteses || prox.getTipo() == Virgula || prox.getTipo() == PontoEVirgula || prox.getTipo() == FechaParenteses ||
            prox.getTipo() == Mais || prox.getTipo() == Menos || prox.getTipo() == Dividido || prox.getTipo() == Vezes ||
            prox.getTipo() == Mod || prox.getTipo() == Maior || prox.getTipo() == Menor || prox.getTipo() == EhIgual ||
            prox.getTipo() == MenorIgual || prox.getTipo() == MaiorIgual || prox.getTipo() == Recebe || prox.getTipo() == DoTipo)
            throw 390;
        else
           // if (prox.getTipo() != Fim)
             //  throw 40;

        prox.setTipo(this->al->ProximoPedaco());
    }

    //this->ts->elimineNivel(this->nivelAtual);
    //this->nivelAtual -= 1;

/*    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 21)
        throw 30;
*/

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() == Senao)
    {
        //prox.setTipo(this->al->ProximoPedaco());
        prox.setTipo(this->al->ProximoPedacoSemConsumir());
        if (prox.getTipo() == Se)
        {
            prox.setTipo(this->al->ProximoPedaco());
            try
            {
                compilaIf(0);
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
        if(prox.getTipo() == 2)
        {
            try
            {
                compilaComandoComposto();
            }
            catch(int sla)
            {
                throw sla;
            }
        }
        else
            throw 220;
    }
    else
    if (prox.getTipo() != 21)
        throw 30;

    if (temElse() == 1)
    {
        throw 230;
    }
    //free(prox);
}

void AnalisadorSintatico::compilaChamadaDeProcOuFuncao(char* procFunc) throw(int, int, int, int, int, int, int, int, int, int, int)
{//chega aqui com o identificador consumido
    Simbolo simb = this->ts->getSimbolo(procFunc);
    //prox.setTipo(this->al->ProximoPedacoSemConsumir());
    //if (prox.getTipo() == Recebe || prox.getTipo() == Mais || prox.getTipo() == Menos || prox.getTipo() == Dividido || prox.getTipo() == Vezes || prox.getTipo() == Mod)
      //  throw 310;
    //printf("%s\n", procFunc);
    //printf("%d\n", simb.getQtsParams());
    //printf("%d\n", simb.getProximoParametro());
    if (simb.getQtsParams() > 0)
    {
        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != AbreParenteses)
            throw 340;

        char* nome = (char*)malloc(30*sizeof(char));
        int i;
        for (i = 0; i <= simb.getQtsParams(); i++)
        {
            prox.setTipo(this->al->ProximoPedaco());
            if (prox.getTipo() == Identificador)
            {
                strcpy(nome, this->al->getIdentificador());
                if (this->ts->existeSimbolo(nome) == 0)
                {
                    //printf("aqui");
                    throw 300;
                }

                Simbolo simb2 = this->ts->getSimbolo(nome);
                if (simb2.getRetorno() == 1 && strcmp(simb.getProximoParametro(), "integer") != 0)
                    throw 350;
                else
                 if (simb2.getRetorno() == 2 && strcmp(simb.getProximoParametro(), "boolean") != 0)
                    throw 350;
            }
            else
            if (prox.getTipo() == True || prox.getTipo() == False)
            {
                if (strcmp(simb.getProximoParametro(), "boolean") != 0)
                    throw 350;
            }
            else
            if (prox.getTipo() == Numero)
            {
                if (strcmp(simb.getProximoParametro(), "integer") != 0)
                    throw 350;
            }
            else
                throw 360;

            prox.setTipo(this->al->ProximoPedaco());
            if (prox.getTipo() != Virgula && i != simb.getQtsParams())
                throw 370;
        }

        free(nome);
        //prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != FechaParenteses)
            throw 340;

        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != PontoEVirgula && prox.getTipo() != Mais && prox.getTipo() != Menos
             && prox.getTipo() != Vezes && prox.getTipo() != Dividido && prox.getTipo() != Mod)
            throw 340;
    }
    else
    {
        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != PontoEVirgula && prox.getTipo() != Mais && prox.getTipo() != Menos
             && prox.getTipo() != Vezes && prox.getTipo() != Dividido && prox.getTipo() != Mod)
            throw 330;
    }

    //prox.setTipo(this->al->ProximoPedaco());
}

void AnalisadorSintatico::compilaDeclaracaoDeVariavel() throw(int, int, int, int, int, int, int, int, int, int, int) //OK ~OK
{//
    int ind= 0;
    char** vars = (char**)malloc(15*sizeof(char*));
    for (int k=0; k<15; k++)
        vars[k] = (char*)malloc(31*sizeof(char));


    prox.setTipo(this->al->ProximoPedaco());

    if (prox.getTipo() != Identificador)
        throw 20;

    vars[ind] = this->al->getIdentificador();


    if (this->ts->existeSimbolo(vars[ind]) == 1)
        throw 240;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() == Virgula) //,
    {
        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != Identificador) //identificador
            throw 20;

        while (prox.getTipo() == Identificador)
        {
            ind++;
            vars[ind] = this->al->getIdentificador();
            if (this->ts->existeSimbolo(vars[ind]) == 1)
                throw 240;

            prox.setTipo(this->al->ProximoPedaco());
            if (prox.getTipo() != 22 && prox.getTipo() != 4) //4 é :
                throw 120;

            prox.setTipo(this->al->ProximoPedaco());
        }
    }
    else
    {
        if (prox.getTipo() != DoTipo) //:
            throw 70;

        prox.setTipo(this->al->ProximoPedaco());
    }

   // prox.setTipo(this->al->ProximoPedaco());

    if (prox.getTipo() != 19 && prox.getTipo() != 20) //19 é integer e 20 é boolean
        throw 80;


    if (prox.getTipo() == 19)
    {

        for (int i=0; i<=ind; i++)
        {
             char* nome = (char*)malloc(31*(sizeof(char)));
             strcpy(nome, vars[i]);

             if (this->ts->existeSimbolo(nome) == 1)
                throw 240;

             this->ts->guarde(Simbolo(Variaveis, nome, this->nivelAtual, 1, -1, NULL));
             free(nome);
        }

    }

    if (prox.getTipo() == 20)
    {

        for (int i=0; i<=ind; i++)
        {
             char* nome = (char*)malloc(31*(sizeof(char)));
             strcpy(nome, vars[i]);

             if (this->ts->existeSimbolo(nome) == 1)
                throw 240;
             this->ts->guarde(Simbolo(Variaveis, nome, this->nivelAtual, 2, -1, this->parametros));
             free(nome);
        }
    }

    for (int i=0; i<15; i++)
      free(vars[i]);
    free(vars);


    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 21) //;
        throw 30;

    prox.setTipo(this->al->ProximoPedacoSemConsumir());
    if (prox.getTipo() == 39)
    {
        //prox.setTipo(this->al->ProximoPedaco());
        try
        {
            compilaDeclaracaoDeVariavel();
        }
        catch(int sla)
        {
            throw sla;
        }
    }
    //free(prox);
}

void AnalisadorSintatico::compilaParametro() throw(int, int, int, int, int, int, int, int, int, int, int) //OK OK
{
    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 39)
        throw 20;

    int ind= 0;
    char** params = (char**)malloc(15*sizeof(char*));
    for (int k=0; k<15; k++)
        params[k] = (char*)malloc(31*sizeof(char));

    params[ind] = this->al->getIdentificador();
    if (this->ts->existeSimbolo(params[ind]) == 1)
        throw 240;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() == 22)
    {
        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != 39)
            throw 20;

        while (prox.getTipo() == 39)
        {
            ind ++;
            params[ind] = this->al->getIdentificador();
            if (this->ts->existeSimbolo(params[ind]) == 1)
                throw 240;

            prox.setTipo(this->al->ProximoPedaco());
            if (prox.getTipo() != 22 && prox.getTipo() != 4)
                throw 130;

            if (prox.getTipo() == 22)
            {
                prox.setTipo(this->al->ProximoPedaco());
                if (prox.getTipo() != 39)
                    throw 20;
            }
        }
    }
    else if (prox.getTipo() != 4)
        throw 70;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 19 && prox.getTipo() != 20)
        throw 80;

    if (prox.getTipo() == 19)
    {
        for (int i=0; i<=ind; i++)
        {
             char* nome = (char*)malloc(31*(sizeof(char)));
             strcpy(nome, params[i]);

             if (this->ts->existeSimbolo(nome) == 1)
                throw 240;

             this->qtsParametros++;
             //printf("%d\n", this->qtsParametros);
             strcpy(this->parametros[indParams], "integer");
             //printf("%s\n", this->parametros[this->indParams]);
             this->indParams++;
             this->ts->guarde(Simbolo(Variaveis, nome, this->nivelAtual, 1, -1, this->parametros));
             //printf("%s\n", nome);
             free(nome);
        }
    }
    else
    if (prox.getTipo() == 20)
    {
        for (int i=0; i<=ind; i++)
        {
             char* nome = (char*)malloc(31*(sizeof(char)));
             strcpy(nome, params[i]);

             if (this->ts->existeSimbolo(nome) == 1)
                throw 240;

             this->qtsParametros++;
             //printf("%d\n", this->qtsParametros);
             strcpy(this->parametros[indParams], "boolean");
             //printf("%s\n", this->parametros[this->indParams]);
             this->indParams++;
             this->ts->guarde(Simbolo(Variaveis, nome, this->nivelAtual, 2, -1, this->parametros));
             free(nome);
        }
    }

    for (int i=0; i<15; i++)
      free(params[i]);
    free(params);

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() == 21)
    {
        try
        {
            compilaParametro();
        }
        catch(int sla)
        {
            throw sla;
        }
    }

    //free(prox);
}

void AnalisadorSintatico::compilaIf(int ehWhile) throw(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int) //OK
{
    prox.setTipo(this->al->ProximoPedacoSemConsumir());

    if (prox.getTipo() == Nao) //se for um not
    {
        prox.setTipo(this->al->ProximoPedaco()); //consome ele
        prox.setTipo(this->al->ProximoPedacoSemConsumir());
    }

    if (prox.getTipo() == Identificador || prox.getTipo() == Numero)  //se já de cara for um número ou var
    {
        try
        {
            compilaExpressaoBooleana(); //compila
        }
        catch(int sla)
        {
            throw sla;
        }

        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() == E || prox.getTipo() == Ou)
        {
            prox.setTipo(this->al->ProximoPedacoSemConsumir());
            if (prox.getTipo() != Identificador || prox.getTipo() != Numero)
            {
                //printf("aqui");
                throw 140;
            }

            try
            {
                compilaExpressaoBooleana(); //compila
            }
            catch(int sla)
            {
                throw sla;
            }

            prox.setTipo(this->al->ProximoPedaco());
        }
    }
    else
    if (prox.getTipo() == AbreParenteses) //caso haja um parênteses
    {
        prox.setTipo(this->al->ProximoPedaco());
        int qtsAbre = 0;
        int qtsFecha = 0;

        while (prox.getTipo() == AbreParenteses) //enquanto houverem parênteses sendo abertos
        {
            //prox.setTipo(this->al->ProximoPedaco()); //consome o abre parênteses
            qtsAbre++;
            prox.setTipo(this->al->ProximoPedacoSemConsumir()); //não consome o próximo           AQ TAVA ERRADO
            if (prox.getTipo() != Identificador && prox.getTipo() != Numero && prox.getTipo() != Nao) //e se o próximo não for not, var, num
                throw 140; //lança exceção

            if (prox.getTipo() == 26) //se for um not
            {
                prox.setTipo(this->al->ProximoPedaco()); //consome not
                prox.setTipo(this->al->ProximoPedacoSemConsumir()); //consome próximo

                if (prox.getTipo() != 39 && prox.getTipo() != 38) //e se o próximo não for var nem num
                    throw 140; //lança exceção
            }

            try
            {
                compilaExpressaoBooleana(); //compila
            }
            catch(int sla)
            {
                throw sla;
            } //depois, como chegou até aqui, quer dizer que é algo válido, então compila

            prox.setTipo(this->al->ProximoPedaco()); //depois de compilar, ele verifica o próximo
            if (prox.getTipo() != E && prox.getTipo() != Ou && prox.getTipo() != FechaParenteses) //se não for nem e nem ou nem )
                throw 140; //exceção

            //prox->setTipo(this->al->ProximoPedacoSemConsumir()); //depois, não consome o próximo
            if (prox.getTipo() == E || prox.getTipo() == Ou) //se ele for e/ou
            {
                prox.setTipo(this->al->ProximoPedaco());
                if (prox.getTipo() != AbreParenteses && prox.getTipo() != Identificador && prox.getTipo() != Numero && prox.getTipo() != Nao)
                    throw 140;
                //se esse próximo não for nem ( nem num nem var nem not, exceção

                if (prox.getTipo() == Nao)
                    prox.setTipo(this->al->ProximoPedaco());

                if (prox.getTipo() == Identificador || prox.getTipo() == Numero)
                {
                    try
                    {
                        compilaExpressaoBooleana(); //compila
                    }
                    catch(int sla)
                    {
                        throw sla;
                    }
                }

                prox.setTipo(this->al->ProximoPedaco()); //se chegou aqui, é um desses, então consome o e/ou lá de cima
            }  //se for var ou num, vai sair do while e compilar a última expressão, se for  vai continuar no while
            else
            {
                qtsFecha++;
                prox.setTipo(this->al->ProximoPedaco());
                if (prox.getTipo() == E || prox.getTipo() == Ou) //se ele for e/ou
                {
                    prox.setTipo(this->al->ProximoPedaco()); //não consome o próximo
                    if (prox.getTipo() != AbreParenteses && prox.getTipo() != Identificador && prox.getTipo() != Numero && prox.getTipo() != Nao)
                        throw 140;
                        //se esse próximo não for nem ( nem num nem var nem not, exceção

                    if (prox.getTipo() == Nao)
                        prox.setTipo(this->al->ProximoPedaco());

                    if (prox.getTipo() == Identificador || prox.getTipo() == Numero)
                    {
                        try
                        {
                            compilaExpressaoBooleana(); //compila
                        }
                        catch(int sla)
                        {
                            throw sla;
                        }
                    }

                    //prox.setTipo(this->al->ProximoPedaco());
                }   //se for var ou num, vai sair do while e compilar a última expressão, se for  vai continuar no while
            }

            //agora, se não for nem e nem ou, ou seja, se não entrou naquele while, quer dizer q é )
        }

        if (prox.getTipo() == E || prox.getTipo() == Ou)
        {
            prox.setTipo(this->al->ProximoPedaco());
            prox.setTipo(this->al->ProximoPedaco());
        }

        if (prox.getTipo() == 39 || prox.getTipo() == 38 || prox.getTipo() == 26)
        {
            if (prox.getTipo() == Nao)
                prox.setTipo(this->al->ProximoPedaco());

            try
            {
                compilaExpressaoBooleana(); //compila
            }
            catch(int sla)
            {
                throw sla;
            }
        }

        if (qtsAbre != qtsFecha)
            throw 200;
    }
    else
        throw 200;

    if (ehWhile == 0) //se o método não foi chamado a partir do while
    {
        //prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != 23)
            throw 140;
    }
    else
    {
        //prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != 24)
            throw 140;
    }

    try
    {
        compilaComandoComposto(); //compila
    }
    catch(int sla)
    {
        throw sla;
    }

    //free(prox);
}

void AnalisadorSintatico::compilaWhile() throw(int) //OK
{
    try
    {
        compilaIf(1); //a expressão dentro do if e a expressão dentro do while é exatamente a mesma, a única coisa é q no final
          //do if tem um then, e no final do while tem um do
    }
    catch(int sla)
    {
        throw sla;
    }
}

void AnalisadorSintatico::compilaPrintNaTela() throw(int, int, int, int, int, int, int, int)
{
    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 14)
        throw 210;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != Identificador)
        throw 210;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != FechaParenteses && prox.getTipo() != Mais)
        throw 210;

    if (prox.getTipo() == Mais)
    {
        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != Identificador)
            throw 210;

        while (prox.getTipo() == Identificador)
        {
            prox.setTipo(this->al->ProximoPedaco());
            if (prox.getTipo() != FechaParenteses && prox.getTipo() != Mais)
                throw 210;

            if (prox.getTipo() == Mais)
            {
                prox.setTipo(this->al->ProximoPedaco());
                if (prox.getTipo() != Identificador)
                    throw 210;
            }

            //prox.setTipo(this->al->ProximoPedaco());
        }
    }

    if (prox.getTipo() != FechaParenteses)
        throw 210;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != PontoEVirgula)
        throw 30;
}

void AnalisadorSintatico::compilaOperacaoComVariavel() throw(int, int, int, int, int, int, int/*, int, int*/) //OK
{
    //o fluxo chegará aqui já com o identificador da variável consumido
    char* nome = (char*)malloc(31*sizeof(char));
    nome = this->al->getIdentificador();

    if (this->ts->existeSimbolo(nome) == 0)
    {
        //printf("aqui");
        throw 300; //variavel inexisente
    }

    Simbolo simb = this->ts->getSimbolo(nome);
    int tipo = simb.getRetorno();

    if (simb.getTipo() == Procedimento || simb.getTipo() == Funcao)
        throw 310;

    if (simb.getNivel() > this->nivelAtual)
        throw 250;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 5)
        throw 160;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 38 && prox.getTipo() != 39 && prox.getTipo() != 33 && prox.getTipo() != 34)
        throw 170;

    if (tipo == 2 && (prox.getTipo() == 38))
        throw 280; //tipos incompativeis

    if (tipo == 1 && (prox.getTipo() == 33 || prox.getTipo() == 34))
        throw 270;

    if (prox.getTipo() == 33 || prox.getTipo() == 34) //se for true ou false
    {
        prox.setTipo(this->al->ProximoPedaco());
        if (prox.getTipo() != 21)
        {
            //printf("aqui");
            throw 380;
        }
    }
    else
    {
        while (prox.getTipo() == 38 || prox.getTipo() == 39)
        {
            if (prox.getTipo() == 38 && tipo == 2)
                throw 280;

            if (prox.getTipo() == 39)
            {

                nome = this->al->getIdentificador();
                if (this->ts->existeSimbolo(nome) == 0)
                    throw 300;

                Simbolo simb2 = this->ts->getSimbolo(nome);
                if (simb2.getNivel() > this->nivelAtual)
                    throw 250;

                if (simb2.getTipo() == Procedimento)
                    throw 400;

                if (simb2.getTipo() == Funcao)
                {
                    if (simb2.getTipo() != tipo)
                        throw 320;
                }


                if (identificadorEhValido(tipo, nome) == 0)
                    throw 320;

                //compilaChamadaDeProcOuFuncao(nome);
            }

            prox.setTipo(this->al->ProximoPedaco());
            //printf("%d\n", (int)prox.getTipo());
            if (prox.getTipo() != 21 && prox.getTipo() != 28 && prox.getTipo() != 29 && prox.getTipo() != 30 && prox.getTipo() != 31 && prox.getTipo() != 32)
                throw 180;

            if (prox.getTipo() != 21)
                prox.setTipo(this->al->ProximoPedaco());
        }

        if (prox.getTipo() == True || prox.getTipo() == False && tipo==1)
            throw 270;

        if (prox.getTipo() != 21)
        {
            //printf("aqui");
            throw 30;
        }
    }

    free(nome);

    //free(prox);
}

int AnalisadorSintatico::temElse() throw()
{
    Simbolo aux;
    aux.setTipo(this->al->ProximoPedacoSemConsumir());
    if (aux.getTipo() == Senao)
        return 1;
    else
        return 0;
}

void AnalisadorSintatico::compilaExpressaoBooleana() throw(int, int, int, int, int, int, int, int) //OK
{
    int tipo;
    prox.setTipo(this->al->ProximoPedaco()); //lembrando q qd esse método for chamado, o numero ou var não terá sido consumida ainda
    //então consumimos ele primeiro
    char* nome = (char*)malloc(31 * sizeof(char));
    nome = this->al->getIdentificador();

    if (this->ts->existeSimbolo(nome) == 0)
    {
        //printf("aqui");
        throw 300;
    }

    Simbolo simb = this->ts->getSimbolo(nome);
    tipo = simb.getRetorno();
    if (simb.getTipo() == 17)
        throw 260;

    if (simb.getNivel() > this->nivelAtual)
        throw 250;

    prox.setTipo(this->al->ProximoPedaco()); //depois consumimos o operador lógico
    if (prox.getTipo() != 6 && prox.getTipo() != 7 && prox.getTipo() != 8 && prox.getTipo() != 9 && prox.getTipo() != 36)
        throw 190;

    prox.setTipo(this->al->ProximoPedaco());
    if (prox.getTipo() != 38 && prox.getTipo() != 39 && prox.getTipo() != 33 && prox.getTipo() != 34)
        throw 200;

    if (prox.getTipo() == 39)
        nome = this->al->getIdentificador();

    if (tipo == 2 && prox.getTipo() == 38)
        throw 280;

    if (tipo == 1 && (prox.getTipo() == 33 || prox.getTipo() == 34))
        throw 270;

    if (identificadorEhValido(tipo, nome) == 0)
        throw 320;

}

int AnalisadorSintatico::identificadorEhValido(int tipo, char* nm) throw()
{
    if (tipo == 1)
    {
        try
        {
            Simbolo simb = this->ts->getSimbolo(nm);
            if (simb.getTipo() == 17)
                return 0;

            if (simb.getRetorno() != 1)
                return 0;

            if (simb.getNivel() > this->nivelAtual)
                return 0;

            return 1;
        }
        catch(int sla)
        {
            return 0;
        }
    }
    else
    if (tipo == 2)
    {
        try
        {
            Simbolo simb = this->ts->getSimbolo(nm);
            if (simb.getTipo() == 17)
                return 0;

            if (simb.getRetorno() != 2)
                return 0;

            if (simb.getNivel() > this->nivelAtual)
                return 0;

            return 1;
        }
        catch(int sla)
        {
            return 0;
        }
    }
    else
        return 0;
}

AnalisadorLexico* AnalisadorSintatico::getAl() const throw()
{
    AnalisadorLexico* ret = new AnalisadorLexico(*(this->al));
    return ret;
}

TabelaDeSimbolo* AnalisadorSintatico::getTS() const throw()
{
    TabelaDeSimbolo* ret = new TabelaDeSimbolo(*(this->ts));
    return ret;
}

AnalisadorSintatico::~AnalisadorSintatico() throw()
{
    delete al;
    delete ts;
}

AnalisadorSintatico::AnalisadorSintatico(const AnalisadorSintatico &outro) throw()
{
    *this = outro;
}

AnalisadorSintatico& AnalisadorSintatico::operator=(const AnalisadorSintatico &outro) throw()
{
    this->prox = outro.prox;
    delete this->al;
    this->al = outro.getAl();
}

char* AnalisadorSintatico::tstring()
{
    return this->ts->toString();
}
