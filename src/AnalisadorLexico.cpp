#include "AnalisadorLexico.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

AnalisadorLexico::AnalisadorLexico(char* arq)
{
   this->arquivo = fopen(arq, "r");
   this->pedaco = (char*)malloc(31*sizeof(char));

}

char ehNumero(char*str) throw()
{
    for (int i=0; i<strlen(str); i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

char ehIdentificador(char*str) throw()
{
    if (isdigit(str[0]))
        return 0;

    for (int i=0; i<strlen(str); i++)
       if (!isalnum(str[i]))
           return 0;
    return 1;
}

TipoPedaco AnalisadorLexico::ProximoPedaco() throw()
{

   if (!this->TemMaisPedaco())
        return EndOfFile;

   this->pedaco = (char*)malloc(256*sizeof(char));
   char* c = this->pedaco;
   char atual;
   int j = 0;

   atual = fgetc(this->arquivo);
   if (atual == ';')
      return PontoEVirgula;

   ungetc(atual, this->arquivo);

   while (  ((atual != EOF) && (atual != ' ') && (atual != '\n') && (atual != '\t') && (isalnum(atual))) || j==0)
   {
      atual =(char)fgetc(this->arquivo);
      if (isalnum(atual))
         c[j++] = atual;

      else if (atual != EOF && atual != ' ' && atual != '\n' && (atual != '\t') && atual != ';')
      {
          if (j == 0)
          {
              c[j++] = atual;
              if (atual == ':')
              {
                  char f = fgetc(this->arquivo);
                  if (f == '=')
                    c[j++] = f;
                  else
                    ungetc(f, this->arquivo);
              }
          }
           else
              ungetc(atual, this->arquivo);
      }
   }


   if (atual == ';')
    ungetc(atual, this->arquivo);

    c[j] = '\0';

    return this->identificaTipo(this->pedaco);
}

TipoPedaco AnalisadorLexico::identificaTipo(char* p) throw()
{
   for (int i=0; i<38; i++)
   {

    if (strcmp(p, this->PalavrasReservadas[i]) == 0)
        return (TipoPedaco)i;
   }


   if (ehNumero(p))
     return Numero;

   if (ehIdentificador(p))
    return Identificador;

   return Desconhecido;
}

char* AnalisadorLexico::getIdentificador() throw()
{
    return pedaco;
}

TipoPedaco AnalisadorLexico::ProximoPedacoSemConsumir() throw()
{
  if (this->TemMaisPedaco())
  {
     int i = this->ProximoPedaco();
     ungetc(' ', this->arquivo);
     int j;
     for (j = strlen(this->pedaco) - 1; j>=0; j--)
       ungetc(this->pedaco[j], this->arquivo);
     return (TipoPedaco)i;
  }
  else
     return EndOfFile;

}

char AnalisadorLexico::TemMaisPedaco() throw()
{
    char a = (char)fgetc(this->arquivo);
    if (a == EOF)
        return 0;

    ungetc(a, this->arquivo);
    return 1;

}

AnalisadorLexico::~AnalisadorLexico() throw()
{
    fclose(arquivo);
    free(pedaco);
    free(arquivo);
    int i = 0;
    while (i < 39)
    {
        free(this->PalavrasReservadas[i]);
        i++;
    }
}

AnalisadorLexico::AnalisadorLexico(const AnalisadorLexico &outro) throw()
{
    *this = outro;
}

AnalisadorLexico& AnalisadorLexico::operator=(const AnalisadorLexico &outro) throw()
{
    free(this->arquivo);
    free(this->pedaco);
    int i = 0;
    while (i < 39)
    {
        free(this->PalavrasReservadas[i]);
        i++;
    }

    this->arquivo = outro.arquivo;
    this->pedaco = outro.pedaco;
    i = 0;
    while (i < 39)
    {
        strcpy(this->PalavrasReservadas[i], outro.PalavrasReservadas[i]);
        i++;
    }

    return *this;
}
