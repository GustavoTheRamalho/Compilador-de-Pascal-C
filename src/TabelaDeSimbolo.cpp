#include "TabelaDeSimbolo.h"
#include "No.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TabelaDeSimbolo::TabelaDeSimbolo()
{
   this->head = NULL;

}

void TabelaDeSimbolo::guarde(Simbolo s) throw()
{
   No *atual = this->head;
   No *anterior = NULL;
   while (atual != NULL)
   {
       anterior = atual;
       atual = atual->proximo;
   }

   if (this->head ==NULL)
       this->head = new No(s);
   else
   {
       anterior->proximo = new No(s);
   }
}

Simbolo TabelaDeSimbolo::getSimbolo(char* id) throw(int)
{
    No* atual = this->head;
    No* anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->valor.getNome(), id)== 0)
        {
            return atual->valor;
        }
         anterior = atual;
         atual = atual->proximo;
    }

    throw 0;
}

int TabelaDeSimbolo::existeSimbolo(char* id) throw()
{
    int ret = 0;
    No* atual = this->head;
    No* anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->valor.getNome() , id) == 0)
        {
            ret = 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }


    return ret;
}

char* TabelaDeSimbolo::toString()
{
   No *atual = this->head;
   No *anterior = NULL;

   while (atual != NULL)
   {
       anterior = atual;
       if (anterior != NULL)
       {
           printf("%s\n",  anterior->valor.getNome());
       }

       atual = atual->proximo;
   }
}

void TabelaDeSimbolo::elimineNivel(int i)
{
   No *atual = this->head;
   No *anterior = NULL;


   while (atual != NULL)
   {
       if (atual->valor.getNivel() == i)
       {
           if (anterior == NULL)
           {
               this->head = atual->proximo;
               free(atual);
               atual = this->head;

           }
           else
           {
               anterior->proximo = atual->proximo;
               free(atual);
               atual = anterior->proximo;
           }
       }
       else
       {
          anterior = atual;
          atual = atual->proximo;
       }

   }
}

TabelaDeSimbolo::~TabelaDeSimbolo() throw()
{
    No *atual = this->head;
    No *anterior = NULL;

    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->proximo;
        free(anterior);
    }

}

TabelaDeSimbolo::TabelaDeSimbolo(const TabelaDeSimbolo &outro) throw()
{
    *this = outro;
}

TabelaDeSimbolo& TabelaDeSimbolo::operator=(const TabelaDeSimbolo &outro) throw()
{
    No *atual = this->head;
    No *anterior = NULL;

    while (atual != NULL)
    {
        anterior = atual;
        atual = atual->proximo;
        delete anterior;
    }

    delete atual;
    delete this->head;
    this->head = outro.head;
}


